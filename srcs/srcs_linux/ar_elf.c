/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:59 by azziz             #+#    #+#             */
/*   Updated: 2021/05/02 17:17:51 by azziz            ###   ########.fr       */
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
	char			*str, *strtab;
	int				i = 16;

	/* ptr += SARMAG; */
	ar = (struct ar_hdr *)(ptr + SARMAG);
	/* prints(ar->ar_name); */
	/* ar = (struct ar_hdr *)((char*)ptr + sizeof(*ar)); */
	/* prints(&ptr[100]); */
	/* prints(str); */
	ptr += SARMAG + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	while (--i >= 0 && ptr[i] == ' ');
	if (i == 1 && ptr[0] == '/' && ptr[1] == '/')
	{
		/* strtab = ptr; */
		ar = (struct ar_hdr *)ptr;
		ptr += sizeof(*ar) + ft_atoi(ar->ar_size);
		prints(ptr);
	}
	else if (i > 0 && ptr[0] == '/')
		prints(ptr);
	else if (i != 0 || ptr[0] != '/') {
		if (ptr[i] == '/')
			i--;
		prints(ptr);
	}
	while (ptr < offset)
	{
		ar = (struct ar_hdr *)ptr;
		/* ptr = ptr + sizeof(struct ar_hdr); */
		if (nm_elf(ptr + sizeof(*ar), offset, bin, opt))
			return (ft_perror("Corrupted\n", 0));
		prints("\n");
		ptr += sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
		/* ptr += ft_atoi(ar->ar_size) + sizeof(struct ar_hdr); */
		/* prints(str); */
	}
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
