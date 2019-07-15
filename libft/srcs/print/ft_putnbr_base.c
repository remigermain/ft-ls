/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 13:38:11 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:39:51 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(int n, int base)
{
	char	str[12];
	int		i;
	t_mint	max;

	ft_bzero(str, 12);
	i = ft_intlen_base(n, base);
	max = 0;
	if (n < 0 && base == 10)
	{
		str[0] = '-';
		max = 1;
	}
	if (n < 0)
		n = -n;
	else
		i -= 1;
	while (i >= max)
	{
		str[i] = (n % base) + 48;
		i--;
		n /= base;
	}
	ft_putstr_fd(str, 1);
}
