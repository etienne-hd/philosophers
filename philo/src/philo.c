/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:59:24 by ehode             #+#    #+#             */
/*   Updated: 2025/11/12 15:26:40 by ehode            ###   ########.fr       */
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

static int	philo_next_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->state == THINKING)
	{
		philo->state = EAT;
		philo->eat_count++;
		philo->next_state_in = get_timestamp() + philo->simulation->time_to_eat;
		philo->last_meal = get_timestamp();
	}
	else if (philo->state == EAT)
	{
		philo->fork = 0;
		pthread_mutex_lock(&philo->left_philo->lock);
		philo->left_philo->fork = 0;
		pthread_mutex_unlock(&philo->left_philo->lock);
		philo->state = SLEEP;
		if (philo->simulation->nb_of_times_each_philo_must_eat != -1 &&
			philo->eat_count >= philo->simulation->nb_of_times_each_philo_must_eat)
		{
			pthread_mutex_unlock(&philo->lock);
			return (1);
		}
		philo->next_state_in = get_timestamp() + philo->simulation->time_to_sleep;
	}
	else if (philo->state == SLEEP)
		philo->state = THINKING;
	pthread_mutex_unlock(&philo->lock);
	philo_display(philo, NULL, 1);
	return (0);
}

static int	philo_check_lifetime(t_philo *philo)
{
	int	is_died;
	
	is_died = 0;
	pthread_mutex_lock(&philo->simulation->lock);
	if (philo->simulation->is_finish)
		is_died = 1;
	pthread_mutex_unlock(&philo->simulation->lock);
	if (is_died)
		return (1);

	pthread_mutex_lock(&philo->lock);
	if (
		(philo->last_meal != 0 && philo->last_meal + philo->simulation->time_to_die <= get_timestamp())
		|| (philo->last_meal == 0 && philo->simulation->start_at + philo->simulation->time_to_die <= get_timestamp())
	)
	{
		is_died = 1;
		pthread_mutex_lock(&philo->simulation->lock);
		philo_display(philo, "died", 0);
		philo->simulation->is_finish = 1;
		pthread_mutex_unlock(&philo->simulation->lock);
	}
	pthread_mutex_unlock(&philo->lock);
	return (is_died);
}

static int	philo_lock_fork(t_philo *philo, int is_left)
{
	t_philo	*target_philo;

	if (is_left)
		target_philo = philo->left_philo;
	else
		target_philo = philo;
	while (1)
	{
		if (philo_check_lifetime(philo))
			return (1);
		pthread_mutex_lock(&target_philo->lock);
		if (target_philo->fork == 0)
		{
			target_philo->fork = 1;
			pthread_mutex_unlock(&target_philo->lock);
			break ;
		}
		pthread_mutex_unlock(&target_philo->lock);
	}
	if (is_left)
		philo_display(philo, "has taken left fork", 1);
	else
		philo_display(philo, "has taken right fork", 1);
	return (0);
}

void	*philo_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_check_lifetime(philo))
			break ;
		if (philo->state == THINKING)
		{
			if (philo_lock_fork(philo, 0))
				break ;
			if (philo_lock_fork(philo, 1))
				break ;
			philo_next_state(philo);
		}
		if (get_timestamp() >= philo->next_state_in)
			if (philo_next_state(philo))
				break;
		//usleep(50);
	}
	return (NULL);
}
