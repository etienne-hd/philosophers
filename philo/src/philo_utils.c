/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:18:02 by ehode             #+#    #+#             */
/*   Updated: 2025/11/14 17:29:08 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "simulation.h"
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>

void	philo_display(t_philo *philo, const char *s, int is_already_locked)
{
	const char	*message;
	size_t		start_ts;
	
	start_ts = get_timestamp();
	if (s)
		message = s;
	else if (philo->state == THINKING)
		message = "is thinking";
	else if (philo->state == EAT)
		message = "is eating";
	else if (philo->state == SLEEP)
		message = "is sleeping";
	if (!is_already_locked)
		pthread_mutex_lock(&philo->simulation->lock);
	if (!philo->simulation->is_finish)
		printf("\e[0;33m%lums\t\e[0;32m%lu \e[0;34m%s\e[0m\n",
			(get_timestamp() - philo->simulation->start_at) / 1000, philo->id, message);
	if (!is_already_locked)
		pthread_mutex_unlock(&philo->simulation->lock);
}