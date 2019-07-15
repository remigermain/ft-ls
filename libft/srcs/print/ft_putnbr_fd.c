/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putnbr_fd.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 13:38:11 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:25:39 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		i;
	t_mint	max;

	ft_bzero(str, 12);
	i = ft_intlen(n);
	max = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		max = 1;
	}
	else
		i -= 1;
	while (i >= max)
	{
		str[i] = (n % 10) + 48;
		i--;
		n /= 10;
	}
	ft_putstr_fd(str, fd);
}
