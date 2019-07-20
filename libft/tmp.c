#include "libft.h"

enum	e_regex_op
{
	R_NOT = '^',
	R_OR = '|',
	R_RANGE = '-',
	R_STAR = '*',
	R_COMMA= ',',
	R_QUAN_O = '{',
	R_QUAN_C = '}',
	R_CLASS_O = '[',
	R_CLASS_C = ']',
};

enum	e_regex
{
	CLASS_RANG,
	CLASS_NOT,
};

enum	e_quantifier
{
	QUAN_PLUS,
	QUAN_STAR,
	QUAN_INT
};

typedef struct s_quanti
{
	int		qu1;
	int		qu2;
	unsigned	fl : 2;
}		t_quanti;







typedef	struct	s_reg_word
{
	char			*name;
	struct	s_class	*next;
}				t_reg_word;

typedef	struct	s_reg_class
{
	t_reg_word	*word;
	int			range1;
	int			range2;
	int			stop;
	int			flags;
}














typedef struct s_class
{
	char		*regex;
	int		rg1;
	int		rg2;
	int		stop;
	int		*mem;
	unsigned 	fl : 2;
}		t_class;



typedef struct	s_regex
{
	char	*regex;
	int	i;
}		t_regex;


t_bool	ft_strchr_range(t_class *class, char *s1, int *mem)
{
	int	i;

	i = -1;
	ft_printf("%c   %d\n", s1[0], class->stop);
	while (s1[++i] && s1[i] != class->stop)
	{
//		ft_printf("s1[%d] >= %d  <= %d\n", s1[i], class->rg1, class->rg2);
		if ((class->fl >> CLASS_NOT) & 0x1)
		{
			if (s1[i] >= class->rg1 && s1[i] <= class->rg2)
			{
			//	(*mem) += i;
				return (FALSE);
			}
		}
		else if (s1[i] < class->rg1 || s1[i] > class->rg2)
		{
		//	(*mem) += i;
			return (FALSE);
		}
	}
	(*mem) += i;
	return (TRUE);
}

t_bool	ft_strchr_norange(t_class *class, char *s1, int *mem)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (class->regex[++i])
	{
		j = -1;
		while (s1[++j] && s1[j] != class->stop)
		{
			if (s1[j] == class->regex[i])
			{
				if ((class->fl >> CLASS_NOT) & 0x1)
					return (FALSE);
				else
				{
					(*mem) += j;
					return (TRUE);
				}
			}
		}
	}
	if ((class->fl >> CLASS_NOT) & 0x1)
	{
		(*mem) += j;
		return (TRUE);
	}
	return (FALSE);
}

int	parse_quantifier(t_class *class, char *regex, int i)
{
}	

int	parse_class(t_class *class, char *regex)
{
	int	i;

	i = 0;
	ft_bzero(class, sizeof(t_class));
	class->regex = regex;
	class->rg1 = -1;
	class->rg2 = -1;
	while (regex[++i] && regex[i] != ']')
	{
		if (regex[i] == R_NOT)
			class->fl |= (1 << CLASS_NOT);
		else if (regex[i] == R_RANG)
			class->fl |= (1 << CLASS_RANG);
		else if (class->rg1 == -1)
			class->rg1 = regex[i];
		else if (class->rg2 == -1)
			class->rg2 = regex[i];
	}
	if (regex[i] == ']')
		i++;
	if (regex[i] == '{')
		i += parse_quantifier(class, regex, i);
	class->stop = regex[i];
	return (i);
}

t_bool	regex_class(t_regex *reg, char *s1, int *i)
{
	t_class	class;

	reg->i += parse_class(&class, reg->regex + reg->i);
	if ((class.fl >> CLASS_RANG) & 0x1)
		return (ft_strchr_range(&class, s1, i));
	else
		return (ft_strchr_norange(&class, s1, i));
}

t_bool	match2(char *s1, char *regex)
{
	t_regex	reg;
	t_bool	ret;
	int	i;

	ft_bzero(&reg, sizeof(t_regex));
	reg.regex = regex;
	ret = FALSE;
	i = 0;
	while (s1[i] && reg.regex[reg.i])
	{
		if (reg.regex[reg.i] == '[')
			ret = regex_class(&reg, s1 + i, &i);
		else
		{
			if (s1[i] == reg.regex[reg.i])
				reg.i++;
			else
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}

t_bool	match(char *s1, char *regex)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (match2(s1 + i, regex))
			return (TRUE);
	}
	return (FALSE);
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_printf("./prog < string > < regex string >\n");
		exit(0);
	}
	ft_printf("match = %s\n", (match(argv[1], argv[2]) ?  "\033[38;5;326mTRUE" : "\033[1;31mFALSE"));
	return (0);
}
