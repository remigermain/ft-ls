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
	START_STRING = '^',
	END_STRING = '$',
};

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
}				t_reg_class;

typedef	struct	s_regex
{
	int		start;
	int		end;
	struct	s_regex	*next;
}				t_regex;

void	print_match(t_regex	*reg, char	*s1)
{
	t_regex	*tmp;
	int		i;

	tmp = reg;
	i = 0;
	while (tmp)
	{
		ft_printf("%.*s", tmp->start - i, s1 + i);
		ft_printf(B_BLUE T_BLACK"%.*s" B_WHITE T_WHITE,\
				tmp->end - tmp->start, s1 + tmp->start);
		i = tmp->end;
		tmp = tmp->next;
	}	
	ft_printf("%s\n", s1 + i);
}

int		count_match(t_regex	*reg)
{
	t_regex	*tmp;
	int		i;

	tmp = reg;
	i = 0;
	while (tmp && (++i))
		tmp = tmp->next;
	return (i);
}

t_regex	*add_list(int start, int end)
{
	t_regex	*reg;

	if (!(reg = (t_regex*)ft_memalloc(sizeof(t_regex))))
	{
		ft_dprintf(2, "malloc_error\n");
		exit(0);
	}
	reg->start = start;
	reg->end = end;
	return (reg);
}

void	add_match(t_regex **reg, int start, int end)
{
	t_regex	*tmp;

	tmp = (*reg);
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		(*reg) = add_list(start, end);
	else
		tmp->next = add_list(start, end);
}

t_bool	regex_start_string(char *s1, char *regex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
}

t_bool	match_regex(char *s1, char *regex)
{
	t_regex		*reg;

	reg = NULL;
	add_match(&reg, 1, 4);
	add_match(&reg, 6, 7);
	add_match(&reg, 11, 14);
	print_match(reg, s1);
}


t_bool	match(char *s1, char *regex)
{
	int	i;

	i = -1;
	while (s1[++i])
	{
		if (match_regex(s1 + i, regex))
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
