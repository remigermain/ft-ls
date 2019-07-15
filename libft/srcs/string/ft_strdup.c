/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdup.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:24:37 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 10:54:54 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s1);
	if (!(dest = (char *)ft_memalloc(len + 1)))
		return (NULL);
	ft_memcpy(dest, s1, len);
	return (dest);
}

t_uchar	*ft_ustrdup(unsigned char *s1)
{
	t_uchar	*dest;
	size_t	len;

	len = ft_ustrlen(s1);
	if (!(dest = (unsigned char *)ft_memalloc(len + 1)))
		return (NULL);
	ft_memcpy(dest, s1, len);
	return (dest);
}

t_uchar	*ft_strudup(char *s1)
{
	t_uchar	*dest;
	int		len;

	len = ft_strlen(s1);
	if (!(dest = (unsigned char *)ft_memalloc(len + 1)))
		return (NULL);
	ft_memcpy(dest, s1, len);
	return (dest);
}
