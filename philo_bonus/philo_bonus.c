/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:45:41 by skarim            #+#    #+#             */
/*   Updated: 2024/02/26 13:51:29 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_valid_input(int ac, char **av, t_data *data)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (-1);
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(av[i]) == -1 || ft_atoi(av[i]) == 0)
			return (-1);
		i++;
	}
	if (ac == 6)
		if (ft_atoi(av[5]) == -1)
			return (-1);
	data->nbr_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->nbr_times_eat = -1;
	if (ac == 6)
		data->nbr_times_eat = ft_atoi(av[5]);
	return (0);
}

void	ft_wait_childs(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
			break ;
		if (status >> 8 == 1)
		{
			while (++i < data->nbr_philos)
			{
				kill(data->philos[i].pid, SIGKILL);
			}
			break ;
		}
	}
}

void	ft_start(t_data *data)
{
	int			i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nbr_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			printf("Error creating process");
			return ;
		}
		if (data->philos[i].pid == 0)
		{
			ft_routine(&data->philos[i]);
		}
		i++;
	}
	ft_wait_childs(data);
	sem_post(data->writing_sem);
	sem_close(data->fork_sem);
	sem_close(data->writing_sem);
	sem_unlink("/fork_sem");
	sem_unlink("/writing_sem");
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_valid_input(argc, argv, &data) == -1)
		return (ft_error_message("wrong arguments!"));
	if (data.nbr_times_eat == 0)
		return (0);
	if (ft_init(&data) == -1)
		return (ft_error_message("Data initialization fails"));
	ft_start(&data);
}
