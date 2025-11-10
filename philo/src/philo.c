/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:17:51 by ehode             #+#    #+#             */
/*   Updated: 2025/11/10 14:03:00 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "parser.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void	show_config(t_philo *config)
{
	if (!config)
		return ;
	printf("--- CONFIG ---\n");
	printf("number_of_philo -> %d\n", config->number_of_philo);
	printf("time_to_die -> %d\n", config->time_to_die);
	printf("time_to_eat -> %d\n", config->time_to_eat);
	printf("time_to_sleep -> %d\n", config->time_to_sleep);
	printf("nb_of_times_each_philo_must_eat -> %d\n", config->nb_of_times_each_philo_must_eat);
}

int	main(int argc, char **argv)
{
	t_philo	*config;

	if (argc < 5 || argc > 6)
	{
		write(2, "USAGE: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", 129);
		return (1);
	}
	config = parse(argc, argv);
	if (!config)
		return (1);
	show_config(config);
	free(config);
	return (0);
}