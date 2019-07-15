/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 10:59:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 10:32:13 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				count;
	int				result;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	count = 0;
	result = 0;
	t_s1 = (unsigned char*)s1;
	t_s2 = (unsigned char*)s2;
	while (1)
	{
		result += (t_s1[count] - t_s2[count]);
		if (t_s1[count] == '\0' || t_s2[count] == '\0')
			return (result);
		if (t_s1[count] == t_s2[count])
			count++;
		else
			return (result);
	}
}
