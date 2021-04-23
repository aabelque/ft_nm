/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:00:44 by aabelque          #+#    #+#             */
/*   Updated: 2021/04/23 12:24:03 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint8_t		*get_ppc(void)
{
	static uint8_t	ppc = 0;

	return (&ppc);
}

void				set_ppc(uint8_t ppc)
{
	*get_ppc() = ppc;
}

uint32_t			ppc32(uint32_t x)
{
	uint8_t			ppc;

	ppc = *get_ppc();
	if (ppc)
		return (swap32(x));
	return (x);
}

uint64_t			ppc64(uint64_t x)
{
	uint8_t			ppc;

	ppc = *get_ppc();
	if (ppc)
		return (swap64(x));
	return (x);
}

uint32_t			swap32(uint32_t x)
{
	x = ((x << 8) & 0xFF00FF00 ) | ((x >> 8) & 0xFF00FF ); 
    return (x << 16) | (x >> 16);
}

uint64_t			swap64(uint64_t x)
{
    x = ((x << 8) & 0xFF00FF00FF00FF00ULL ) | ((x >> 8) & 0x00FF00FF00FF00FFULL );
    x = ((x << 16) & 0xFFFF0000FFFF0000ULL ) | ((x >> 16) & 0x0000FFFF0000FFFFULL );
    return (x << 32) | (x >> 32);
}

uint64_t			swap_bytes(uint64_t x)
{
	uint64_t	y;
	char		*ptr_x, *ptr_y;

	ptr_x = (char *)&x;
	ptr_y = (char *)&y;
	for (int i = 0; i < sizeof(uint64_t); i++) {
		ptr_y[i] = ptr_x[sizeof(uint64_t) - 1 - i];
	}
	return (y);
	/* x = (x << 32) | (x >> 32); */
    /* x = ((x << 16) & 0xFFFF0000FFFF0000ULL ) | ((x >> 16) & 0x0000FFFF0000FFFFULL ); */
    /* return (((x << 8) & 0xFF00FF00FF00FF00ULL ) | ((x >> 8) & 0x00FF00FF00FF00FFULL )); */
    /* return (x << 32) | (x >> 32); */
}
