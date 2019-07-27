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

static void	add_error(t_lst *st, char *name)
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
		last = lst;
	}
	else
	{
		last->next = lst;
		last = last->next;
	}
	padding_ls(lst, &(st->pad_file));
}

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
		last = lst;
	}
	else
	{
		last->next = lst;
		last = last->next;
	}
	padding_ls(lst, &(st->pad_folder));
}

static int		parse_argv(int argc, char **argv, int i)
{
	t_lst	st;
	t_stat	info;

	ft_bzero(&st, sizeof(t_lst));
	while (argv[i])
	{
		if (!lstat(argv[i], &info))
		{
			if (S_ISDIR(info.st_mode) && !S_ISLNK(info.st_mode) && !exist_flags(LS_D))
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
	print_folder_argv(&st);
	return (0);
}

int				main(int argc, char **argv)
{
	int	ret;
	
	ret = init_flags(argv, LS_FLAGS, LS_MFLAGS, F_STOP);
//	flags_base('G', F_ADD);
	if (ret != -1)
		return (parse_argv(argc, argv, ret));
	else
		ft_dprintf(2, "error generated.\n");
	return (-1);
}
