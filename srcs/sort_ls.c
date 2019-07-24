/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sort_lst.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:48 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 14:04:12 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

int			ls_sort_ctime(t_ls *data, t_lsop *mem, t_lsop *mem2)
{
	if ((test_bit(&(data->flag), LS_R) &&
		mem->file.st_ctime > mem2->file.st_ctime) ||
			(!test_bit(&(data->flag), LS_R) &&
			mem->file.st_ctime < mem2->file.st_ctime))
		return (1);
	else if (mem->file.st_ctime == mem2->file.st_ctime)
		return (ls_sort_ascii(data, mem, mem2));
	return (0);
}

static void	swap_elem2(t_lsop *mem2, t_lsop *mem, t_lsop *mem3)
{
	t_stat	tmp_stat;
	char	mem_name[256];

	if (mem3)
		;

	tmp_stat = mem->file;
	ft_memcpy(mem_name, mem->name, 256);
	mem->file = mem2->file;
	ft_memcpy(mem->name, mem2->name, 256);
	mem2->file = tmp_stat;
	ft_memcpy(mem2->name, mem_name, 256);
	ft_swap(&(mem->xattr), &(mem2->xattr));

}

static int	swap_elem(t_ls *data, t_lsop *mem, t_lsop *mem2, t_lsop *mem3)
{
	if (test_bit(&(data->flag), LS_R))
		swap_elem2(mem, mem2, mem3);
	else if (!test_bit(&(data->flag), LS_R))
		swap_elem2(mem2, mem, mem3);
	return (1);
}

static void	ls_sort_funct(t_ls *data, t_lsop *op,
		int (*sort_function)(t_ls*, t_lsop*, t_lsop*))
{
	t_lsop	*mem;
	t_lsop	*mem2;
	t_lsop	*mem3;
	int		i;

	i = 1;
	while (i)
	{
		mem = op;
		mem2 = op->next;
		mem3 = NULL;
		i = 0;
		while (mem2)
		{
			if (sort_function(data, mem, mem2))
				i = swap_elem(data, mem, mem2, mem3);
			mem3 = mem;
			mem = mem->next;
			mem2 = mem2->next;
		}
	}
}

void		ls_sort(t_ls *data, t_lsop *op)
{
	t_lsop	*mem;

	mem = op;
	if (test_bit(&(data->flag), LS_T))
	{
		if (test_bit(&(data->flag), LS_U))
			ls_sort_funct(data, op, ls_sort_atime);
		else if (test_bit(&(data->flag), LS_U_MAJ))
			ls_sort_funct(data, op, ls_sort_birthtime);
		else if (test_bit(&(data->flag), LS_C))
			ls_sort_funct(data, op, ls_sort_ctime);
		else
			ls_sort_funct(data, op, ls_sort_mtime);
	}
	else if (test_bit(&(data->flag), LS_S_MAJ))
		ls_sort_funct(data, op, ls_sort_size);
	else
		ls_sort_funct(data, op, ls_sort_ascii);
}
