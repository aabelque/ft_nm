/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 21:33:10 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/31 13:48:20 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_archive(char *obj, char *bin)
{
	write(1, "\n", 1);
	prints(bin);
	write(1, "(", 1);
	prints(obj);
	write(1, "):\n", 3);
}

int		ar(void *ptr, void *offset, char *bin)
{
	size_t			len;
	struct ar_hdr	*ar;
	char			*str;

	ptr += SARMAG;
	ar = (struct ar_hdr *)ptr;
	ptr += ft_atoi(ar->ar_size) + sizeof(*ar);
	if (check_offset(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	while (ptr < offset)
	{
		ar = (struct ar_hdr *)ptr;
		if (ar->ar_size <= 0)
			return (EXIT_FAILURE);
		str = ptr + sizeof(struct ar_hdr);
		len = ft_strlen(str);
		while (!str[len++])
			;
		print_archive(str, bin);
		if (nm(ptr + sizeof(struct ar_hdr) + (len - 1), offset, bin))
			return (ft_perror("Corrupted\n", 0));
		ptr += ft_atoi(ar->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
