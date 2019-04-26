/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 08:03:50 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 14:08:20 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

#include "../libft/includes/libft.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
//#include <attr/xattr.h>
#include <time.h>
#include <stdio.h>
//#define ft_printf(...) ft_printf("")

#define MAJOR(dev) ((int)(((unsigned int) (dev) >> 8) & 0xff))
#define MINOR(dev) ((int)((dev) & 0xff))


# define	LS_L	0
# define	LS_R_MAJ	1
# define	LS_A	2
# define	LS_R	3
# define	LS_T	4
# define	LS_U	5

# define	LS_F	6
# define	LS_G	7
# define	LS_D	8
# define	LS_G_MAJ	9
# define	LS_1	10
# define	LS_F_MAJ	11
# define	LS_C	12
# define	LS_N	13
# define	LS_M	14
# define	LS_P	15
# define	LS_A_MAJ	16

# define	LS_B_MAJ	17
# define	LS_S_MAJ	18
# define	LS_T_MAJ	19


typedef	struct dirent	t_dir;
typedef	struct stat	t_stat;
typedef	struct passwd	t_passwd;
typedef	struct group	t_group;

typedef	struct	s_padding
{
	int	link;
	int	group;
	int	group2;
	int	size;
	int	size2;
	int	name;
}		t_padding;

typedef struct	s_lsdiv
{
	t_padding	pad;
	t_dir	*tmp_dir;
	void	*dir_ptr;
	char	*rep_d;
	char	*rep;
	char	*name;
	int		total;
	int		len;
}				t_lsdiv;

typedef	struct	s_lsop
{
	char	*name;
	t_stat	file;
	struct	s_lsop *next;
}		t_lsop;

typedef	struct	s_infols
{
	int	total;
	char	*path;
	t_lsop	*op;
	struct	s_infols *next;
}		t_infols;

typedef	struct	s_ls
{
	t_bool	error;
	long	flag;
	char	*name;
	int		i;
	int		argc;
	char	indi;
	t_infols *st;
}		t_ls;

/*
**	right_file
*/
void	sort_ls(t_ls *data, t_lsop **mem);
void	file_right(t_ls *data, t_stat filestat, t_padding *pad);
void	file_link(t_ls *data, t_stat filestat, t_padding *pad);
void	file_group(t_ls *data, t_stat filestat, t_padding *pad);
void	file_size(t_ls *data, t_stat filestat, t_padding *pad);
void	file_date(t_ls *data, t_stat filestat, t_padding *pad);

/*
**	read-file && dir
*/
void	print_ls(t_ls *data, t_lsop **op, t_padding *pad, int len);
void	read_dir(t_ls *data, char *base, char *path);
int		read_file(t_ls *data, t_lsop *op, t_padding *pad);

/*
**	sort_ls
*/
void	ls_sort(t_ls *data, t_lsop **op, int nb);
int	swap_elem(t_ls *data, t_lsop **op, t_lsop ***mem, t_lsop ***mem2);
int	ls_sort_ascii(t_ls *data, t_lsop **op, t_lsop ***mem, t_lsop ***mem2);

/*
**	tools.c
*/
void	ls_putflags(t_ls *data, int argc, char **argv);
void	set_bit(long *st, int i);
void	clear_bit(long *st, int i);
t_bool	test_bit(long *st, int i);
void	ft_lserror(t_ls *st, char *base, char *name);
void	error_ls(t_ls *data);
void	free_ftls(t_ls *st);
void	padding_ls(t_ls *data, t_padding *pad, t_lsop *op);


#endif
