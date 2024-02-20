/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:49:05 by skarim            #+#    #+#             */
/*   Updated: 2024/02/19 11:37:48 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int duration)
{
	long	time_start;

	time_start = get_time();
	while (get_time() - time_start < duration)
	{
		usleep(100);
	}
}

void	ft_print(t_philo *philo, char *msg, int unlock)
{
	unsigned long	time;

	time = get_time() - philo->data->start_time;
	ft_mutex_handler(&(philo->data->writing), LOCK);
	if (!get_with_mutex(&philo->data->data_mtx, &philo->data->end)
		&& !get_with_mutex(&philo->data->data_mtx, &philo->data->dead_flag))
		printf("%ld %d %s\n", time, philo->id, msg);
	if (unlock == 0)
		ft_mutex_handler(&(philo->data->writing), UNLOCK);
}

void	ft_eat(t_philo *philo)
{
	ft_mutex_handler(&philo->data->forks[philo->ffork_index].fork_mutex, LOCK);
	ft_print(philo, "has taken a fork", 0);
	ft_mutex_handler(&philo->data->forks[philo->sfork_index].fork_mutex, LOCK);
	ft_print(philo, "has taken a fork", 0);
	ft_print(philo, "is eating", 0);
	ft_mutex_handler(&philo->philo_mtx, LOCK);
	philo->last_eating = get_time();
	ft_mutex_handler(&philo->philo_mtx, UNLOCK);
	set_with_mutex(&philo->philo_mtx, &philo->is_eating, 1);
	set_with_mutex(&(philo->philo_mtx), &philo->nbr_meals,
		philo->nbr_meals + 1);
	ft_usleep(philo->data->time_eat);
	ft_mutex_handler(&philo->data->forks[philo->ffork_index].fork_mutex,
		UNLOCK);
	ft_mutex_handler(&philo->data->forks[philo->sfork_index].fork_mutex,
		UNLOCK);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (!get_with_mutex(&philo->data->data_mtx, &philo->data->end)
		&& !get_with_mutex(&philo->data->data_mtx, &philo->data->dead_flag))
	{
		ft_eat(philo);
		set_with_mutex(&philo->philo_mtx, &philo->is_eating, 0);
		ft_print(philo, "is sleeping", 0);
		ft_usleep(philo->data->time_sleep);
		ft_print(philo, "is thinking", 0);
	}
	return (NULL);
}
