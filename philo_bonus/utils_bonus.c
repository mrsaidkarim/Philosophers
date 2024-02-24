/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:21:18 by skarim            #+#    #+#             */
/*   Updated: 2024/02/20 19:30:15 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_skip_spaces(char *str, int *end)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] == '0' && i != ft_strlen(str) - 1 && str[i+1] != ' ')
		i++;
	*end = ft_strlen(str) - 1;
	while (str[*end] == 32 || (str[*end] >= 9 && str[*end] <= 13))
		(*end)--;
	return (i);
}

long int	ft_atoi(char *str)
{
	long int	n;
	int			i;
	int			count;
	int			end;

	i = 0;
	n = 0;
	count = 0;
	i = ft_skip_spaces(str, &end);
	while (i < end + 1)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			n = n * 10 + (str[i] - '0');
			count++;
		}
		else
			return (-1);
		i++;
	}
	if (n > INT_MAX || count > 10 || count == 0)
		return (-1);
	return (n);
}

int	ft_error_message(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
