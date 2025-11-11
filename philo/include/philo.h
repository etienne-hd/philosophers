/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:57:56 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 13:37:46 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
#include <stddef.h>

typedef struct s_simulation	t_simulation;
typedef enum e_state
{
	EAT,
	THINKING,
	SLEEP,
}			t_state;
typedef struct s_philo
{
	t_simulation	*simulation;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	size_t			id;
	pthread_t		thread;
	t_state			state;
	size_t			next_state_in;
	size_t			last_meal;
}				t_philo;
t_philo	*philo_new(t_simulation *simulation, size_t id);
void	*philo_start(void *arg);

#endif