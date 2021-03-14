/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabelque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 13:39:05 by aabelque          #+#    #+#             */
/*   Updated: 2021/03/14 20:23:56 by aabelque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

# define ERROR(s) prints(s) 
# define RD PROT_READ
# define PRIV MAP_PRIVATE

# if __APPLE__
	#include <mach-o/loader.h>
	#include <mach-o/nlist.h>
	# define MAGIC_64 MH_MAGIC_64
	# define SYMTAB LC_SYMTAB
	# define SEGMENT64 LC_SEGMENT_64
# elif __linux__
	#include </usr/include/linux/elf.h>
	#include </usr/include/bsd/nlist.h>
# else
	ERROR("It only work on MAC OS and LINUX system\n")
# endif

typedef struct	s_symbol
{
	char			*name;
	uint8_t			n_type;
	uint8_t			n_sect;
	uint8_t			ext;
	uint64_t		n_value;
}				t_symbol;

typedef struct	s_section
{
	uint32_t	index;
	uint32_t	text;
	uint32_t	data;
	uint32_t	bss;
}				t_section;

int			handle_64(char *ptr);
void		init_sections(void);
t_section	*sections(void);
int			close_binary(void **ptr, int *fd, struct stat *buff);
int			open_binary(char *bin, int *fd, void **ptr, struct stat *buff);
int			ft_perror(char *s, int fd);
void		sort_symbols(t_symbol *sym, uint32_t nsyms);
void		ft_swap_symbol(t_symbol *sym, int i, int j);
void		ft_qsort_symbol(t_symbol *sym, int left, int right, int (*comp)(const char *, const char *));

int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
void		prints(char const *s);
void		printc(char c);
void		ft_putnbr(int nb);
void		hexdump(uint64_t n);
char		*ft_strcpy(char *dest, const char *src);
