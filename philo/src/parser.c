/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:30:13 by ehode             #+#    #+#             */
/*   Updated: 2025/11/10 14:01:18 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	ft_is_space(char c)
{
	return ((c == ' ') || (c >= 8 && c <= 13));
}

static int	ft_philo_atoi(char *s)
{
	long int	nb;
	size_t		i;

	i = 0;
	nb = 0;
	while (ft_is_space(s[i]))
		i++;
	if (s[i] == '+' || (s[i] == '-' && s[i + 1] == '0'))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + s[i] - '0';
		if (nb > 2147483647)
			return (-1);
		i++;
	}
	while (ft_is_space(s[i]))
		i++;
	if (s[i] != '\0')
		return (-1);
	return ((int)nb);
}

static int	check_config(t_philo *config)
{
	return (
		!(
			config->number_of_philo == -1
			|| config->time_to_die == -1
			|| config->time_to_eat == -1
			|| config->time_to_sleep == -1
		)
	);
}

t_philo	*parse(int argc, char **argv)
{
	t_philo	*config;

	config = malloc(sizeof(t_philo));
	if (!config)
	{
		write(2, "Error\nAllocation failed.\n", 27);
		return (NULL);
	}
	config->number_of_philo = ft_philo_atoi(argv[1]);
	config->time_to_die = ft_philo_atoi(argv[2]);
	config->time_to_eat = ft_philo_atoi(argv[3]);
	config->time_to_sleep = ft_philo_atoi(argv[4]);
	if (argc == 6)
		config->nb_of_times_each_philo_must_eat = ft_philo_atoi(argv[5]);
	else
		config->nb_of_times_each_philo_must_eat = -1;
	if (!check_config(config) || (argc == 6 && ft_philo_atoi(argv[5]) == -1))
	{
		write(2, "Error\nInvalid input.\n", 23);
		free(config);
		return (NULL);
	}
	return (config);
}
