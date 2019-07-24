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

t_bool			read_dir(t_ls *data, char *path, char *name)
{
	t_stat	file;
	DIR		*dir_ptr;

	dir_ptr = NULL;
	ft_bzero(&file, sizeof(t_stat));
	if (!stat(path, &file))
	{
		if (S_ISDIR(file.st_mode) && !test_bit(&(data->flag), LS_D))
		{
			if ((dir_ptr = opendir(path)) != NULL)
				return (directory_file(data, path, dir_ptr));
			else
				ft_lserror(data, path);
		}
		else if (!regular_file(data, path, name))
			return (FALSE);
	}
	else
		ft_lserror(data, name);
	return (TRUE);
}

/*
**	apelle la fonction read_dir() pour chaque arguments
*/

static t_bool	put_dread(t_ls *data, t_lsop *base)
{
	t_lsop	*origi;
	t_lsop	*lst;
	t_lsop	*mem;
	t_pad	pad;

	origi = base;
	lst = NULL;
	mem = NULL;
	if (test_bit(&(data->flag), LS_R_MAJ))
		clear_bit(&(data->flag), LS_R_MAJ);
	ft_bzero(&pad, sizeof(t_pad));
	while (origi)
	{
		if ((!lst && !(lst = info_file(data, &pad, origi->name, ""))) ||
			(mem && !(mem->next = info_file(data, &pad, origi->name, ""))))
		{
			free_lsop(lst);
			return (error_ls("malloc from directory_file", lst));
		}
		mem = (!mem ? lst : mem->next);
		origi = origi->next;
	}
	return (directory_print(data, lst, "", &pad));
}

static t_bool	put_read(t_ls *data, t_lsop *mem)
{
	t_lsop	*origi;

	origi = mem;
	if (test_bit(&(data->flag), LS_D) && mem)
		return (put_dread(data, mem));
	while (origi)
	{
		if (data->len_argc)
			ft_stprintf(KEEP_PF, "%s:\n", mem->name);
		if (!read_dir(data, origi->name, origi->name))
			return (FALSE);
		if (origi->next)
			ft_stprintf(KEEP_PF, "\n");
		origi = origi->next;
	}
	if (!mem && !read_dir(data, ".", "."))
		return (FALSE);
	return (TRUE);
}

/*
**	malloc et tri les arguments
*/

static t_bool	sort_argv(t_ls *data, t_lsop **op, char **argv)
{
	t_lsop	*mem;
	int		i;

	i = 0;
	data->len_argc = -1;
	if (argv[0] && !((*op) = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		return (error_ls("sort_argv", NULL));
	mem = (*op);
	while (argv[i])
	{
		ft_strcat(mem->name, argv[i]);
		lstat(argv[i++], &(mem->file));
		if (argv[i] && !(mem->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			return (error_ls("sort_argv", *op));
		mem = mem->next;
		data->len_argc++;
	}
	ls_sort(data, (*op));
	return (TRUE);
}

int				main(int argc, char **argv)
{
	t_ls	data;
	t_lsop	*op;
	int		i;

	op = NULL;
	i = ls_putflags(&data, argc, argv);
	if (data.error)
	{
		ft_dprintf(2, "ls: illegal option -- %c\n", data.error);
		ft_dprintf(2, "usage: ls [-ABCFGHLOPRSTUWabcdefghikl");
		ft_dprintf(2, "mnopqrstuwx1] [file ...]\n");
		return (1);
	}
	data.time = time(NULL);
	if (sort_argv(&data, &op, argv + i))
		put_read(&data, op);
	ft_stprintf(OUT_PF, "");
	free_lsop(op);
	return (0);
}
