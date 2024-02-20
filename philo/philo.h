/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:33:47 by skarim            #+#    #+#             */
/*   Updated: 2024/02/18 19:26:24 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_data	t_data;

typedef enum e_mutex_opr
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY
}	t_mutex_opr;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				nbr_meals;
	long			last_eating;
	int				is_eating;
	int				ffork_index;
	int				sfork_index;
	pthread_t		thread;
	pthread_mutex_t	philo_mtx;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_times_eat;
	int				end;
	int				dead_flag;
	long			start_time;
	pthread_mutex_t	writing;
	pthread_mutex_t	data_mtx;
	t_philo			*philos;
	t_fork			*forks;
}	t_data;

long int	ft_atoi(char *str);
int			ft_error_message(char *str);
int			ft_mutex_handler(pthread_mutex_t *mutex, t_mutex_opr mutex_opr);
int			ft_init(t_data *data);
int			ft_start(t_data *data);
void		ft_destroy_philos(t_data *data, int nbr);
void		ft_destroy_forks(t_data *data, int nbr);
void		ft_print(t_philo *philo, char *msg, int unlock);
void		*routine(void *arg);
long		get_time(void);
int			get_with_mutex(pthread_mutex_t *mtx, int *val);
void		set_with_mutex(pthread_mutex_t *mtx, int *val, int new);
long		getlong_with_mutex(pthread_mutex_t *mtx, long *val);
void		setlong_with_mutex(pthread_mutex_t *mtx, long *val, long new);

#endif