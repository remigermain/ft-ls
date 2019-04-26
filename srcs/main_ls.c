/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 14:27:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		free_readdir(t_lsdiv *div, char **path)
{
	if (div)
	{
		if (div->name)
			ft_memdel((void**)&(div->name));
		if (div->rep_d)
			ft_memdel((void**)&(div->rep_d));
	}
	if ((*path) && (*path)[0])
		ft_memdel((void**)path);
}

static void		print_file(t_ls *data, t_lsop **mem, t_padding *pad,
		t_lsdiv *div)
{
	if ((test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11)) &&
			data->indi)
		ft_printf("\n%s:\n", div->name);
	data->indi = 1;
	if (test_bit(&(data->flag), 0))
		ft_printf("total %d\n", div->total);
	print_ls(data, mem, pad, div->len);
}

static void		recursive_dir(t_ls *data, t_lsop **origi, char *name)
{
	t_lsop	*mem;
	t_lsop	*tmp;

	mem = (*origi);
	while (mem)
	{
		if (test_bit(&(data->flag), 1) && (S_ISDIR(mem->file.st_mode))
			&& ft_strcmp(".", mem->name) && ft_strcmp("..", mem->name))
		{
			if (mem->name[0])
				read_dir(data, mem->name, ft_strjoin(name, "/"));
		}
		tmp = mem->next;
		if (mem->name)
			ft_memdel((void**)&(mem->name));
		ft_memdel((void**)&mem);
		mem = tmp;
	}
}

static t_lsop	*put_info(t_ls *data, t_lsop **op, t_lsdiv *div)
{
	if (!(*op))
	{
		if (!((*op) = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			return (NULL);
		(*op)->next = NULL;
	}
	else if (!(*op)->next)
	{
		if (!(((*op)->next) = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			return (NULL);
		op = &((*op)->next);
		(*op)->next = NULL;
	}
	if (!(div->rep = ft_strjoin(div->rep_d, div->tmp_dir->d_name)))
		return (0);
	(*op)->name = strdup(div->tmp_dir->d_name);
	lstat(div->rep, &((*op)->file));
	if (test_bit(&(data->flag), 2) || (*op)->name[0] != '.')
		padding_ls(data, &(div->pad), (*op));
	div->total += (*op)->file.st_blocks;
	div->len++;
	ft_memdel((void**)&(div->rep));
	div->tmp_dir = NULL;
	return ((*op));
}

void			read_dir(t_ls *data, char *base, char *path)
{
	t_lsop		*op;
	t_lsop		*mem;
	t_lsdiv		div;

	ft_bzero(&div, sizeof(t_lsdiv));
	ft_bzero(&(div.pad), sizeof(t_padding));
	if (!(div.name = ft_strjoin(path, base)))
		error_ls(data);
	op = NULL;
	mem = NULL;
	if ((div.dir_ptr = opendir(div.name)))
	{
		if (!(div.rep_d = ft_strjoin(div.name, "/")))
			error_ls(data);
		while ((div.tmp_dir = readdir(div.dir_ptr)))
		{
			if (!(op = put_info(data, &op, &div)))
				error_ls(data);
			else if (!mem)
				mem = op;
		}
		print_file(data, &mem, &(div.pad), &div);
		recursive_dir(data, &mem, div.name);
		closedir(div.dir_ptr);
	}
	else
		ft_lserror(data, base, div.name);
	free_readdir(&div, &path);
}
