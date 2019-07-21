/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:12:02 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"



t_lsop		*info_file(t_ls *data, t_pad *pad, char *name, char *path_mem)
{
	t_lsop	*lst;
	char	*path;

	if (!(lst = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		return (NULL);
	if (!(path = cat_path(name, path_mem)))
	{
		ft_memdel((void**)&lst);
		return (NULL);
	}
	lst->xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	ft_strcat(lst->name, name);
	lstat(path, &(lst->file));
//	if (!S_ISLNK(lst->file.st_mode))
//		stat(path, &(lst->file));
	padding_ls(data, lst, pad);
	ft_strdel(&path);
	return (lst);
}

t_bool			recursive_dir(t_ls *data, t_lsop *lst, char *path)
{
	t_lsop	*mem;
	char	*new_path;

	while(lst)
	{
		mem = lst;
		if (test_bit(&(data->flag), LS_R_MAJ) && ft_strcmp(".", lst->name) && ft_strcmp("..", lst->name) && (S_ISDIR(mem->file.st_mode) || (S_ISLNK(mem->file.st_mode) && test_bit(&(data->flag), LS_L_MAJ))))
		{
			ft_stprintf(OUT_PF, "\n%s/%s:\n", path, lst->name);
			if (!(new_path = cat_path(mem->name, path)))
				return (free_lsop(mem));
			if (!read_dir(data, new_path, mem->name))
			{
				ft_strdel(&new_path);
				return (free_lsop(mem));
			}
			ft_strdel(&new_path);
		}
		lst = lst->next;
		ft_memdel((void**)&mem);
	}
	return (true);
}

t_bool			directory_file(t_ls *data, char *path, void *dir_ptr)
{
	t_dir	*dir;
	t_pad	pad;
	t_lsop	*lst;
	t_lsop	*mem;

	lst = NULL;
	mem = NULL;
	ft_bzero(&pad, sizeof(t_pad));
	while ((dir = readdir(dir_ptr)))
	{
		if (test_bit(&(data->flag), LS_A) || dir->d_name[0] != '.')
		{
			lst = info_file(data, &pad, dir->d_name, path);
			lst->next = mem;
			mem = lst;
		}
	}
	if (test_bit(&(data->flag), LS_L))
		ft_stprintf(KEEP_PF, "total %d\n", pad.total);
	print_file(data, lst, &pad, path);
	closedir(dir_ptr);
	return (recursive_dir(data, lst, path));
}

t_bool			regular_file(t_ls *data, char *name, char *path)
{
	t_pad pad;
	t_lsop *lst;

	ft_bzero(&pad, sizeof(t_pad));
	if (!(lst = info_file(data, &pad, name, path)))
		return (false);
	print_file(data, lst, &pad, path);
	ft_stprintf(KEEP_PF, "\n");
	return (true);
}

t_bool			read_dir(t_ls *data, char *path, char *name)
{
	t_stat		file;
	void		*dir_ptr;

	dir_ptr = NULL;
	ft_bzero(&file, sizeof(t_stat));
	if (!lstat(path, &file))
	{
		if (S_ISDIR(file.st_mode) && !test_bit(&(data->flag), LS_D))
		{
			if ((dir_ptr = opendir(path)))
				return (directory_file(data, path, dir_ptr));
			else
				ft_lserror(data, name);
		}
		else if (!regular_file(data, path, path))
			return (false);
	}
	else
		ft_lserror(data, path);
	return (true);
}
