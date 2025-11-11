/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehode <ehode@student.42angouleme.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:47:22 by ehode             #+#    #+#             */
/*   Updated: 2025/11/11 08:50:42 by ehode            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t n, size_t size)
{
	void	*alloc;
	size_t	i;

	if (n == 0 || size == 0)
		return (malloc(0));
	if (n > (size_t)-1 / size)
		return (NULL);
	alloc = malloc(n * size);
	if (!alloc)
		return (NULL);
	i = 0;
	while (i < n * size)
		((char *)alloc)[i++] = 0;
	return (alloc);
}