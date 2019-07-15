/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:49:01 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/02 16:45:09 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	int				count;
	unsigned char	*s2;

	count = 0;
	s2 = (unsigned char*)s;
	while (n-- > 0)
	{
		if (s2[count] == (unsigned char)c)
			return (s2 + count);
		else
			count++;
	}
	return (NULL);
}
