NAME = pipex

SRC = pipex.c
UTIL = get_next_line_utils.c ft_split.c ft_strlen.c ft_strncmp.c utility.c
SRC_DIR = mandatory/
UTIL_DIR = utility/
SRCPATH = $(addprefix $(SRC_DIR), $(SRC))
UTILPATH = $(addprefix $(UTIL_DIR), $(UTIL))

BONUS_NAME = pipex_bonus

BONUS_SRC = pipex_bonus.c initialize.c childs.c
UTIL = ft_split.c ft_strlen.c ft_strncmp.c get_next_line.c get_next_line_utils.c utility.c
BONUS_DIR = px_bonus/
BONUSPATH = $(addprefix $(BONUS_DIR), $(BONUS_SRC))

FLAG = -Wall -Wextra -Werror -g

$(NAME):
		gcc $(FLAG) $(SRCPATH) $(UTILPATH) -o $(NAME)

bonus:
		gcc $(FLAG) $(BONUSPATH) $(UTILPATH) -o $(BONUS_NAME)

clean:
		rm -f $(NAME) $(BONUS_NAME)

fclean: clean

all: $(NAME) bonus

re: fclean all