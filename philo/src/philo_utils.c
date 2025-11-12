/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 10:18:02 by ehode             #+#    #+#             */
/*   Updated: 2025/11/12 17:02:25 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "simulation.h"
#include <stdio.h>

void	philo_display(t_philo *philo, const char *s, int lock_sim)
{
	const char	*message;

	if (s)
		message = s;
	else if (philo->state == THINKING)
		message = "is thinking";
	else if (philo->state == EAT)
		message = "is eating";
	else if (philo->state == SLEEP)
		message = "is sleeping";
	if (lock_sim)
		pthread_mutex_lock(&philo->simulation->lock);
	if (!philo->simulation->is_finish)
		printf("\e[0;33m%lums\t\e[0;32m%lu \e[0;34m%s\e[0m\n",
			get_timestamp() - philo->simulation->start_at, philo->id, message);
	if (lock_sim)
		pthread_mutex_unlock(&philo->simulation->lock);
}