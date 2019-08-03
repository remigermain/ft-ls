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

/*
**-----------------------------------------------------------------------
**			concat name with path
**			if last char of path and name is not slash "/" i add one .
**-----------------------------------------------------------------------
*/

char	*cat_path(char *name, char *path)
{
	char	path_mem[257];

	if (!name || !path)
		return (NULL);
	if (!path[0])
		return (ft_strdup(name));
	ft_bzero(path_mem, 2);
	if (ft_strlen(path) > 0 && path[ft_strlen(path)] != '/'
				&& name[0] != '/')
		path_mem[0] = '/';
	ft_strcat(path_mem, name);
	return (ft_strjoin(path, path_mem));
}

/*
**-----------------------------------------------------------------------
**			free lsop
**-----------------------------------------------------------------------
*/

t_bool	free_lsop(t_lsop *op)
{
	t_lsop *mem;

	while (op)
	{
		mem = op;
		op = (exist_flags(LS_R) ? op->prev : op->next);
		ft_memdel((void**)&mem);
	}
	return (FALSE);
}

/*
**-----------------------------------------------------------------------
**			free lsop
**			print error ( when malloc failed )
**			if dir_ptr is no null , closedir ( fucking norminette !)
**-----------------------------------------------------------------------
*/

t_bool	error_ls(t_lsop *lst, char *str, void *dir_ptr)
{
	free_lsop(lst);
	ft_dprintf(2, T_RED"error: "T_LGREY"%s: %m\n"T_WHITE, str);
	if (dir_ptr)
		closedir(dir_ptr);
	return (FALSE);
}

/*
**-----------------------------------------------------------------------
**		function for hidden_file
**
**		if falgs "LS_A" is set
**			include directory and all file with a dot
**		else if file name is not start with dot
**
**		else if falgs "LS_A" is set
**			include directory and all file with a dot
**-----------------------------------------------------------------------
*/

t_bool	hidden_file(char *name)
{
	if (exist_flags(LS_A) ||
			name[0] != '.' || (exist_flags(LS_A_MAJ) &&
				ft_strcmp(".", name) && ft_strcmp("..", name)))
		return (TRUE);
	return (FALSE);
}

/*
**-----------------------------------------------------------------------
**		function for recurisve_file
**
**		if falgs "LS_R_MAJ" is set and name of file is not "." and ".."
**		and ( the file is directory or
**			file is link and LS_L_MAJ flags is set )
**-----------------------------------------------------------------------
*/

t_bool	recusive_file(t_lsop *lst)
{
	if (exist_flags(LS_R_MAJ) && ft_strcmp(".", lst->name) &&
			ft_strcmp("..", lst->name) && (S_ISDIR(lst->file.st_mode) ||
			(S_ISLNK(lst->file.st_mode) && exist_flags(LS_L_MAJ))))
		return (TRUE);
	return (FALSE);
}
