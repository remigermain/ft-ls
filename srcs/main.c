/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 21:10:06 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_read(t_ls *data, t_lsop **origi, int len)
{
	t_lsop	*tmp;
	t_lsop	*mem;
	char	*dir;

	mem = (*origi);
	if (!(dir = ft_strdup("")))
		error_ls();
	if (mem)
	{
		ls_sort(data, &mem, len);
		while (mem)
		{
			data->error = FALSE;
			data->i++;
			read_dir(data, mem->name, dir);
			tmp = mem->next;
			ft_memdel((void**)&mem);
			mem = tmp;
		}
	}
	else
		read_dir(data, ".", dir);
	ft_memdel((void**)&dir);
}

static void	sort_argv(t_ls *data, char **argv, int i, int len)
{
	t_lsop	*mem;
	t_lsop	*op;

	op = NULL;
	mem = NULL;
	while (argv[i] && (++len))
	{
		if (!op)
		{
			if (!(op = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				error_ls();
			op->next = NULL;
			mem = op;
		}
		else if (!(op->next))
		{
			if (!(op->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				error_ls();
			op = op->next;
			op->next = NULL;
		}
		op->name = argv[i];
		lstat(argv[i++], &(op->file));
	}
	put_read(data, &mem, len);
}

int			main(int argc, char **argv)
{
	t_ls	data;

	ls_putflags(&data, argc, argv);
	data.time = time(NULL);
	sort_argv(&data, argv + data.i, 0, 0);
	free_ftls(&data);
	return (0);
}
