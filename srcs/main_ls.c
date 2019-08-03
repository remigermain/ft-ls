/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 12:10:24 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**-----------------------------------------------------------------------
**			join new lsop form older
**			last lsop is just for optimizing listing
**-----------------------------------------------------------------------
*/

static void		ls_join(t_lsop **last, t_lsop **lst, t_lsop **op)
{
	if (!(*last))
	{
		(*op) = (*lst);
		(*op)->last = NULL;
		(*last) = (*lst);
	}
	else
	{
		(*last)->next = (*lst);
		(*last)->next->prev = (*last);
		(*last) = (*last)->next;
		(*op)->last = (*last);
	}
}

/*
**-----------------------------------------------------------------------
**			take information forn file
**			and add this to t_lsop
**			if file is link , take info from lstat otherwise stat
**-----------------------------------------------------------------------
*/

static t_bool	add_all(t_lsop **op, t_pad *pad, t_dir *dir_tmp, char *path)
{
	static	t_lsop	*last = NULL;
	t_lsop			*lst;
	char			*path_name;

	if (!op)
	{
		last = NULL;
		return (TRUE);
	}
	if (!(lst = (t_lsop*)ft_memalloc(sizeof(t_lsop))) ||
		!(path_name = cat_path(dir_tmp->d_name, path)))
		return (error_ls(lst, "malloc from add_filefoler", NULL));
	ft_strcat(lst->name, dir_tmp->d_name);
	lst->xattr = listxattr(path_name, NULL, 0, XATTR_NOFOLLOW);
	lstat(path_name, &(lst->file));
	if (!S_ISLNK(lst->file.st_mode) || exist_flags(LS_L_MAJ))
		stat(path_name, &(lst->file));
	ls_join(&last, &lst, op);
	padding_ls(lst, pad);
	ft_strdel(&path_name);
	return (TRUE);
}

/*
**-----------------------------------------------------------------------
**			add file/folder to t_lsop
**-----------------------------------------------------------------------
*/

static t_bool	get_folder(char *path)
{
	DIR		*dir_ptr;
	t_dir	*dir_tmp;
	t_lsop	*file;
	t_pad	pad;

	file = NULL;
	ft_bzero(&pad, sizeof(t_pad));
	add_all(NULL, NULL, NULL, path);
	if ((dir_ptr = opendir(path)))
	{
		while ((dir_tmp = readdir(dir_ptr)))
		{
			if (hidden_file(dir_tmp->d_name) &&
				!add_all(&file, &pad, dir_tmp, path))
				return (error_ls(file, "add_all", dir_ptr));
		}
		if (closedir(dir_ptr) != 0)
			return (error_ls(file, "can't close dir", NULL));
		return (print_folder(file, &pad, path));
	}
	else
		ft_lserror(path);
	return (TRUE);
}

/*
**-----------------------------------------------------------------------
**			if recursive's flags is set ( LS_R_MAJ )
**			get folder to this folder print get folderm, print ... ect
**-----------------------------------------------------------------------
*/

t_bool			recursive_dir(t_lsop *lst, char *path, int folder)
{
	t_lsop	*tmp;
	char	*new_path;

	new_path = NULL;
	lst = (exist_flags(LS_R) && lst && lst->last ? lst->last : lst);
	while (lst)
	{
		tmp = lst;
		if (recusive_file(tmp) && (++folder))
		{
			print_folder_text(lst, "\n", NULL);
			if (!(new_path = cat_path(tmp->name, path)))
				return (free_lsop(tmp));
			print_folder_text(lst, "%s:\n", new_path);
			if (!get_folder(new_path))
			{
				ft_strdel(&new_path);
				return (free_lsop(tmp));
			}
			ft_strdel(&new_path);
		}
		lst = (exist_flags(LS_R) ? lst->prev : lst->next);
		ft_memdel((void**)&tmp);
	}
	return (TRUE);
}

/*
**-----------------------------------------------------------------------
**			print folder from argv to t_lsop
**			if not have arguments , is remplaced by "."
**-----------------------------------------------------------------------
*/

t_bool			print_folder_argv(t_lst *st)
{
	t_lsop	*tmp;
	int		folder;

	ls_sort(st->folder);
	tmp = (exist_flags(LS_R) && st->folder &&
			st->folder->last ? st->folder->last : st->folder);
	folder = 0;
	while (tmp)
	{
		if (folder || st->nb_file || st->nb_error)
			ft_stprintf(KEEP_PF, "\n");
		if (st->nb_folder - 1)
			ft_stprintf(KEEP_PF, "%s:\n", tmp->name);
		if (!get_folder(tmp->name))
			return (free_lsop(st->folder));
		folder++;
		tmp = (exist_flags(LS_R) ? tmp->prev : tmp->next);
	}
	if (!st->folder && !st->nb_file && !st->nb_error)
		return (get_folder("."));
	return (TRUE);
}
