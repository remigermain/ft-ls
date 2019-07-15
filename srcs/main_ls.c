/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/15 02:32:54 by rgermain    ###    #+. /#+    ###.fr     */
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
		if (test_bit(&(data->flag), LS_R_MAJ) &&
			ft_strcmp(".", mem->name) && ft_strcmp("..", mem->name)
				&& mem->name[0])
		{
			if (S_ISDIR(mem->file.st_mode) || (S_ISLNK(mem->file.st_mode) &&
						test_bit(&(data->flag), LS_L_MAJ)))
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
	if (!(div->rep = ft_strjoin(div->rep_d, div->tmp_dir->d_name)) ||
			!((*op)->name = strdup(div->tmp_dir->d_name)))
		error_ls();
	(*op)->xattr = listxattr(div->rep, NULL, 0, XATTR_NOFOLLOW);
	if (div->tmp_dir->d_type == DT_LNK)
		lstat(div->rep, &((*op)->file));
	else
		stat(div->rep, &((*op)->file));
	if (test_bit(&(data->flag), LS_A) || (*op)->name[0] != '.')
		padding_ls(data, div, (*op));
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

static int		link_dir(t_ls *data, t_lsdiv *div, t_stat *file, char *base)
{
	if (!((lstat(base, file) != -1 && S_ISLNK(file->st_mode) &&
		test_bit(&(data->flag), LS_L) && !data->level &&
		!test_bit(&(data->flag), LS_L_MAJ)) ||
			test_bit(&(data->flag), LS_D)))
		return (0);
	ft_bzero(&(div->pad), sizeof(t_padding));
	data->link_dir = 1;
	if (!(div->mem = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		error_ls();
	div->mem->file = (*file);
	div->mem->name = strdup(base);
	div->mem->xattr = listxattr(base, NULL, 0, XATTR_NOFOLLOW);
	if (test_bit(&(data->flag), LS_A) || base[0] != '.')
		padding_ls(data, div, div->mem);
	div->len++;
	return (1);
}

void			read_dir(t_ls *data, char *base, char *path)
{
	t_lsdiv		div;
	t_stat		file;

	ft_bzero(&div, sizeof(t_lsdiv));
	if (!path || !(div.name = ft_strjoin(path, base)))
		error_ls();
	if ((div.dir_ptr = opendir(div.name)))
	{
		data->path = path;
		if (!link_dir(data, &div, &file, base))
			normal_dir(data, &div);
		print_file(data, &(div.mem), &(div.pad), &div);
		recursive_dir(data, &(div.mem), div.name);
		closedir(div.dir_ptr);
	}
	else if (open(div.name, O_RDONLY) > 0)
		one_file(data, &div, &(div.mem));
	else
		ft_lserror(data, base, path);
	ft_memdel((void**)&(div.name));
	ft_memdel((void**)&(div.rep_d));
	if (path && path[0])
		ft_memdel((void**)&path);
}
