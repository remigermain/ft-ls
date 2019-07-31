/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_ls.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:09 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/21 12:48:50 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void    print_error_argv(t_lsop *lst)
{
    t_lsop  *op;

    if (!exist_flags(LS_F))
        ls_sort_funct(lst, ls_sort_ascii);
    while (lst)
    {
        op = lst;
        ft_dprintf(2, "ls: %s: %s\n", lst->name, lst->error);
        lst = lst->next;
        ft_memdel((void**)&op);
    }
}

void    print_file_argv(t_lst *st)
{
    ls_sort(st->file);
    if (!print_file(st->file, &(st->pad_file), ""))
        error_argv(st, "print_file_argv");
    free_lsop(st->file);
}

static t_bool      print_folder(t_lsop *lst, t_pad *pad, char *path)
{
    if (lst && exist_flags(LS_L))
        ft_stprintf(KEEP_PF, "total %d\n", pad->total);
    if (!print_file(lst, pad, path))
        return (false);
    return (recursive_dir(lst, path));
}

static t_bool		add_file2(t_lsop **op, t_pad *pad, t_dir *dir_tmp, char *path)
{
	static	t_lsop	*last = NULL;
	t_lsop			*lst;
    char            *path_name;

    if (!op)
    {
        last = NULL;
        return (true);
    }
	if (!(lst = (t_lsop*)ft_memalloc(sizeof(t_lsop))))
		return (false);
    if (!(path_name = cat_path(dir_tmp->d_name, path)))
    {
        ft_memdel((void**)&lst);
        return (false);
    }
	ft_strcat(lst->name, dir_tmp->d_name);
    lst->xattr = listxattr(path_name, NULL, 0, XATTR_NOFOLLOW);
	lstat(path_name, &(lst->file));
	if (!S_ISLNK(lst->file.st_mode) || exist_flags(LS_L_MAJ))
		stat(path_name, &(lst->file));
	if (!last)
	{
		(*op) = lst;
        (*op)->last = NULL;
		last = lst;
	}
	else
	{
		last->next = lst;
        last->next->prev = last;
		last = last->next;
        (*op)->last = last;
	}
	padding_ls(lst, pad);
    ft_strdel(&path_name);
    return (true);
}

static t_bool     get_folder(char *path)
{
    DIR     *dir_ptr;
    t_dir   *dir_tmp;
    t_lsop  *file;
    t_pad   pad;

    file = NULL;
    ft_bzero(&pad, sizeof(t_pad));
    add_file2(NULL, NULL, NULL, path);
    if ((dir_ptr = opendir(path)))
    {
        while ((dir_tmp = readdir(dir_ptr)))
        {
            if (hidden_file(dir_tmp->d_name) && !add_file2(&file, &pad, dir_tmp, path))
            {
                closedir(dir_ptr);
                return (error_ls(file, "add_file2"));
            }
        }
        if (closedir(dir_ptr) != 0)
            return (error_ls(file, "can't close dir"));
        return (print_folder(file, &pad, path));
    }
    else
        ft_lserror(path);
    return (true);
}

t_bool    recursive_dir(t_lsop *lst, char *path)
{
    t_lsop  *tmp;
    char    *new_path;
    int     folder;

    new_path = NULL;
    folder = 0;
    while (lst)
    {
        tmp = (exist_flags(LS_R) && lst && lst->last ? lst->last : lst);
        if (recusive_file(tmp))
        {
            ft_stprintf(KEEP_PF, "\n");
            if (!(new_path = cat_path(tmp->name, path)))
                return(free_lsop(tmp));            
            ft_stprintf(KEEP_PF, "%s:\n", new_path);
            if (!get_folder(new_path))
            {
                ft_strdel(&new_path);
                return(free_lsop(tmp));
            }
            ft_strdel(&new_path);
            folder++;
        }
        lst = (exist_flags(LS_R) ? lst->prev : lst->next);
        ft_memdel((void**)&tmp);
    }
    return (true);
}

void    print_folder_argv(t_lst *st)
{
    t_lsop  *tmp;
    int     folder;

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
        {
            free_lsop(st->folder);
            return ;
        }
        folder++;
        tmp = (exist_flags(LS_R) ? tmp->prev : tmp->next);
    }
   // ft_stprintf(OUT_PF, "");
}
