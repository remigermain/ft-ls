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

typedef	struct dirent	t_dir;
typedef	struct stat	t_stat;
typedef	struct passwd	t_passwd;
typedef	struct group	t_group;
typedef	struct winsize	t_winsize;
#define LS_FLAGS "RaArfGFsTL|l;;m|g;l;m|d;a;|1;l;|n;l;m|m;;l1|p;;F|S;;t|t;;S|U;;uc|u;;Uc|c;:Uu"
#define LS_MFLAGS ""

enum	e_flag_ls
{
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
	LS_R,
	LS_S
};

typedef	struct	s_lsop
{
	char			name[256];
	int				xattr;
	t_stat			file;
	int				exist;
	struct s_lsop	*next;
	struct s_lsop	*prev;
	struct s_lsop	*last;
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
	int block;
	int	col;
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
	int			len_argc;
	int			error;
	int			av;
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
t_bool			directory_file(t_ls *data, char *path, DIR *dir_ptr);
t_bool			regular_file(t_ls *data, char *name, char *path);
t_lsop			*info_file(t_ls *data, t_pad *pad, char *name, char *path_mem);
t_bool			directory_print(t_ls *da, t_lsop *l, char *p, t_pad *pa);
void			padding_ls(t_ls *data, t_lsop *op, t_pad *pad);
t_bool			print_file(t_ls *data, t_lsop *lst, t_pad *pad, char *path);
char			*cat_path(char *name, char *path);
t_bool			error_ls(char *str, t_lsop *lst);
t_bool			file_acl(t_ls *data, t_lsop *op, char *path);
t_bool			file_info(t_ls *data, t_lsop *op, t_pad *pad, char *path);

/*
**	sort_ls
*/
void			ls_sort(t_ls *data, t_lsop *op);
int				ls_sort_ascii(t_lsop *m, t_lsop *p);
int				ls_sort_size(t_lsop *m, t_lsop *p);
int				ls_sort_mtime(t_lsop *m, t_lsop *p);
int				ls_sort_atime(t_lsop *m, t_lsop *p);
int				ls_sort_ctime(t_lsop *m, t_lsop *p);
int				ls_sort_birthtime(t_lsop *m, t_lsop *p);

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
#endif
