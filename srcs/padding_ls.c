/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_padding.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:40:54 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/30 15:19:11 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static void	padding_groups(t_ls *data, t_lsdiv *div, t_lsop *op)
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
	if (div->pad.group < i_uid)
		div->pad.group = i_uid;
	if (div->pad.group2 < i_gid)
		div->pad.group2 = i_gid;
}

void		padding_ls(t_ls *data, t_lsdiv *div, t_lsop *op)
{
	div->total += op->file.st_blocks;
	if (div->pad.link < ft_intlen(op->file.st_nlink))
		div->pad.link = ft_intlen(op->file.st_nlink);
	padding_groups(data, div, op);
	if (S_ISBLK(op->file.st_mode) || S_ISCHR(op->file.st_mode))
	{
		if (div->pad.size < ft_intlen(major(op->file.st_rdev)))
			div->pad.size = ft_intlen(major(op->file.st_rdev));
		if (div->pad.size2 < ft_intlen(minor(op->file.st_rdev)))
			div->pad.size2 = ft_intlen(minor(op->file.st_rdev));
	}
	else if (div->pad.size < ft_intlen(op->file.st_size))
		div->pad.size = ft_intlen(op->file.st_size);
	if (div->pad.name < (int)ft_strlen(op->name))
		div->pad.name = ft_strlen(op->name);
}
