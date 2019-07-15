/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 10:59:27 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/09 17:53:34 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				count;
	int				result;
	unsigned char	*t_s1;
	unsigned char	*t_s2;

	count = 0;
	result = 0;
	t_s1 = (unsigned char*)s1;
	t_s2 = (unsigned char*)s2;
	if ((int)n == 0)
		return (0);
	while (1)
	{
		result += (t_s1[count] - t_s2[count]);
		if (count >= ((int)n - 1))
			return (result);
		if (t_s1[count] == '\0' && t_s2[count] == '\0')
			return (result);
		if (t_s1[count] == t_s2[count])
			count++;
		else
			return (result);
	}
}
