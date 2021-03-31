/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 11:04:49 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/31 15:35:39 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			find_arch(cpu_type_t cputype, cpu_subtype_t cpusubtype, char *bin)
{
	if (swap64(cputype) == CPU_TYPE_X86_64)
	{
		prints(bin);
		write(1, " ", 1);
		if (swap64(cpusubtype) == CPU_SUBTYPE_X86_64_H)
			prints("(for architecture x86_64h):\n");
		else
			prints("(for architecture x86_64):\n");
	}
	else if  (swap64(cputype) == CPU_TYPE_I386)
	{
		prints(bin);
		write(1, " ", 1);
		prints("(for architecture i386):\n");
	}
	else if  (swap64(cputype) == CPU_TYPE_POWERPC)
	{
		prints(bin);
		write(1, " ", 1);
		prints("(for architecture ppc):\n");
	}
}

int					fat64(void *ptr, void *offset, char *bin)
{
	int					narch, i;
	struct fat_header	*fat_header;
	struct fat_arch_64	*arch;

	i = 0;
	fat_header = (struct fat_header *)ptr;
	narch = swap64(fat_header->nfat_arch);
	arch = (void *)fat_header + sizeof(*fat_header);
	if (check_offset(ptr + sizeof(*fat_header), offset) || arch->offset < 1)
		return (ft_perror("Corrupted file\n", 0));
	write(1, "\n", 1);
	while (i++ < narch)
	{
		find_arch(arch->cputype, arch->cpusubtype, bin);
		if (nm(ptr + swap64(arch->offset), offset, bin))
			return (ft_perror("Corrupted\n", 0));
		if (i < narch)
			write(1, "\n", 1);
		arch++;
	}
	return (EXIT_SUCCESS);
}
