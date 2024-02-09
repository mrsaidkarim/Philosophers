/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:38:49 by skarim            #+#    #+#             */
/*   Updated: 2024/02/09 15:45:26 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nbr_meals = 0;
		data->philos[i].last_eating = -1;
		data->philos[i].dead_flag = 0;
		data->philos[i].ffork_id = i;
		data->philos[i].sfork_id = (i + 1) % data->nbr_philos;
		data->philos[i].data = data;
		i++;
	}
}

int	ft_init(t_data *data)
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->nbr_philos);
	if (!data->philos)
		return (-1);
	data->forks = (t_fork *)malloc(sizeof(t_fork) * data->nbr_philos);
	if (!data->forks)
	{
		free(data->philos);
		return (-1);
	}
	ft_philo_init(data);
	i = 0;
	while (i < data->nbr_philos)
	{
		data->forks[i].fork_id = i + 1;
		if (ft_mutex_handler(&(data->forks[i].fork_mutex), INIT))
			return (-1);
		i++;
	}
	if (ft_mutex_handler(&(data->writing), INIT))
		return (-1);
}
