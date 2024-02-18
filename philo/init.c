/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:38:49 by skarim            #+#    #+#             */
/*   Updated: 2024/02/18 13:53:12 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_philos(t_data *data, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		ft_mutex_handler(&(data->philos[i].philo_mtx), DESTROY);
		i++;
	}
}

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
		if ((i + 1) % 2 == 0)
		{
			data->philos[i].ffork_index = i;
			data->philos[i].sfork_index = (i + 1) % data->nbr_philos;
		}
		else
		{
			data->philos[i].ffork_index = (i + 1) % data->nbr_philos;
			data->philos[i].sfork_index = i;
		}
		if (ft_mutex_handler(&(data->philos[i].philo_mtx), INIT) != 0)
			return (ft_destroy_philos(data, i), -1);
		i++;
	}
	return (0);
}

void	ft_destroy_forks(t_data *data, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		ft_mutex_handler(&data->forks[i].fork_mutex, DESTROY);
		i++;
	}
}

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		if (ft_mutex_handler(&(data->forks[i].fork_mutex), INIT) != 0)
			return (free(data->forks), free(data->philos),
				ft_destroy_forks(data, i), -1);
		i++;
	}
	if (ft_mutex_handler(&(data->writing), INIT) != 0)
		return (free(data->forks), free(data->philos),
			ft_destroy_forks(data, i), -1);
	if (ft_mutex_handler(&(data->data_mtx), INIT) != 0)
	{
		ft_mutex_handler(&(data->writing), DESTROY);
		return (free(data->forks), free(data->philos),
			ft_destroy_forks(data, i), -1);
	}
	return (0);
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
	if (ft_philo_init(data) != 0)
		return (-1);
	i = 0;
	data->dead_flag = 0;
	data->end = 0;
	if (ft_init_mutex(data) != 0)
		return (-1);
	return (0);
}
