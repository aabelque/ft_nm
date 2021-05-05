/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:00:44 by aabelque          #+#    #+#             */
/*   Updated: 2021/05/05 14:59:17 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t			reverse32(uint32_t x, size_t size, short reverse) {
	int				i = 0;
	uint32_t		y = 0;
	unsigned char	*ptr_x, *ptr_y;

	if (!reverse)
		return (x);
	ptr_x = (unsigned char *)&x;
	ptr_y = (unsigned char *)&y;
	while (--size)
		ptr_y[i++] = ptr_x[size];
	ptr_y[i++] = ptr_x[size];
	return (y);
}

uint64_t			reverse64(uint64_t x, size_t size, short reverse) {
	int				i = 0;
	uint64_t		y = 0;
	unsigned char	*ptr_x, *ptr_y;

	if (!reverse)
		return (x);
	ptr_x = (unsigned char *)&x;
	ptr_y = (unsigned char *)&y;
	while (--size)
		ptr_y[i++] = ptr_x[size];
	ptr_y[i++] = ptr_x[size];
	return (y);
}

int					get_endianess(void) {
	int		value = 1;
	return ((int)(((char *)&value)[0]));
}

short				should_reverse(short file, short machine) {

	if (file == BIG && !machine)
		return (0);
	else if (file == BIG && machine)
		return (1);
	else if (file == LITTLE && machine)
		return (0);
	else if (file == LITTLE && !machine)
		return (1);
}
