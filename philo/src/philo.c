/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:59:24 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 16:06:14 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "simulation.h"
#include "utils.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

t_philo	*philo_new(t_simulation *simulation, size_t id)
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->simulation = simulation;
	return (philo);
}

static void	philo_display(t_philo *philo, const char *s)
{
	size_t	current_timestamp;
	current_timestamp = get_timestamp();
	pthread_mutex_lock(&philo->simulation->lock);
	printf("%lu %lu %s\n", current_timestamp - philo->simulation->start_at, philo->id, s);
	pthread_mutex_unlock(&philo->simulation->lock);
}

static void philo_next_state(t_philo *philo)
{
	if (philo->state == EAT)
	{
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		philo->next_state_in = get_timestamp() + philo->simulation->time_to_sleep;
		philo->state = SLEEP;
		philo_display(philo, "is sleeping");
	}
	else if (philo->state == SLEEP)
	{
		philo->next_state_in = 0;
		philo->state = THINKING;
		philo_display(philo, "is thinking");
	}
	else if (philo->state == THINKING)
	{
		philo->next_state_in = get_timestamp() + philo->simulation->time_to_eat;
		philo->state = EAT;
		philo->last_meal = get_timestamp();
		philo_display(philo, "is eating");
	}
}

static int	philo_is_dead(t_philo *philo)
{
	size_t	current_timestamp;

	current_timestamp = get_timestamp();
	if (get_simulation_state(philo->simulation))
		return (1);
	if (
		(philo->last_meal != 0 && current_timestamp > philo->last_meal + philo->simulation->time_to_die)
		|| (philo->last_meal == 0 && current_timestamp > philo->simulation->start_at + philo->simulation->time_to_die)
	)
	{
		pthread_mutex_lock(&philo->simulation->lock);
		philo->simulation->is_finish = 1;
		pthread_mutex_unlock(&philo->simulation->lock);
		philo_display(philo, "died");
		return (1);
	}
	return (0);
}

void	*philo_start(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)//(!get_simulation_state(philo->simulation))
	{
		if (philo_is_dead(philo))
			break;
		if (philo->state == THINKING)
		{
			pthread_mutex_lock(&philo->right_fork);
			if (philo_is_dead(philo))
				break;
			philo_display(philo, "has taken right fork");
			pthread_mutex_lock(philo->left_fork);
			if (philo_is_dead(philo))
				break;
			philo_display(philo, "has taken left fork");
			philo_next_state(philo);
		}
		else if (philo->next_state_in <= get_timestamp())
			philo_next_state(philo);
		usleep(500);
	}
	return (NULL);
}
