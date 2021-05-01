/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:59 by azziz             #+#    #+#             */
/*   Updated: 2021/05/01 18:31:43 by azziz            ###   ########.fr       */
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
	size_t			len, coff;
	struct ar_hdr	*ar;
	char			*str;
	int				i = 16;

	ptr += SARMAG;
	ar = (struct ar_hdr *)ptr;
	prints(ar->ar_name);
	ar = (struct ar_hdr *)((char*)ptr + sizeof(*ar));
	prints(ptr + 1);
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	/* while (--i >= 0 && ar->ar_name[i] == ' '); */
	/* if (i == 1 && ar->ar_name[0] == '/' && ar->ar_name[1] == '/') */
	/* 	prints(ar->ar_name); */
	/* else if (i > 0 && ar->ar_name[0] == '/') */
	/* 	prints(ar->ar_name); */
	/* else if (i != 0 || ar->ar_name[0] != '/') { */
	/* 	if (ar->ar_name[i] == '/') */
	/* 		i--; */
	/* 	prints(ar->ar_name); */
	/* } */
	/* prints(ar->ar_name); */
	/* while (ptr < offset) */
	/* { */
	/* 	ar = (struct ar_hdr *)ptr; */
	/* 	if (ar->ar_size <= 0) */
	/* 		return (EXIT_FAILURE); */
	/* 	str = ptr + sizeof(struct ar_hdr); */
	/* 	len = ft_strlen(str); */
	/* 	while (!str[len++]) */
	/* 		; */
	/* 	print_archive(str, bin); */
	/* 	if (nm_elf(ptr + sizeof(struct ar_hdr) + (len - 1), offset, bin, opt)) */
	/* 		return (ft_perror("Corrupted\n", 0)); */
	/* 	ptr += ft_atoi(ar->ar_size) + sizeof(struct ar_hdr); */
	/* } */
	return (EXIT_SUCCESS);
}
