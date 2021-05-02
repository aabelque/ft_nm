/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:59 by azziz             #+#    #+#             */
/*   Updated: 2021/05/02 18:46:37 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		print_archive(char *bin)
{
	write(1, "\n", 1);
	while (*bin != '/')
	{
		printc(*bin);
		bin++;
	}
	write(1, ":\n", 3);
}

int		ar_elf(char *ptr, char *offset, char *bin, int opt)
{
	struct ar_hdr	*ar;
	int				i = 16;

	ar = (struct ar_hdr *)(ptr + SARMAG);
	ptr += SARMAG + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	while (--i >= 0 && ptr[i] == ' ');
	if (i == 1 && ptr[0] == '/' && ptr[1] == '/')
	{
		ar = (struct ar_hdr *)ptr;
		ptr += sizeof(*ar) + ft_atoi(ar->ar_size);
	}
	else if (i > 0 && ptr[0] == '/')
		prints("XXX\n");
    else if (i != 0 || ptr[0] != '/')
    {
		prints("YYY\n");
    	/* if (header->ar_name[i] == '/') */
    	/* 	i--; */
    	/* if ((entry->filename = strndup(header->ar_name, i + 1)) == NULL) */
    	/* { */
    	/* 	fprintf(stderr, "malloc has returned NULL\n"); */
    	/* 	return (-1); */
    	/* } */
    }
	while (ptr < offset)
	{
		ar = (struct ar_hdr *)ptr;
		printc('\n');
		prints(ar->ar_name);
		printc('\n');
		print_archive(ar->ar_name);
		if (nm_elf(ptr + sizeof(*ar), offset, bin, opt))
			return (ft_perror("Corrupted\n", 0));
		ptr += sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	}
	return (EXIT_SUCCESS);
}
