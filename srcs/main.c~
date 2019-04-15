#include "ft_ls.h"

void	set_bit(short *st, int i)
{
	(*st) ^= 1 << i;
}

t_bool	test_bit(short *st, int i)
{
	if ((*st) & 1 << i)
		return (TRUE);
	return (FALSE);
}


static	int	put_flags(t_ls *st, int argc, char **argv)
{
	int	i;

	i = -1;
	ft_bzero(st, sizeof(t_ls));
	while (argc > 2 && argv[1][0] == '-' && argv[1][++i])
	{
		if (argv[1][i] == 'l')
			set_bit(&(st->flag), 0);
		else if (argv[1][i] == 'R')
			set_bit(&(st->flag), 1);
		else if (argv[1][i] == 'a')
			set_bit(&(st->flag), 2);
		else if (argv[1][i] == 'r')
			set_bit(&(st->flag), 3);
		else if (argv[1][i] == 't')
			set_bit(&(st->flag), 4);
		else if (argv[1][i] == 'u')
			set_bit(&(st->flag), 5);
		else if (argv[1][i] == 'f')
			set_bit(&(st->flag), 6);
		else if (argv[1][i] == 'g')
			set_bit(&(st->flag), 7);
		else if (argv[1][i] == 'd')
			set_bit(&(st->flag), 8);
		else if (argv[1][i] == 'G')
			set_bit(&(st->flag), 9);
	}
	return (i == -1 ? 1 : 2);
}

static	void	read_file(t_ls *st, int argc, int i)
{
	while ((st->dir = readdir(st->dir_ptr)))
	{
		stat(st->dir->d_name, &(st->stat));
		if (test_bit(&(st->flag), 0)) 
		{
			file_right(st->stat);
			file_link(st->stat);
			file_group(st->stat);
			file_size(st->stat);
			file_date(st->stat);
		}
		ft_printf("%s", st->dir->d_name);
		if (test_bit(&(st->flag), 0) && (i + 1)  < argc)
			ft_printf("\n");
		else
			ft_printf("  ");
	}
}

int main(int argc, char **argv)
{
	t_ls	st;
	int	i;
	char	multi;

	i = put_flags(&st, argc, argv);
	while (i < argc)
	{
		if ((st.dir_ptr = opendir(argv[i])))
		{
			if (i < argc)
				ft_printf("%s:\n", argv[i]);
		}
		if (st.dir_ptr)
			read_file(&st, argc, i);
		else
			ft_lserror(&st, argv[i]);
		i++;
		//if (++i < argc)
		//	ft_printf("\n");
	}
	return (0);
}
