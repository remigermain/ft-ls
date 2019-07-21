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
**	apelle la fonction read_dir() pour chaque arguments
*/

static t_bool	put_read(t_ls *data, t_lsop *mem)
{
	t_lsop *origi;

	origi = mem;
	data->path = "";
	while (origi)
	{
		if (!read_dir(data, origi->name, origi->name))
			return (false);
		origi = origi->next;
	}
	if (!mem && !read_dir(data, ".", "."))
		return (false);
	return (true);
}

/*
**	malloc et tri les arguments
*/

static t_bool	sort_argv(t_ls *data, t_lsop **op, char **argv)
{
	t_lsop *mem;
	int i;

	i = 0;
	if (argv[0] && !((*op) = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		return (error_ls("sort_argv"));
	mem = (*op);
	while (argv[i])
	{
		ft_strcat(mem->name, argv[i]);
		lstat(argv[i++], &(mem->file));
		if (argv[i] && !(mem->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			return (error_ls("sort_argv"));
		mem = mem->next;
	}
	ls_sort(data, op);
	return (TRUE);
}

int			main(int argc, char **argv)
{
	t_ls	data;
	t_lsop	*op;
	int		i;

	op = NULL;
	if (argc > 1 && !ft_strcmp(argv[1], "--help"))
		usage_ls();
	i = ls_putflags(&data, argc, argv);
	data.time = time(NULL);
	if (sort_argv(&data, &op, argv + i))
	{
		if (put_read(&data, op))
			ft_stprintf(OUT_PF, "");
		else
			error_ls("main");
	}
	free_lsop(op);
	free_ftls(&data);
	return (0);
}
