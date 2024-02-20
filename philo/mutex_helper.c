/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:10:51 by skarim            #+#    #+#             */
/*   Updated: 2024/02/18 22:49:08 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_with_mutex(pthread_mutex_t *mtx, int *val)
{
	int	value;

	ft_mutex_handler(mtx, LOCK);
	value = *val;
	ft_mutex_handler(mtx, UNLOCK);
	return (value);
}

void	set_with_mutex(pthread_mutex_t *mtx, int *val, int new)
{
	ft_mutex_handler(mtx, LOCK);
	*val = new;
	ft_mutex_handler(mtx, UNLOCK);
}

long	getlong_with_mutex(pthread_mutex_t *mtx, long *val)
{
	long	value;

	ft_mutex_handler(mtx, LOCK);
	value = *val;
	ft_mutex_handler(mtx, UNLOCK);
	return (value);
}

void	setlong_with_mutex(pthread_mutex_t *mtx, long *val, long new)
{
	ft_mutex_handler(mtx, LOCK);
	*val = new;
	ft_mutex_handler(mtx, UNLOCK);
}
