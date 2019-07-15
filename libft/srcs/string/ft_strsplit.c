/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 10:55:45 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/19 12:32:33 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_passchar(const char *str, char c, size_t *ib)
{
	size_t	len;

	len = 0;
	while (str[(*ib)] == c)
		(*ib)++;
	while (str[(*ib) + len] != c && str[(*ib) + len] != '\0')
		len++;
	return (len);
}

static size_t	ft_splitlen(const char *str, char c)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			len++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (len + 1);
}

char			**ft_strsplit(const char *str, char c)
{
	char	**tab;
	size_t	len;
	size_t	ib;
	size_t	i;

	ib = 0;
	i = 0;
	if (!(tab = (char**)ft_memalloc(sizeof(char*) * ft_splitlen(str, c))))
		return (NULL);
	while (str[ib] != '\0')
	{
		len = ft_passchar(str, c, &ib);
		if (!(tab[i++] = ft_strsub(str, ib, len)))
		{
			ft_memdeltab_char(&tab);
			return (NULL);
		}
		ib += len;
	}
	tab[i] = NULL;
	return (tab);
}
