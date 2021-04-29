/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:59 by azziz             #+#    #+#             */
/*   Updated: 2021/04/29 19:34:49 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		print_archive(char *obj, char *bin)
{
	write(1, "\n", 1);
	prints(bin);
	write(1, "(", 1);
	prints(obj);
	write(1, "):\n", 3);
}

int		ar_elf(char *ptr, char *offset, char *bin, int opt)
{
	size_t			len;
	struct ar_hdr	*ar;
	char			*str;
	int				i = 0;

	ptr += SARMAG;
	ar = (struct ar_hdr *)ptr;
	ptr += ft_atoi(ar->ar_size) + sizeof(*ar);
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	char s[16];
	while (ptr < offset)
	{
		ar = (struct ar_hdr *)ptr;
		while (ar->ar_name[i] != '/') {
			s[i] = ar->ar_name[i];
			i++;
		}
		prints(s);
		if (ar->ar_size <= 0)
			return (EXIT_FAILURE);
		str = ptr + sizeof(struct ar_hdr);
		len = ft_strlen(str);
		while (!str[len++])
			;
		print_archive(s, bin);
		if (nm_elf(s, offset, bin, opt))
			return (ft_perror("Corrupted\n", 0));
		ptr += ft_atoi(ar->ar_size) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
