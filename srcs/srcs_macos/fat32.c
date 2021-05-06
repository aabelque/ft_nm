/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:49:50 by aabelque          #+#    #+#             */
/*   Updated: 2021/05/06 12:12:37 by azziz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			find_arch(cpu_type_t cputype, cpu_subtype_t cpusubtype, char *bin)
{
	if (swap32(cputype) == CPU_TYPE_X86_64)
	{
		prints(bin);
		write(1, " ", 1);
		if (swap32(cpusubtype) == CPU_SUBTYPE_X86_64_H)
			prints("(for architecture x86_64h):\n");
		else
			prints("(for architecture x86_64):\n");
	}
	else if  (swap32(cputype) == CPU_TYPE_I386)
	{
		prints(bin);
		write(1, " ", 1);
		prints("(for architecture i386):\n");
	}
	else if  (swap32(cputype) == CPU_TYPE_POWERPC)
	{
		prints(bin);
		write(1, " ", 1);
		prints("(for architecture ppc):\n");
	}
	else
	{
		prints(bin);
		write(1, " ", 1);
		prints("(for architecture arm64e):\n");
	}
}

int					fat32(void *ptr, void *offset, char *bin)
{
	int					narch, i;
	struct fat_header	*fat_header;
	struct fat_arch		*arch;

	i = 0;
	fat_header = (struct fat_header *)ptr;
	narch = swap32(fat_header->nfat_arch);
	arch = (void *)fat_header + sizeof(*fat_header);
	if (check_offset(ptr + sizeof(*fat_header), offset) || arch->offset < 1)
		return (ft_perror("Corrupted file\n", 0));
	write(1, "\n", 1);
	while (i++ < narch)
	{
		find_arch(arch->cputype, arch->cpusubtype, bin);
		if (nm(ptr + swap32(arch->offset), offset, bin))
			return (ft_perror("Corrupted\n", 0));
		if (i < narch)
			write(1, "\n", 1);
		arch++;
	}
	return (EXIT_SUCCESS);
}
