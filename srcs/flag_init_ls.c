/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   flag_init.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:21 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 21:28:40 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_error_argv(t_lsop *lst)
{
	t_lsop	*op;

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

void		print_file_argv(t_lst *st)
{
	ls_sort(st->file);
	if (!print_file(st->file, &(st->pad_file), ""))
		error_argv(st, "print_file_argv");
	free_lsop(st->file);
}

t_bool		print_folder(t_lsop *lst, t_pad *pad, char *path)
{
	if (lst && exist_flags(LS_L))
		ft_stprintf(KEEP_PF, "total %d\n", pad->total);
	if (!print_file(lst, pad, path))
		return (FALSE);
	return (recursive_dir(lst, path, 0));
}
