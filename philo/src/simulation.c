/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:32:48 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 10:01:50 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_simulation	*simulation;

	if (argc < 5 || argc > 6)
	{
		write(2, "Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", 128);
		return (1);
	}
	simulation = parse(argc, argv);
	free(simulation);
}