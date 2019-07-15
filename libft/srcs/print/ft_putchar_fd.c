/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putchar_fd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:07:14 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:06:04 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpchar_fd(char c, int fd)
{
	if (ft_isprint(c) || (c >= 9 && c <= 13))
		return (ft_putchar_fd(c, fd));
	else
	{
		ft_putchar_fd('^', fd);
		ft_putchar_fd(c + 64, fd);
		return (2);
	}
}

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putwchar_fd(wchar_t c, int fd)
{
	unsigned char	new[4];
	int				a;

	a = 0;
	if (c <= 0x7F)
		new[a++] = c;
	else if (c <= 0x7FF)
		new[a++] = 192 + (c / 64);
	else
	{
		if (c > 0xFFFF)
		{
			new[a++] = 240 + (c / 262144);
			new[a++] = 128 + ((c / 4096) % 64);
		}
		else
			new[a++] = 224 + (c / 4096);
		new[a++] = 128 + ((c / 64) % 64);
	}
	if (c > 0x7F)
		new[a++] = 128 + (c % 64);
	write(fd, new, a);
	return (a);
}
