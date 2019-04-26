/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/26 11:12:54 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_tlsop(t_lsop **tmp)
{
	if ((*tmp))
	{
		free_tlsop(&((*tmp)->next));
		ft_memdel((void**)&((*tmp)->dir));
		ft_memdel((void**)tmp);
	}
}

static void	free_read_dir(t_ls *data, t_lsdiv *div, char **path)
{
	if (div)
	{
		if (div->rep_d)
			ft_memdel((void**)&(div->rep_d));
		if (div->rep)
			ft_memdel((void**)&(div->rep));
		ft_memdel((void**)&(div->name));
	}
	if ((*path) && (*path)[0])
		ft_memdel((void**)path);
}

static void	print_file(t_ls *data, t_lsop **mem, t_padding *pad, t_lsdiv *div)
{
	if ((test_bit(&(data->flag), 1) || test_bit(&(data->flag), 11)) && data->indi)
		ft_printf("\n%s:\n", div->name);
	data->indi = 1;
	if (test_bit(&(data->flag), 0))
		ft_printf("total %d\n", div->total);
	print_ls(data, mem, pad, div->len);
}

static void	recursive_dir(t_ls *data, t_lsop **origi, char *name)
{
	t_lsop	*mem;
	t_lsop	*tmp;

	mem = (*origi);
	while (mem->next)
	{
		if (test_bit(&(data->flag), 1) && (S_ISDIR(mem->file.st_mode))
			&& ft_strcmp(".", mem->dir->d_name) && ft_strcmp("..", mem->dir->d_name))
		{
			if (mem->dir->d_name[0])
				read_dir(data, mem->dir->d_name, ft_strjoin(name, "/"));
		}
		tmp = mem->next;
		ft_memdel((void**)&(mem->dir));
		ft_memdel((void**)&mem);
		mem = tmp;
	}
	ft_memdel((void**)&mem);
}

void	read_dir(t_ls *data, char *base, char *path)
{
	t_padding	pad;
	t_lsop		*op;
	t_lsop		*mem;
	t_lsdiv		div;

	ft_bzero(&pad, sizeof(t_padding));
	ft_bzero(&div, sizeof(t_lsdiv));
	if (!(div.name = ft_strjoin(path, base)))
		error_ls(data);
	op = NULL;
	if ((div.dir_ptr = opendir(div.name)))
	{
		if (!(div.rep_d = ft_strjoin(div.name, "/")))
			error_ls(data);
		while (1)
		{
			if (!op)
			{
				if (!(op = (t_lsop*)malloc(sizeof(t_lsop))))
					error_ls(data);
				op->next = NULL;
				mem = op;
			}
			else if (!op->next)
			{
				if (!((op->next) = (t_lsop*)malloc(sizeof(t_lsop))))
					error_ls(data);
				op = op->next;
				op->next = NULL;
			}
			if (!(div.tmp_dir = readdir(div.dir_ptr)))
				break ;
			if (!(op->dir = (t_dir*)ft_memalloc(sizeof(t_dir))))
				error_ls(data);
			ft_memcpy(op->dir, div.tmp_dir, sizeof(*div.tmp_dir));
			if (!(div.rep = ft_strjoin(div.rep_d , op->dir->d_name)))
				error_ls(data);
			lstat(div.rep, &(op->file));
			op->name = op->dir->d_name;
			if (test_bit(&(data->flag), 2) || op->dir->d_name[0] != '.')
				padding_ls(data, &pad, op);
			div.total += op->file.st_blocks;
			div.len++;
			ft_memdel((void**)&(div.rep));
		}
		print_file(data,& mem, &pad, &div);
		recursive_dir(data, &mem, div.name);
		closedir(div.dir_ptr);
	}
	else
		ft_lserror(data, base, div.name);
	free_read_dir(data, &div, &path);
}
