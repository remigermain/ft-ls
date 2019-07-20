/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   limit.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/21 02:28:17 by rgermain     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/28 03:10:54 by rgermain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIMIT_H
# define LIMIT_H
# define ULONG_MAX 18446744073709551615UL
# define LONG_MAX 9223372036854775807
# define LONG_MIN -9223372036854775808
# define UINT_MAX 4294967295
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define USHRT_MAX 65535
# define SHRT_MAX 32767
# define SHRT_MIN -32768
# define CHAR_MAX 127
# define CHAR_MIN -128
# define UCHAR_MAX 255

typedef char			t_bool;
typedef unsigned char	t_muint;
typedef char			t_mint;
typedef unsigned long	t_ulong;
typedef unsigned char	t_uchar;

typedef struct	s_time
{
	int	year;
	int	month;
	int	day;
	int	hour;
	int	minute;
	int	seconde;
}				t_time;

#endif
