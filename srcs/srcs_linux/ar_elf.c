/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_elf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azziz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 14:42:59 by azziz             #+#    #+#             */
/*   Updated: 2021/05/03 20:03:23 by azziz            ###   ########.fr       */
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
	write(1, ":\n", 2);
}

static char		*get_name(char **strtab, int str_idx, int size)
{

	int			idx;
	char		*name, *tmp;

	idx = 0;
	name = NULL;
	while (!('a' <= **strtab && **strtab <= 'z'))
		(*strtab)++;
	tmp = *strtab;
	while (*tmp != '/')
		tmp++;
	idx = tmp - *strtab;
	name = ft_strndup(*strtab, idx);
	*strtab += idx;
	return (name);
}

int				ar_elf(char *ptr, char *offset, char *bin, int opt)
{
	int				i, j, str_idx, size;
	char			*strtab, *name;
	struct ar_hdr	*ar;

	ar = (struct ar_hdr *)(ptr + SARMAG);
	ptr += SARMAG + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	if (check_offset_elf(ptr, offset))
		return (ft_perror("Corrupted file\n", 0));
	i = 16;
	while (--i >= 0 && ptr[i] == ' ');
	if (i == 1 && ptr[0] == '/' && ptr[1] == '/')
	{
		strtab = ptr;
		ar = (struct ar_hdr *)ptr;
		size = ft_atoi(ar->ar_size);
		ptr += sizeof(*ar) + size;
	}
	while (ptr < offset)
	{
		j = 0;
		name = NULL;
		ar = (struct ar_hdr *)ptr;
		while (ar->ar_name[j++] != '/')
				;
		if (!j)
		{
			str_idx = ft_atoi(ar->ar_name + 1);
			name = get_name(&strtab, str_idx, size);
		}
		(name) ? print_archive(name) : print_archive(ar->ar_name);
		if (nm_elf(ptr + sizeof(*ar), offset, bin, opt))
			return (ft_perror("Corrupted\n", 0));
		ptr += sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
		free(name);
	}
	return (EXIT_SUCCESS);
}
