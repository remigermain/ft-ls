/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/23 12:08:25 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_read(t_ls *data, t_lsop	*mem, int len)
{
	t_lsop	*op;

	if (mem)
	{
		ls_sort(data, &mem, len);
		op = mem;
		while (op->next)
		{
			data->error = FALSE;
			data->i++;
			read_dir(data, op->name, "");
			mem = op;
			op = op->next;
			ft_memdel((void**)&(mem));
			if (data->i < data->argc && !data->error)
				ft_printf("\n");
		}
		ft_memdel((void**)&(op));
	}
	else
		read_dir(data, ".", "");
}

static void	sort_argv(t_ls *data, char **argv)
{
	int		i;
	int		len;
	t_lsop	*mem;
	t_lsop	*op;

	i = 0;
	len = 0;
	op = NULL;
	if (argv[i] && !(op = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_ls(data);
	mem = op;
	while (argv[i])
	{
		op->name = argv[i];
		lstat(argv[i++], &(op->file));
		if (!(op->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			error_ls(data);
		len++;
		op = op->next;
		op->next = NULL;
	}
	put_read(data, mem, len);
}

int			main(int argc, char **argv)
{
	t_ls	data;
	char	*name;
	int		i;

	i = ls_putflags(&data, argc, argv);
	sort_argv(&data, argv + data.i);
	free_ftls(&data);
	return (0);
}
