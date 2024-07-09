/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:49:03 by mhiguera          #+#    #+#             */
/*   Updated: 2024/07/09 12:08:01 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stddef.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
/*
 * Reserva memoria con malloc y la llena de 0 con bzero.
*/
