######################
## MAKE FILE BASICS ##
######################

NAME := minishell

CC := cc
#CFLAGS := -Wall -Werror -Wextra #

SRCS := src/minishell.c \
						builtins/cd.c \
						builtins/echo.c \
						builtins/env.c \
							builtins/exit.c \
						  builtins/export.c \
						  builtins/unset.c \
						  builtins/pwd.c \
						  src/token.c \
						  src/split_cmd.c \
						  src/free.c \
						  src/parse.c \
						  src/executer.c \
						  src/executer_utils.c \
						  src/token_checker.c \
						  src/token_checker_utils.c \
						  src/token_filter1.c \
						  src/token_filter2.c \
						  src/prompt.c \
						  src/init.c \
						  src/init_utils.c \
						  src/expander.c \
						  lib/libft/ft_isalnum.c \
						  lib/libft/ft_bzero.c \
						  lib/libft/ft_putchar_fd.c \
						  lib/libft/ft_itoa.c \
						  lib/libft/ft_strlcpy.c \
						  lib/libft/ft_memset.c \
						  lib/libft/ft_striteri.c \
						  lib/libft/ft_isdigit.c \
						  lib/libft/ft_tolower.c \
						  lib/libft/ft_toupper.c \
						  lib/libft/ft_strlen.c \
						  lib/libft/ft_strdup.c \
						  lib/libft/ft_putnbr_fd.c \
						  lib/libft/ft_isprint.c \
						  lib/libft/ft_calloc.c \
						  lib/libft/ft_memcpy.c \
						  lib/libft/ft_strchr.c \
						  lib/libft/ft_strrchr.c \
						  lib/libft/ft_isascii.c \
						  lib/libft/ft_memchr.c \
						  lib/libft/ft_putendl_fd.c \
						  lib/libft/ft_strmapi.c \
						  lib/libft/ft_strncmp.c \
						  lib/libft/ft_strnstr.c \
						  lib/libft/ft_strtrim.c \
						  lib/libft/ft_atoi.c \
						  lib/libft/ft_memcmp.c \
						  lib/libft/ft_strlcat.c \
						  lib/libft/ft_putstr_fd.c \
						  lib/libft/ft_isalpha.c \
						  lib/libft/ft_substr.c \
						  lib/libft/ft_strjoin.c \
						  lib/libft/ft_split.c \
						  lib/libft/ft_memmove.c \
						  lib/libft/ft_lstmap.c \
						  lib/libft/ft_lstadd_back.c \
						  lib/libft/ft_lstsize.c \
						  lib/libft/ft_lstnew.c \
						  lib/libft/ft_lstclear.c \
						  lib/libft/ft_lstlast.c \
						  lib/libft/ft_lstiter.c \
						  lib/libft/ft_lstdelone.c \
						  lib/libft/ft_lstadd_front.c \

OBJS := $(SRCS:.c=.o)

%.o: %.c
	@$(CC) -g $(CFLAGS) -c $< -o $@ -I./

######################
## MAKE FILE COLORS ##
######################


CLR_RMV         := \033[0m
RED                 := \033[1;31m
GREEN           := \033[1;32m
YELLOW          := \033[1;33m
BLUE            := \033[1;34m
CYAN            := \033[1;36m


######################
## MAKE FILE CONFIG ##
######################

all: $(NAME)

$(NAME): ${OBJS}
	@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
	$(CC) -o $(NAME) $(OBJS) -lreadline
	@echo "$(GREEN)$(NAME) created ✔️"



clean:
		@rm -f $(OBJS)
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
		@rm -f $(NAME)
		@ echo "$(RED)Deleting $(CYAN)$(NAME) $(NAME_BONUS) $(CLR_RMV)binary ✔️"

re: fclean all

.PHONY: all clean fclean re
