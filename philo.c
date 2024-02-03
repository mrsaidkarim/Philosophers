/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarim <skarim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:31:31 by skarim            #+#    #+#             */
/*   Updated: 2024/02/03 15:53:54 by skarim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_valid_input(int ac, char **av, t_args *args)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (-1);
	i = 1;
	while (i < 5)
	{
		if (ft_atoi(av[i]) == -1 || ft_atoi(av[i]) == 0)
			return (-1);
		i++;
	}
	if (ac == 6)
		if (ft_atoi(av[5]) == -1)
			return (-1);
	args->nbr_philos = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	args->nbr_times_eat = -1;
	if (ac == 6)
		args->nbr_times_eat = ft_atoi(av[5]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (ft_valid_input(argc, argv, &args) == -1)
		return (ft_error_message("wrong arguments!"));
	return (0);
}
