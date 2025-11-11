/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:06:21 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 15:08:34 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include <pthread.h>

int	get_simulation_state(t_simulation *sim)
{
	int	state;

	pthread_mutex_lock(&sim->lock);
	state = sim->is_finish;
	pthread_mutex_unlock(&sim->lock);
	return (state);
}