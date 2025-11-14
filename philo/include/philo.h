/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:57:56 by ehode             #+#    #+#             */
/*   Updated: 2025/11/14 16:21:05 by ehode            ###   ########.fr       */
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
typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				is_availaible;
}					t_fork;
typedef struct s_philo
{
	t_simulation	*simulation;
	size_t			id;
	pthread_t		thread;
	t_state			state;
	size_t			next_state_in;
	size_t			last_meal;
	size_t			eat_count;
	int				is_mutex_init;
	t_fork			*left_fork;
	t_fork			right_fork;
}				t_philo;
void	philo_display(t_philo *philo, const char *s, int is_already_locked);
t_philo	*philo_new(t_simulation *simulation, size_t id);
void	*philo_start(void *arg);

#endif