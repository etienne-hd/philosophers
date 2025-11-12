/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:32:48 by ehode             #+#    #+#             */
/*   Updated: 2025/11/12 19:06:39 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "utils.h"
#include "parser.h"
#include "philo.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	simulation_destroy(t_simulation **simulation)
{
	size_t	i;

	i = 0;
	while ((*simulation)->philos && i < (*simulation)->number_of_philo)
	{
		if (!(*simulation)->philos[i])
			break ;
		if ((*simulation)->philos[i]->is_mutex_init)
			pthread_mutex_destroy(&(*simulation)->philos[i]->lock);
		free((*simulation)->philos[i]);
		i++;
	}
	if ((*simulation)->philos)
		free((*simulation)->philos);
	free(*simulation);
	*simulation = NULL;
}

static void	start_thread(t_philo *philo, int *code)
{
	*code = pthread_create(&philo->thread, NULL, philo_start, philo);
	if (*code != 0)
	{
		write(2, "\e[0;31mError\nUnable to create thread.\e[0m\n", 42);
		pthread_mutex_lock(&philo->simulation->lock);
		philo->simulation->is_finish = 1;
		pthread_mutex_unlock(&philo->simulation->lock);
	}
}

static void	simulation_start(t_simulation *simulation)
{
	size_t	i;
	int		code;

	code = 0;
	simulation->start_at = get_timestamp();
	i = 0;
	while (i < simulation->number_of_philo && code == 0)
	{
		start_thread(simulation->philos[i], &code);
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < simulation->number_of_philo && code == 0)
	{
		start_thread(simulation->philos[i], &code);
		i += 2;
	}
	i = 0;
	while (i < simulation->number_of_philo)
	{
		if (simulation->philos[i]->thread)
			pthread_join(simulation->philos[i]->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_simulation	*simulation;

	if (argc < 5 || argc > 6)
	{
		write(2, "Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", 128);
		return (1);
	}
	simulation = parse(argc, argv);
	if (!simulation)
		return (1);
	simulation_start(simulation);
	simulation_destroy(&simulation);
	return (0);
}