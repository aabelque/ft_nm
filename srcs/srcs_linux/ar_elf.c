/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:59 by azziz             #+#    #+#             */
/*   Updated: 2021/05/03 11:42:15 by azziz            ###   ########.fr       */
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

static char		*get_name(char *strtab, int str_idx, int size) {

	int			idx;
	char		*name;

	idx = 0;
	name = NULL;
	prints(&strtab[str_idx]);
	return NULL;
	while (str_idx + idx < size - 2
			&& ft_strncmp(&strtab[str_idx + idx], "//\n", 3))
		idx++;
	if (ft_strncmp(&strtab[str_idx + idx], "/\n", 2))
		prints("Error\n");
	else if ((name = ft_strndup(&strtab[str_idx], idx)) == NULL)
		prints("Error Malloc\n");
	return (name);
}

int				ar_elf(char *ptr, char *offset, char *bin, int opt)
{
	int				i, j, str_idx, size;
	char			*strtab, *name = NULL;
	struct ar_hdr	*ar;

	ar = (struct ar_hdr *)(ptr + SARMAG);
	ptr += SARMAG + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	while (ptr < offset)
	{
		i = 16;
		j = 0;
		while (--i >= 0 && ptr[i] == ' ');
		if (i == 1 && ptr[0] == '/' && ptr[1] == '/')
		{
			strtab = ptr;
			ar = (struct ar_hdr *)ptr;
			size = ft_atoi(ar->ar_size);
			ptr += sizeof(*ar) + size;
		}
		else if ((i > 0 && ptr[0] == '/') || (i != 0 || ptr[0] != '/'))
		{
			while (ar->ar_name[j] != '/')
				j++;
			if (!j)
			{
				str_idx = ft_atoi(ar->ar_name + 1);
				name = get_name(strtab, str_idx, size);
				/* prints(name); */
			}
		}
		/* { */
			/* while (ar->ar_name[j] != '/') */
			/* 	j++; */
			/* ft_putnbr(j); */
			/* printc('\n'); */
			/* if (header->ar_name[i] == '/') */
			/* 	i--; */
			/* if ((entry->filename = strndup(header->ar_name, i + 1)) == NULL) */
			/* { */
			/* 	fprintf(stderr, "malloc has returned NULL\n"); */
			/* 	return (-1); */
			/* } */
		/* } */
		/* ar = (struct ar_hdr *)ptr; */
		/* printc('\n'); */
		/* prints(ar->ar_name); */
		/* printc('\n'); */
		/* print_archive(ar->ar_name); */
		/* if (nm_elf(ptr + sizeof(*ar), offset, bin, opt)) */
		/* 	return (ft_perror("Corrupted\n", 0)); */
		ptr += sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	}
	return (EXIT_SUCCESS);
}
