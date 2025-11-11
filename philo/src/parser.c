/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:37:59 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 11:36:10 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int	ft_philo_atoi(char *s)
{
	size_t		i;
	long int	nb;

	nb = 0;
	i = 0;
	while (s[i] == ' ' && (s[i] >= 8 && s[i] <= 13))
		i++;
	if (s[i] == '+' || (s[i] == '-' && s[i + 1] == '0'))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + s[i++] - '0';
		if (nb > 2147483647)
			return (-1);
	}
	while (s[i] == ' ' && (s[i] >= 8 && s[i] <= 13))
		i++;
	if (s[i] != '\0')
		return (-1);
	return (nb);
}

static int	init_settings(int argc, char **argv, t_simulation *simulation)
{
	simulation->number_of_philo = ft_philo_atoi(argv[1]);
	simulation->time_to_die = ft_philo_atoi(argv[2]);
	simulation->time_to_eat = ft_philo_atoi(argv[3]);
	simulation->time_to_sleep = ft_philo_atoi(argv[4]);
	if (argc == 6)
		simulation->nb_of_times_each_philo_must_eat = ft_philo_atoi(argv[5]);
	else
		simulation->nb_of_times_each_philo_must_eat = -1;
	if (
		(argc == 6 && simulation->nb_of_times_each_philo_must_eat == -1)
		|| simulation->number_of_philo == -1
		|| simulation->time_to_die == -1
		|| simulation->time_to_eat == -1
		|| simulation->time_to_sleep == -1
	)
	{
		write(2, "Error\nInvalid input.\n", 21);
		return (1);
	}
	return (0);
}

static void	init_philos_fork(t_simulation *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->number_of_philo)
	{
		if (sim->number_of_philo == 1)
			sim->philos[i]->left_fork = NULL;
		else if (sim->number_of_philo == i + 1)
			sim->philos[i]->left_fork = &sim->philos[0]->right_fork;
		else
			sim->philos[i]->left_fork = &sim->philos[i + 1]->right_fork;
		pthread_mutex_lock(&sim->philos[i]->right_fork);
		i++;
	}
}
static int	init_philos(t_simulation *sim)
{
	size_t	i;

	i = 0;
	while (i < sim->number_of_philo)
	{
		sim->philos[i] = philo_new(sim, i + 1);
		if (!sim->philos[i])
		{
			write(2, "Error\nAllocation failed.\n", 25);
			return (1);
		}
		i++;
	}
	sim->philos[i]->state = EAT;
	init_philos_fork(sim);
	return (0);
}

t_simulation	*parse(int argc, char **argv)
{
	t_simulation	*sim;

	sim = ft_calloc(1, sizeof(t_simulation));
	if (!sim)
	{
		write(2, "Error\nAllocation failed.\n", 25);
		return (NULL);
	}
	if (init_settings(argc, argv, sim))
	{
		simulation_destroy(&sim);
		return (NULL);
	}
	sim->philos = ft_calloc(sim->number_of_philo, sizeof(t_philo *));
	if (!sim->philos)
	{
		write(2, "Error\nAllocation failed.\n", 25);
		simulation_destroy(&sim);
		return (NULL);
	}
	if (init_philos(sim))
		simulation_destroy(&sim);
	return (sim);
}
