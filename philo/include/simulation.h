/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:06 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 10:00:12 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

#include "philo.h"
typedef struct s_simulation
{
	t_philo	*philos;
	int		number_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_of_times_each_philo_must_eat;
}				t_simulation;

#endif