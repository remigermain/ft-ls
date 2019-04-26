/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 13:06:39 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_read(t_ls *data, t_lsop	**origi, int len)
{
	t_lsop	*tmp;
	t_lsop	*mem;
	char	*dir;

	mem = (*origi);
	if (!(dir = ft_strdup("")))
		error_ls(data);
	if (mem)
	{
		ls_sort(data, &mem, len);
		while (mem)
		{
			data->error = FALSE;
			data->i++;
			read_dir(data, mem->name, dir);
			if (data->i < data->argc && !data->error)
				ft_printf("\n");
			tmp = mem->next;
			ft_memdel((void**)&mem);
			mem = tmp;
		}
	}
	else
		read_dir(data, ".", dir);
	ft_memdel((void**)&dir);
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
	mem = NULL;
	while (argv[i])
	{
		if (!op)
		{
			if (!(op = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				error_ls(data);
			op->next = NULL;
			mem = op;
		}
		else if (!(op->next))
		{
			if (!(op->next = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
				error_ls(data);
			op = op->next;
			op->next = NULL;
		}
		op->name = argv[i];
		lstat(argv[i++], &(op->file));
		len++;
	}
	put_read(data, &mem, len);
}

int			main(int argc, char **argv)
{
	t_ls	data;
	char	*name;
	int		i;

	i = ls_putflags(&data, argc, argv);
	sort_argv(&data, argv + data.i);
/*	free_ftls(&data);
*/	return (0);
}
