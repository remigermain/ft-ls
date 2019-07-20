# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rgermain <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/10/01 15:39:03 by rgermain     #+#   ##    ##    #+#        #
#    Updated: 2019/06/10 18:51:01 by rgermain    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libft.a
TYPE = " de la library"

CFLAGS = -Wall -Werror -Wextra -o3 -g

INCLUDE = -Iincludes

HEADER = libft.h limit.h color.h ft_printf.h is_methode.h memory.h strings.h \
		divers.h get_next_line.h lib_lst.h math.h print.h flags.h

OBJ = $(SRC:.c=.o)

DSRC = srcs/
DOBJ = obj/
ALL_D = $(D_DIVERS) $(D_IS_METHODE) $(D_LST) $(D_MATH) $(D_MEMORY) $(D_FLAGS) \
		$(D_PUT) $(D_STDIO) $(D_STRING) $(addprefix $(D_STDIO),$(D_FT_PRINTF))

DHEADER = includes/

SRC =  $(CSRC_divers) $(CSRC_ISMETHODE) $(CSRC_lst) $(CSRC_MATH) \
	  $(CSRC_MEMORY) $(CSRC_PUT) $(CSRC_string) $(CSRC_STDIO) $(CSRC_FLAGS)

CSRC = $(addprefix $(DSRC),$(SRC))
COBJ = $(addprefix $(DOBJ),$(OBJ))
CHEADER = $(addprefix $(DHEADER),$(HEADER))

# *****************************************************************************#
# 								ALL  SCRS									   #
# *****************************************************************************#

CSRC_divers = $(addprefix $(D_DIVERS),$(SRC_divers))
D_DIVERS = divers/
SRC_divers = 		ft_countwchar.c ft_match.c ft_sort_integer_table.c ft_swap.c get_next_line.c \
					ft_createtab.c timestamp.c

CSRC_FLAGS = $(addprefix $(D_FLAGS),$(SRC_flags))
D_FLAGS = flags/
SRC_flags = 	ft_erro_argv.c ft_flags.c ft_parse_argv.c


CSRC_ISMETHODE = $(addprefix $(D_IS_METHODE),$(SRC_ISMETHODE))  
D_IS_METHODE = is_methode/
SRC_ISMETHODE =		ft_isalpha.c  ft_isblank.c  ft_isdigit.c  ft_isprint.c  ft_isxdigit.c ft_toupper.c \
					ft_isalnum.c  ft_isascii.c  ft_iscntrl.c  ft_isgraph.c  ft_isspace.c  ft_tolower.c ft_toupper.c



CSRC_lst = $(addprefix $(D_LST),$(SRC_lst))
D_LST = libft_list/
SRC_lst	=			ft_lstadd.c    ft_lstdel.c    ft_lstdelone.c ft_lstiter.c   ft_lstmap.c    ft_lstnew.c



CSRC_MATH = $(addprefix $(D_MATH),$(SRC_MATH))
D_MATH = math/
SRC_MATH = 			ft_find_next_prime.c ft_iterative_factorial.c ft_recursive_factorial.c ft_sqrt.c \
					ft_intlen.c ft_iterative_power.c ft_recursive_power.c ft_is_prime.c



CSRC_MEMORY = $(addprefix $(D_MEMORY),$(SRC_MEMORY))
D_MEMORY = memory/
SRC_MEMORY = 		ft_bzero.c ft_memalloc.c ft_memccpy.c  ft_memchr.c ft_memcmp.c \
					ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c


CSRC_PUT = $(addprefix $(D_PUT),$(SRC_PUT))
D_PUT = print/
SRC_PUT = 			ft_putchar.c ft_putendl.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
					ft_printtab.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_base.c ft_putpstr_fd.c ft_putstr_fd.c 



CSRC_STDIO = $(addprefix $(D_STDIO),$(SRC_STDIO))
D_STDIO = stdio/
SRC_STDIO = $(CSRC_PRINTF)

