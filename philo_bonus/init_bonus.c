/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:34:03 by skarim            #+#    #+#             */
/*   Updated: 2024/02/24 16:25:50 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nbr_meals = 0;
		data->philos[i].is_eating = 0;
		data->philos[i].data = data;
		data->philos[i].done = 0;
		// sem_unlink("philo_sem");
		// data->philos[i].philo_sem = sem_open("philo_sem", O_CREAT, 0600, 1);
		i++;
	}
	return (0);
}

void	ft_create_sem(t_data *data)
{
	sem_unlink("end_sem");
	sem_unlink("fork_sem");
	sem_unlink("dead_flag_sem");
	sem_unlink("writing_sem");
	data->fork_sem = sem_open("fork_sem", O_CREAT, 0600, data->nbr_philos);
	data->writing_sem = sem_open("writing_sem", O_CREAT, 0600, 1);
}

int	ft_init(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		return (-1);
	ft_philo_init(data);
	ft_create_sem(data);
	return (0);
}
