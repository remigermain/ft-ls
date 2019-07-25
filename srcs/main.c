/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/19 09:41:41 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/20 16:30:21 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

static int		parse_argv(int argc, char **argv, int i)
{
	return (0);
}

int				main(int argc, char **argv)
{
	int	ret;
	
	ret = init_flags(argv, LS_FLAGS, LS_MFLAGS, F_STOP);
	if (ret != -1)
		return (parse_argv(argc, argv, ret));
	else
		ft_dprintf(2, "error generated.\n");
	return (-1);
}
