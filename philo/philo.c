/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:31:31 by skarim            #+#    #+#             */
/*   Updated: 2024/02/15 21:43:03 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ft_mutex_handler(pthread_mutex_t *mutex, t_mutex_opr mutex_opr)
{
	if (mutex_opr == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (mutex_opr == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (mutex_opr == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (mutex_opr == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else
		return (-1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_valid_input(argc, argv, &data) == -1)
		return (ft_error_message("wrong arguments!"));
	if (ft_init(&data) == -1)
		return (ft_error_message("Data initialization fails"));
	if (ft_start(&data) == -1)
		return (ft_error_message("threads error"));
	return (0);
}
