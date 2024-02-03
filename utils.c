/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:19:08 by skarim            #+#    #+#             */
/*   Updated: 2024/02/03 15:55:01 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] == '0' && i != ft_strlen(str) - 1)
		i++;
	return (i);
}

long int	ft_atoi(char *str)
{
	long int	n;
	int			i;
	int			count;

	i = 0;
	n = 0;
	count = 0;
	i = ft_skip_spaces(str);
	while (str[i])
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
	return (0);
}
