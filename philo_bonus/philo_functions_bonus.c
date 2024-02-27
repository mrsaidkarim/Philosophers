/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:23:51 by skarim            #+#    #+#             */
/*   Updated: 2024/02/26 14:10:57 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_usleep(int duration)
{
	long	time_start;

	time_start = get_time();
	while (get_time() - time_start < duration)
	{
		usleep(100);
	}
}

void	ft_print(t_philo *philo, char *msg)
{
	unsigned long	time;

	time = get_time() - philo->data->start_time;
	sem_wait(philo->data->writing_sem);
	printf("%ld %d %s\n", time, philo->id, msg);
	sem_post(philo->data->writing_sem);
}

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->fork_sem);
	ft_print(philo, "has taken a fork");
	sem_wait(philo->data->fork_sem);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->last_eating = get_time();
	philo->is_eating = 1;
	philo->nbr_meals++;
	ft_usleep(philo->data->time_eat);
	sem_post(philo->data->fork_sem);
	sem_post(philo->data->fork_sem);
}

void	*ft_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	while (1)
	{
		if ((get_time() - philo->last_eating) > philo->data->time_die
			&& !philo->is_eating)
		{
			sem_wait(philo->data->writing_sem);
			printf("%ld %d died\n",
				get_time() - philo->data->start_time, philo->id);
			exit(1);
		}
	}
	return (NULL);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	monitor_thread;

	philo->last_eating = get_time();
	pthread_create(&monitor_thread, NULL, ft_monitor, philo);
	while (1)
	{
		ft_eat(philo);
		if (philo->nbr_meals >= philo->data->nbr_times_eat
			&& philo->data->nbr_times_eat != -1)
			exit(0);
		philo->is_eating = 0;
		ft_print(philo, "is sleeping");
		ft_usleep(philo->data->time_sleep);
		ft_print(philo, "is thinking");
	}
	pthread_join(monitor_thread, NULL);
}
