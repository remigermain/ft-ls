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
		if (mem)
			mem->next->prev = mem;
		mem = (!mem ? lst : mem->next);
		origi = origi->next;
	}
	if (lst)
		lst->last = mem;
	return (directory_print(data, lst, "", &pad));
}

static t_lsop	*print_fileargv(t_ls *data, t_lsop *mem)
{
	t_lsop *origi;
	int		i;

	origi = mem;
	data->av = 1;
	i = 0;
	while (origi)
	{
		if (origi->exist == 2 && (++i))
			read_dir(data, origi->name, "");
		origi = origi->next;
	}
	data->av = 0;
	if (i)
		ft_stprintf(KEEP_PF, "\n");
	if (!test_bit(&(data->flag), LS_L) &&
		!test_bit(&(data->flag), LS_1))
		ft_stprintf(KEEP_PF, "\n");
	if (mem && (test_bit(&(data->flag), LS_R)))
		return (mem->last ? mem->last : mem);
	else
		return (mem);
}

static t_lsop	*print_error(t_ls *data, t_lsop *mem)
{
	t_lsop *origi;

	origi = mem;
	while (origi)
	{
		if (origi->exist == -1)
			read_dir(data, origi->name, origi->name);
		origi = origi->next;
	}
	return (print_fileargv(data, mem));
}

static t_bool	put_read(t_ls *data, t_lsop *mem, int i)
{
	t_lsop	*origi;

	origi = print_error(data, mem);
	if (test_bit(&(data->flag), LS_D) && mem)
		return (put_dread(data, mem));
	while (origi)
	{
		if (origi->exist == 1)
		{
			if (i)
				ft_stprintf(KEEP_PF, "\n");
	 		if (data->len_argc && S_ISDIR(origi->file.st_mode))
				ft_stprintf(KEEP_PF, "%s:\n", origi->name);
			if (!read_dir(data, origi->name, origi->name))
				return (FALSE);
			if (((!test_bit(&(data->flag), LS_R) && origi->next) ||
				(test_bit(&(data->flag), LS_R) && origi->prev)) &&
				S_ISDIR(origi->file.st_mode))
				i = 1;
		}
		origi = (test_bit(&(data->flag), LS_R) ? origi->prev : origi->next);
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
		if ((mem->exist = lstat(argv[i], &(mem->file))) == 0)
			mem->exist = (S_ISDIR(mem->file.st_mode) ? 1 : 2);
		if (argv[++i] && !(mem->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			return (error_ls("sort_argv", *op));
		if (mem->next)
		{
			mem->next->prev = mem;
			(*op)->last = mem->next;
		}
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
		put_read(&data, op, 0);
	ft_stprintf(OUT_PF, "");
	free_lsop(op);
	return (0);
}
