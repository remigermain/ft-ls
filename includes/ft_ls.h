/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/26 08:03:50 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/15 02:32:16 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/ioctl.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# define MONTH_SIX 15552000
# define BUFF_STPRINTF 10000

typedef	struct dirent	t_dir;
typedef	struct stat	t_stat;
typedef	struct passwd	t_passwd;
typedef	struct group	t_group;
typedef	struct winsize	t_winsize;

#define true 1
#define false 0

enum	{
	LS_L = 0,
	LS_A,
	LS_A_MAJ,
	LS_1,
	LS_R_MAJ,
	LS_P,
	LS_T_MAJ,
	LS_L_MAJ,
	LS_C,
	LS_M,
	LS_N,
	LS_G_MAJ,
	LS_G,
	LS_D,
	LS_F_MAJ,
	LS_F,
	LS_T,
	LS_U,
	LS_U_MAJ,
	LS_S_MAJ,
	LS_R
};

typedef	struct	s_lsop
{
	char			name[256];
	int				xattr;
	t_stat			file;
	struct s_lsop	*next;
}				t_lsop;

typedef	struct	s_pad
{
	int	total;
	int	link;
	int	group;
	int	group2;
	int	size;
	int	size2;
	int	sizet;
	int mm;
	int	name;
}				t_pad;

typedef	struct	s_infols
{
	int				total;
	char			*path;
	t_lsop			*op;
	struct s_infols	*next;
}				t_infols;

typedef	struct	s_ls
{
	t_winsize	w;
	long		flag;
	time_t		time;
	char		*path;
}				t_ls;

/*
**	right_file
*/
void			sort_ls(t_ls *data, t_lsop **mem);
int				ls_putflags(t_ls *data, int argc, char **argv);

/*
**	read-file && dir
*/
t_bool			read_dir(t_ls *data, char *path, char *name);

/*
**	sort_ls
*/
void			ls_sort(t_ls *data, t_lsop **op);
int				ls_sort_ascii(t_ls *d, t_lsop **m, t_lsop **p);
int				ls_sort_size(t_ls *d, t_lsop **m, t_lsop **p);
int				ls_sort_mtime(t_ls *d, t_lsop **m, t_lsop **p);
int				ls_sort_atime(t_ls *d, t_lsop **m, t_lsop **p);
int				ls_sort_ctime(t_ls *d, t_lsop **m, t_lsop **p);

void			padding_ls(t_ls *data, t_lsop *op, t_pad *pad);
t_bool    		print_file(t_ls *data, t_lsop *lst, t_pad *pad, char *path);
char			*cat_path(char *name, char *path);

/*
**	tools.c
*/
t_bool			free_lsop(t_lsop *mem);
void			usage_ls(void);
void			set_bit(long *st, int i);
void			clear_bit(long *st, int i);
void			set_or_clear_bit(long *st, int i);
t_bool			test_bit(long *st, int i);
void			ft_lserror(t_ls *st, char *path);
t_bool			error_ls(char *str);
void			free_ftls(t_ls *st);
void			sticky_byte(t_stat stat, char right[10]);
#endif
