/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_trjoin.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:55:10 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/23 20:38:40 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	len2;
	char	*str;

	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = (char *)ft_memalloc(len + len2 + 1)))
		return (NULL);
	ft_memcpy(str, s1, len);
	ft_memcpy(str + len, s2, len2);
	return (str);
}