CSRC_PRINTF = $(addprefix $(D_FT_PRINTF),$(SRC_PRINTF))
D_FT_PRINTF = ft_printf/
SRC_PRINTF =		conv_char.c conv_int.c conv_string.c ft_printf.c ft_stprintf.c lst_putdouble.c lst_putoption.c \
					put_string.c conv_double.c conv_other.c conv_tabstring.c utils.c



CSRC_string = $(addprefix $(D_STRING),$(SRC_STRINGS))
D_STRING = string/
SRC_STRINGS =		ft_atoi.c ft_str_is_uppercase.c ft_strcpychr.c ft_strlcat.c ft_strncmp.c ft_strrev.c \
					ft_itoa.c ft_strcapitalize.c ft_strdel.c ft_strlcpy.c ft_strncpy.c ft_strsplit.c \
					ft_itoa_base.c ft_strcat.c ft_strdup.c ft_strlen.c ft_strncpychr.c ft_strstr.c \
					ft_str_is_alpha.c ft_strchr.c ft_strequ.c ft_strlowcase.c ft_strnequ.c ft_strsub.c \
					ft_str_is_lowercase.c ft_strclr.c ft_striter.c ft_strmap.c ft_strnew.c ft_strtrim.c \
					ft_str_is_numeric.c ft_strcmp.c ft_striteri.c ft_strmapi.c ft_strnstr.c ft_strupcase.c \
					ft_str_is_printable.c ft_strcpy.c ft_strjoin.c ft_strncat.c ft_strrchr.c

COUNT = "1"
SPACE = "                  "
.DEFAULT_GOAL := all
ESC = $(shell printf '\033')

print_name : 
	@printf "\n----------------------------------------------------------------------\n\n\033[37m"
	@printf " \033[47m  \033[0m\033[37m                      [    LIBFT     ]               "
	@printf "         \033[0m  \033[47m  \033[0m\n"
	@printf "\n----------------------------------------------------------------------\n\n"

print_norme : 
	@printf "\n----------------------------------------------------------------------\n\n\033[37m"
	@printf " \033[47m  \033[0m\033[37m                   [    NORME LIBFT     ]            "
	@printf "         \033[0m  \033[47m  \033[0m\n"
	@printf "\n----------------------------------------------------------------------\n\n"


all: print_name $(NAME)
	@if [ $(COUNT) = "1" ]; then \
		echo $(SPACE)"\033[1;34m    Nothing are changed !\033[0m"; \
	fi

$(NAME): $(COBJ)
	@echo $(SPACE)"\033[JCompilation des Objects \033[38;5;326mterminer\033[0m"
	@echo $(SPACE)"Compilation "$(TYPE)" \033[34m" $(NAME) "\033[0m"
	@ar ru $(NAME) $?
	@echo $(SPACE)"Optimisation des index avec ranlib"
	@ranlib $(NAME)

$(DOBJ)%.o : $(DSRC)%.c $(CHEADER)
	@$(eval COUNT = "0")
	@mkdir -p $(DOBJ)
	@mkdir -p $(addprefix $(DOBJ), $(ALL_D))
	@gcc $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo $(SPACE)"compilation de la fonction \033[38;5;326m"$< "\033[0m\033[K\033[1A"

clean: print_name
	@rm -rf $(DOBJ)
	@echo $(SPACE)"Suppresion des \033[38;5;265mobjects\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo $(SPACE)"Suppresion "$(TYPE)" \033[38;5;265m"$(NAME) "\033[0m"

re: fclean all

norme : print_norme
	@norminette $(CSRC) $(CHEADER) | sed "s,Norme,${ESC}[38;5;326m&${ESC}[0m," | sed "s/Error/  Error/g" | sed "s,Error,${ESC}[31m&${ESC}[0m,"

.PHONY: default all clean fclean re norme print_libft print_norme
