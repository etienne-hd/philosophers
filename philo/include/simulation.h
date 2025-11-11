/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:06 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 15:08:45 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

#include "philo.h"
#include <stddef.h>
typedef struct s_simulation
{
	pthread_mutex_t	lock;
	t_philo			**philos;
	size_t			start_at;
	int				is_finish;
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_times_each_philo_must_eat;
}				t_simulation;
void	simulation_destroy(t_simulation **simulation);
int		get_simulation_state(t_simulation *sim);

#endif