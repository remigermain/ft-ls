/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: loiberti <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/14 14:36:08 by loiberti     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/27 21:41:15 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void	set_or_clear_bit(long *bit, int bit_nb, int mode)
{
	if (!mode && !(*bit & (1 << bit_nb)))
		*bit |= (1 << bit_nb);
	else if (mode && (*bit & (1 << bit_nb)))
		*bit ^= (1 << bit_nb);
}

t_bool	test_bit(long *bit, int bit_nb)
{
	return (!(*bit & (1 << bit_nb)) ? FALSE : TRUE);
}

void	set_bit(long *bit, int bit_nb)
{
	*bit |= (1 << bit_nb);
}

void	clear_bit(long *bit, int bit_nb)
{
	if (test_bit(bit, bit_nb))
		*bit ^= (1 << bit_nb);
}
