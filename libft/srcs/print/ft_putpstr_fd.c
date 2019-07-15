/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_putendl_fd.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 14:13:25 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/05 18:45:19 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_putpstr_fd(char const *s, int fd)
{
	int count;

	count = 0;
	if (!s)
		return (-1);
	while (s[count] != '\0')
		ft_putpchar_fd(s[count++], fd);
	return (count);
}

int	ft_putpnstr_fd(char const *s, int len, int fd)
{
	int count;

	count = 0;
	if (!s)
		return (-1);
	while (s[count] != '\0' && count < len)
		ft_putpchar_fd(s[count++], fd);
	return (count);
}
