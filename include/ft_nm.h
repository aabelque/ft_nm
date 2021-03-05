/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/05 16:59:29 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define ERROR(s) prints(s) 
#define RD PROT_READ
#define PRIV MAP_PRIVATE

#if __APPLE__
	#include <mach-o/loader.h>
	#include <mach-o/nlist.h>
#elif __linux__
	#include </usr/include/linux/elf.h>
	#include </usr/include/bsd/nlist.h>
#else
	ERROR("It only work on MAC OS and LINUX system\n")
#endif

typedef struct	s_env
{
	int32_t					fd;
	char					*p;
	struct stat				buf; 
	struct mach_header_64	*header_64;
	struct mach_header		*header_32;
	struct load_command		*lc;
	struct symtab_command	*sym;

}				t_env;


void		init_env(t_env **e);
int			close_binary(t_env **e);
int			open_binary(t_env **e, char *bin);
int			ft_perror(char *s, t_env *e);

int			ft_strlen(char *s);
void		prints(char *s);
void		printc(char c);
void		ft_putnbr(int nb);
void		hexdump(long n);
