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

t_bool	error_ls(t_lsop *lst, char *str)
{
	free_lsop(lst);
	ft_dprintf(2, T_RED"error: "T_LGREY"%s: %m\n"T_WHITE, str);
	return (FALSE);
}

t_bool	hidden_file(char *name)
{
	if (exist_flags(LS_A) || exist_flags(LS_F) ||
			name[0] != '.' || (exist_flags(LS_A_MAJ) &&
				ft_strcmp(".", name) && ft_strcmp("..", name)))
		return (true);
	return (false);
}

t_bool recusive_file(t_lsop *lst)
{
	if (exist_flags(LS_R_MAJ) && ft_strcmp(".", lst->name) &&
			ft_strcmp("..", lst->name) && (S_ISDIR(lst->file.st_mode) ||
			(S_ISLNK(lst->file.st_mode) && exist_flags(LS_L_MAJ))))
		return (true);
	return (false);
}

void	ft_lserror(char *name)
{
	char	*file;
	int		len;

	len = ft_strlen(name);
	while (len > 0 && name[len - 1] != '/')
		len--;
	file = name + len;
	ft_stprintf(OUT_PF, "");
	ft_dprintf(2, "ls: %s: ", file);
	if (exist_flags(LS_G_MAJ))
		ft_dprintf(2, T_RED);
	ft_dprintf(2, "%m\n");
	if (exist_flags(LS_G_MAJ))
		ft_dprintf(2, T_WHITE);
}

void		error_argv(t_lst *st, char *error)
{
	ft_dprintf(2, T_RED"error: "T_LGREY"%s\n"T_WHITE, error);
	free_lsop(st->error);
	free_lsop(st->file);
	free_lsop(st->folder);
	exit(0);
}