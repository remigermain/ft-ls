/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_padding.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:40:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:08:49 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	padding_groups(t_ls *data, t_lsop *op, t_pad *pad)
{
	t_passwd	*uid;
	t_group		*gid;
	int			i_uid;
	int			i_gid;

	if ((uid = getpwuid(op->file.st_uid)) &&
			!test_bit(&(data->flag), LS_N))
		i_uid = ft_strlen(uid->pw_name);
	else
		i_uid = ft_intlen(op->file.st_uid);
	if ((gid = getgrgid(op->file.st_gid)) &&
			!test_bit(&(data->flag), LS_N))
		i_gid = ft_strlen(gid->gr_name);
	else
		i_gid = ft_intlen(op->file.st_gid);
	if (pad->group < i_uid)
		pad->group = i_uid;
	if (pad->group2 < i_gid)
		pad->group2 = i_gid;
}

void		padding_ls(t_ls *data, t_lsop *op, t_pad *pad)
{
	pad->total += op->file.st_blocks;
	if (pad->block < ft_intlen(op->file.st_blocks))
		pad->block = ft_intlen(op->file.st_blocks);
	if (pad->link < ft_intlen(op->file.st_nlink))
		pad->link = ft_intlen(op->file.st_nlink);
	padding_groups(data, op, pad);
	if (S_ISBLK(op->file.st_mode) || S_ISCHR(op->file.st_mode))
	{
		if (pad->size < ft_intlen(major(op->file.st_rdev)))
			pad->size = ft_intlen(major(op->file.st_rdev));
		if (pad->size2 < ft_intlen(minor(op->file.st_rdev)))
			pad->size2 = ft_intlen(minor(op->file.st_rdev));
		if (pad->size2 > pad->sizet)
			pad->sizet = pad->size2;
		if (pad->size > pad->sizet)
			pad->sizet = pad->size;
		pad->mm = 1;
	}
	else if (pad->size < ft_intlen(op->file.st_size))
		pad->size = ft_intlen(op->file.st_size);
	if (pad->name < (int)ft_strlen(op->name))
		pad->name = ft_strlen(op->name);
}
