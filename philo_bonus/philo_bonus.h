/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 10:46:16 by skarim            #+#    #+#             */
/*   Updated: 2024/02/24 16:25:23 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <semaphore.h>
#include <unistd.h>
#include <limits.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	int			nbr_meals;
	long		last_eating;
	int			is_eating;
	int			done;
	t_data		*data;
}	t_philo;

typedef struct s_data
{
	int		nbr_philos;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nbr_times_eat;
	long	start_time;
	t_philo	*philos;
	sem_t	*writing_sem;
	sem_t	*fork_sem;
}	t_data;

long int	ft_atoi(char *str);
int			ft_error_message(char *str);
long		get_time(void);
int			ft_init(t_data *data);

#endif