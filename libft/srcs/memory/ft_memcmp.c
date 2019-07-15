/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 11:49:01 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/07 19:42:25 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	count;
	unsigned char	*s1_b;
	unsigned char	*s2_b;

	count = 0;
	s1_b = (unsigned char*)s1;
	s2_b = (unsigned char*)s2;
	while (n-- > 0)
	{
		if (s1_b[count] != s2_b[count])
			return ((s1_b[count] - s2_b[count]));
		count++;
	}
	return (0);
}
