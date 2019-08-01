/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 20:57:44 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

char	*cat_path(char *name, char *path)
{
	char	path_mem[257];

	if (!name || !path)
		return (NULL);
	if (!path[0])
		return (ft_strdup(name));
	ft_bzero(path_mem, 2);
	if (ft_strlen(path) > 0 && path[ft_strlen(path)] != '/')
		path_mem[0] = '/';
	ft_strcat(path_mem, name);
	return (ft_strjoin(path, path_mem));
}

t_bool	free_lsop(t_lsop *op)
{
	t_lsop *mem;

	while (op)
	{
		mem = op;
		op = op->next;
		ft_memdel((void**)&mem);
	}
	return (FALSE);
}

t_bool	error_ls(t_lsop *lst, char *str, void *dir_ptr)
{
	free_lsop(lst);
	ft_dprintf(2, T_RED"error: "T_LGREY"%s: %m\n"T_WHITE, str);
	if (dir_ptr)
		closedir(dir_ptr);
	return (FALSE);
}

t_bool	hidden_file(char *name)
{
	if (exist_flags(LS_A) || exist_flags(LS_F) ||
			name[0] != '.' || (exist_flags(LS_A_MAJ) &&
				ft_strcmp(".", name) && ft_strcmp("..", name)))
		return (TRUE);
	return (FALSE);
}

t_bool	recusive_file(t_lsop *lst)
{
	if (exist_flags(LS_R_MAJ) && ft_strcmp(".", lst->name) &&
			ft_strcmp("..", lst->name) && (S_ISDIR(lst->file.st_mode) ||
			(S_ISLNK(lst->file.st_mode) && exist_flags(LS_L_MAJ))))
		return (TRUE);
	return (FALSE);
}
