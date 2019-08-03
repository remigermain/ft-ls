/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:30:21 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**-----------------------------------------------------------------------
**			add error from argv to t_lsop
**-----------------------------------------------------------------------
*/

static void		add_error(t_lst *st, char *name)
{
	static	t_lsop	*last = NULL;
	t_lsop			*lst;

	st->nb_error++;
	if (!(lst = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_argv(st, "add_error");
	ft_strcat(lst->name, name);
	lst->error = strerror(errno);
	if (!last)
	{
		st->error = lst;
		last = lst;
	}
	else
	{
		last->next = lst;
		last = last->next;
	}
}

/*
**-----------------------------------------------------------------------
**			add file from argv to t_lsop
**-----------------------------------------------------------------------
*/

static void		add_file(t_lst *st, t_stat *info, char *name)
{
	static	t_lsop	*last = NULL;
	t_lsop			*lst;

	st->nb_file++;
	if (!(lst = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_argv(st, "add_error");
	ft_strcat(lst->name, name);
	ft_memcpy(&(lst->file), info, sizeof(t_stat));
	if (!last)
	{
		st->file = lst;
		st->file->last = NULL;
		last = lst;
	}
	else
	{
		last->next = lst;
		last->next->prev = last;
		last = last->next;
		st->file->last = last;
	}
	padding_ls(lst, &(st->pad_file));
}

/*
**-----------------------------------------------------------------------
**			add folder from argv to t_lsop
**-----------------------------------------------------------------------
*/

static void		add_folder(t_lst *st, t_stat *info, char *name)
{
	static	t_lsop	*last = NULL;
	t_lsop			*lst;

	st->nb_folder++;
	if (!(lst = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_argv(st, "add_error");
	ft_strcat(lst->name, name);
	ft_memcpy(&(lst->file), info, sizeof(t_stat));
	if (!last)
	{
		st->folder = lst;
		st->folder->last = NULL;
		last = lst;
	}
	else
	{
		last->next = lst;
		last->next->prev = last;
		last = last->next;
		st->folder->last = last;
	}
	padding_ls(lst, &(st->pad_folder));
}

/*
**-----------------------------------------------------------------------
**			add folder or file or error from argv to t_lsop
**			and print error first , file and folder
**-----------------------------------------------------------------------
*/

static t_bool	parse_argv(char **argv, int i)
{
	t_lst	st;
	t_stat	info;

	ft_bzero(&st, sizeof(t_lst));
	while (argv[i])
	{
		if (!lstat(argv[i], &info))
		{
			if ((S_ISDIR(info.st_mode) ||
				S_ISLNK(info.st_mode)) && !exist_flags(LS_D))
				add_folder(&st, &info, argv[i]);
			else
				add_file(&st, &info, argv[i]);
		}
		else
			add_error(&st, argv[i]);
		i++;
	}
	print_error_argv(st.error);
	print_file_argv(&st);
	return (print_folder_argv(&st));
}

int				main(int argc, char **argv)
{
	int	ret;

	ret = 0;
	if (argc)
		ret = init_flags(argv, "RaArfGFsTLt|l;;1m|g;l;m|d;a;|1;;l|\
			n;l;m|m;;l1|p;;F|S;;t|U;;uc|u;;Uc|c;;Uu|", "", F_STOP);
	if (exist_flags(LS_G_MAJ))
		flags_base('G', F_RM);
	else
		flags_base('G', F_ADD);
	if (exist_flags(LS_S_MAJ))
		remove_flags(LS_T);
	if (ret != -1 && parse_argv(argv, ret))
		ft_stprintf(OUT_PF, "");
	else
		ft_dprintf(2, "error generated.\n");
	return (-1);
}
