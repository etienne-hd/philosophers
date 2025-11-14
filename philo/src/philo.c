/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:59:24 by ehode             #+#    #+#             */
/*   Updated: 2025/11/14 17:36:09 by ehode            ###   ########.fr       */
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
	philo->sim = simulation;
	return (philo);
}

static int	philo_check_status(t_philo *philo)
{
	int	is_finish;

	if (philo->eat_count >= philo->sim->nb_of_times_each_philo_must_eat
		&& philo->sim->nb_of_times_each_philo_must_eat != 0)
		return (1);
	pthread_mutex_lock(&philo->sim->lock);
	is_finish = philo->sim->is_finish;
	pthread_mutex_unlock(&philo->sim->lock);
	if (is_finish)
		return (1);
	if ((philo->last_meal != 0 && get_timestamp()
			>= philo->last_meal + philo->sim->time_to_die * 1000)
		|| (philo->last_meal == 0 && get_timestamp()
			>= philo->sim->start_at + philo->sim->time_to_die * 1000))
	{
		pthread_mutex_lock(&philo->sim->lock);
		philo_display(philo, "died", 1);
		philo->sim->is_finish = 1;
		pthread_mutex_unlock(&philo->sim->lock);
		return (1);
	}
	return (0);
}

static int	philo_lock_fork(t_philo *philo, t_fork *fork)
{
	while (1)
	{
		if (philo_check_status(philo))
			return (1);
		pthread_mutex_lock(&fork->lock);
		if (fork->is_availaible)
		{
			fork->is_availaible = 0;
			break ;
		}
		pthread_mutex_unlock(&fork->lock);
		usleep(1);
	}
	pthread_mutex_unlock(&fork->lock);
	philo_display(philo, "has taken a fork", 0);
	return (0);
}

static void	next_state(t_philo *philo)
{
	if (philo->state == THINKING)
	{
		philo->last_meal = get_timestamp();
		philo->state = EAT;
		philo->next_state_in = get_timestamp() + philo->sim->time_to_eat * 1000;
	}
	else if (philo->state == EAT)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		philo->left_fork->is_availaible = 1;
		pthread_mutex_unlock(&philo->left_fork->lock);
		pthread_mutex_lock(&philo->right_fork.lock);
		philo->right_fork.is_availaible = 1;
		pthread_mutex_unlock(&philo->right_fork.lock);
		philo->eat_count++;
		philo->state = SLEEP;
		philo->next_state_in = get_timestamp()
			+ philo->sim->time_to_sleep * 1000;
		if (philo->sim->nb_of_times_each_philo_must_eat
			!= 0 && philo_check_status(philo))
			return ;
	}
	else if (philo->state == SLEEP)
		philo->state = THINKING;
	philo_display(philo, NULL, 0);
}

void	*philo_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_check_status(philo))
			break ;
		if (philo->state == THINKING)
		{
			if (philo_lock_fork(philo, philo->left_fork)
				|| philo_lock_fork(philo, &philo->right_fork))
				break ;
			next_state(philo);
		}
		else if (get_timestamp() >= philo->next_state_in)
			next_state(philo);
		usleep(1);
	}
	return (NULL);
}
