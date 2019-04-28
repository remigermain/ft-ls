/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 02:45:16 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void		recursive_dir(t_ls *data, t_lsop **origi, char *name)
{
	t_lsop	*mem;
	t_lsop	*tmp;

	mem = (*origi);
	while (mem)
	{
		if (test_bit(&(data->flag), LS_R_MAJ) && S_ISDIR(mem->file.st_mode)
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
			error_ls();
	}
	else if (!(*op)->next)
	{
		if (!(((*op)->next) = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
			error_ls();
		op = &((*op)->next);
	}
	if (!(div->rep = ft_strjoin(div->rep_d, div->tmp_dir->d_name)))
		return (0);
	(*op)->name = strdup(div->tmp_dir->d_name);
	(*op)->xattr = listxattr(div->rep, NULL, 0, XATTR_NOFOLLOW);
	if (div->tmp_dir->d_type == DT_LNK)
		lstat(div->rep, &((*op)->file));
	else
		stat(div->rep, &((*op)->file));
	if (test_bit(&(data->flag), LS_A) || (*op)->name[0] != '.')
		padding_ls(data, &(div->pad), (*op));
	div->total += (*op)->file.st_blocks;
	div->len++;
	ft_memdel((void**)&(div->rep));
	return ((*op));
}

static void		normal_dir(t_ls *data, t_lsdiv *div)
{
	ft_bzero(&(div->pad), sizeof(t_padding));
	if (!(div->rep_d = ft_strjoin(div->name, "/")))
		error_ls();
	while ((div->tmp_dir = readdir(div->dir_ptr)))
	{
		div->op = put_info(data, &(div->op), div);
		if (!(div->mem))
			div->mem = div->op;
	}
	data->path = div->rep_d;
}

static void		link_dir(t_ls *data, t_lsdiv *div, t_stat *file, char *base)
{
	ft_bzero(&(div->pad), sizeof(t_padding));
	data->link_dir = 1;
	if (!(div->mem = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_ls();
	div->mem->file = (*file);
	div->mem->name = strdup(base);
	div->mem->xattr = listxattr(base, NULL, 0, XATTR_NOFOLLOW);
	if (test_bit(&(data->flag), LS_A) || base[0] != '.')
		padding_ls(data, &(div->pad), div->mem);
	div->len++;
}

void			read_dir(t_ls *data, char *base, char *path)
{
	t_lsdiv		div;
	t_stat		file;

	ft_bzero(&div, sizeof(t_lsdiv));
	if (!(div.name = ft_strjoin(path, base)))
		error_ls();
	if ((div.dir_ptr = opendir(div.name)))
	{
		lstat(base, &file);
		data->path = path;
		if (S_ISLNK(file.st_mode) && test_bit(&(data->flag), LS_L) &&
				!data->level)
			link_dir(data, &div, &file, base);
		else
			normal_dir(data, &div);
		print_file(data, &(div.mem), &(div.pad), &div);
		recursive_dir(data, &(div.mem), div.name);
		closedir(div.dir_ptr);
	}
	else
		ft_lserror(data, base, div.name);
	ft_memdel((void**)&(div.name));
	ft_memdel((void**)&(div.rep_d));
	if (path && path[0])
		ft_memdel((void**)&path);
}
