/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:51:14 by skarim            #+#    #+#             */
/*   Updated: 2024/02/19 12:15:09 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_must_eat(t_data *data)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (i < data->nbr_philos)
	{
		if (get_with_mutex(&(data->philos[i].philo_mtx),
				&data->philos[i].nbr_meals) >= data->nbr_times_eat)
			nbr++;
		i++;
	}
	if (nbr == data->nbr_philos)
		set_with_mutex(&(data->data_mtx), &data->end, 1);
}

void	monitor(t_data *data)
{
	int	i;

	while (!get_with_mutex(&data->data_mtx, &data->dead_flag))
	{
		usleep(100);
		i = -1;
		while (++i < data->nbr_philos && !get_with_mutex(&data->data_mtx,
				&data->dead_flag))
		{
			if (!get_with_mutex(&(data->philos[i].philo_mtx),
					&data->philos[i].is_eating) && (get_time()
					- getlong_with_mutex(&(data->philos[i].philo_mtx),
						&data->philos[i].last_eating)) > data->time_die)
			{
				ft_print(&data->philos[i], "died", 1);
				set_with_mutex(&data->data_mtx, &data->dead_flag, 1);
			}
		}
		if (data->nbr_times_eat != -1)
		{
			ft_must_eat(data);
			if (get_with_mutex(&(data->data_mtx), &(data->end)) == 1)
				break ;
		}
	}
}

void	ft_free_all(t_data *data, int threads_nbr)
{
	int	i;

	i = 0;
	if (data->nbr_philos == 1)
		pthread_detach(data->philos[0].thread);
	else
	{
		while (i < threads_nbr)
		{
			pthread_join(data->philos[i].thread, NULL);
			i++;
		}
	}
	ft_destroy_forks(data, data->nbr_philos);
	ft_destroy_philos(data, data->nbr_philos);
	ft_mutex_handler(&(data->writing), DESTROY);
	ft_mutex_handler(&(data->data_mtx), DESTROY);
	free(data->forks);
	free(data->philos);
}

int	ft_start(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nbr_philos)
	{
		data->philos[i].last_eating = get_time();
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&(data->philos[i])))
			return (ft_free_all(data, i), -1);
		i++;
	}
	monitor(data);
	ft_mutex_handler(&(data->writing), UNLOCK);
	ft_free_all(data, i);
	return (0);
}
