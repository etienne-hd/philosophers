/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:06 by ehode             #+#    #+#             */
/*   Updated: 2025/11/14 17:42:47 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H
# include "philo.h"
# include <stddef.h>

typedef struct s_simulation
{
	pthread_mutex_t	lock;
	t_philo			**philos;
	size_t			start_at;
	int				is_finish;
	int				number_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			nb_of_times_each_philo_must_eat;
}				t_simulation;
void	simulation_exec_took(t_simulation *simulation, size_t begin_ts);
void	simulation_destroy(t_simulation **simulation);
int		get_simulation_state(t_simulation *sim);

#endif