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

/*
**-----------------------------------------------------------------------
**			enum from ls flags
**-----------------------------------------------------------------------
*/

enum	e_flag_ls
{
	LS_L = 'l',
	LS_A = 'a',
	LS_A_MAJ = 'A',
	LS_1 = '1',
	LS_R_MAJ = 'R',
	LS_P = 'p',
	LS_T_MAJ = 'T',
	LS_L_MAJ = 'L',
	LS_C = 'c',
	LS_M = 'm',
	LS_N = 'n',
	LS_G_MAJ = 'G',
	LS_G = 'g',
	LS_D = 'd',
	LS_F_MAJ = 'F',
	LS_F = 'f',
	LS_T = 't',
	LS_U = 'u',
	LS_U_MAJ = 'U',
	LS_S_MAJ = 'S',
	LS_R = 'r',
	LS_S = 's'
};

/*
**-----------------------------------------------------------------------
**		struct for each file
**-----------------------------------------------------------------------
*/

typedef	struct	s_lsop
{
	char			name[256];
	char			*error;
	int				xattr;
	t_stat			file;
	int				exist;
	struct s_lsop	*next;
	struct s_lsop	*prev;
	struct s_lsop	*last;
}				t_lsop;

/*
**-----------------------------------------------------------------------
**		struct for padding
**-----------------------------------------------------------------------
*/

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

/*
**-----------------------------------------------------------------------
**		struct for parse arguments
**-----------------------------------------------------------------------
*/

typedef struct	s_lst
{
	t_lsop	*error;
	t_lsop	*file;
	t_pad	pad_file;
	t_lsop	*folder;
	t_pad	pad_folder;
	int		nb_error;
	int		nb_file;
	int		nb_folder;
}				t_lst;

/*
**-----------------------------------------------------------------------
**			main_ls.c
**-----------------------------------------------------------------------
*/
t_bool			recursive_dir(t_lsop *lst, char *path, int folder);
t_bool			print_folder_argv(t_lst *st);

/*
**-----------------------------------------------------------------------
**			main_ls2.c
**-----------------------------------------------------------------------
*/
void			print_error_argv(t_lsop *lst);
void			print_file_argv(t_lst *st);
t_bool			print_folder(t_lsop *lst, t_pad *pad, char *path);

/*
**-----------------------------------------------------------------------
**			padding_ls.c
**-----------------------------------------------------------------------
*/
void			padding_ls(t_lsop *op, t_pad *pad);

/*
**-----------------------------------------------------------------------
**		print_file.c
**-----------------------------------------------------------------------
*/
t_bool			print_file(t_lsop *lst, t_pad *pad, char *path);
t_bool			file_acl(t_lsop *op, char *path);

/*
**-----------------------------------------------------------------------
**			sort_ls.c && sort_utils_ls.c
**-----------------------------------------------------------------------
*/
void			ls_sort(t_lsop *op);
void			ls_sort_funct(t_lsop *op, int (*func)(t_lsop*, t_lsop*));
int				ls_sort_ascii(t_lsop *m, t_lsop *p);
int				ls_sort_size(t_lsop *m, t_lsop *p);
int				ls_sort_mtime(t_lsop *m, t_lsop *p);
int				ls_sort_atime(t_lsop *m, t_lsop *p);
int				ls_sort_birthtime(t_lsop *m, t_lsop *p);

/*
**-----------------------------------------------------------------------
**			file_info.c
**-----------------------------------------------------------------------
*/
t_bool			file_info(t_lsop *op, t_pad *pad, char *path);

/*
**-----------------------------------------------------------------------
**			utils_ls.c
**-----------------------------------------------------------------------
*/
char			*cat_path(char *name, char *path);
t_bool			free_lsop(t_lsop *mem);
t_bool			error_ls(t_lsop *op, char *str, void *dir);
t_bool			hidden_file(char *name);
t_bool			recusive_file(t_lsop *lst);

/*
**-----------------------------------------------------------------------
**			utils_ls2.c
**-----------------------------------------------------------------------
*/
t_winsize		get_winsize(void);
void			print_ioctl(t_lsop *mem, t_pad *pad);
void			print_folder_text(t_lsop *lst, char *str, char *str2);
void			ft_lserror(char *path);
void			error_argv(t_lst *st, char *error);

#endif
