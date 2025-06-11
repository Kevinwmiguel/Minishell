NAME 	= minishell

CC 		= cc

CFLAGS 	= -Wall -Wextra -Werror -g -I../pipex/srcs #-fsanitize=address

OBJ_DIR = objects
OBJECTS= $(SRC:sources/%.c=%.o)

LIBFT_PATH = ../libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS 	=	minishell.c\
			../builtins/build_echo.c\
			../builtins/builtins.c\
			../builtins/build_cd.c\
			../builtins/build_cd_utils.c\
			../builtins/build_pwd.c\
			../builtins/build_export.c\
			../builtins/build_export_utils1.c\
			../builtins/build_export_utils2.c\
			../builtins/build_export_utils3.c\
			../builtins/build_unset.c\
			../builtins/echo_expansioner.c\
			../builtins/build_unset_utils.c\
			../builtins/build_env.c\
			../builtins/build_exit.c\
			../builtins/aux.c\
			../builtins/expansions2.c\
			../signals/signals.c\
			commands.c\
			minishell5.c\
			../libft/libft.a \
			../pipex/srcs/aux.c ../pipex/srcs/aux2.c \
			../pipex/srcs/checkers.c ../pipex/srcs/children.c \
			../pipex/srcs/closes.c ../pipex/srcs/ft_free_split.c \
			../pipex/srcs/main.c ../pipex/srcs/path.c \
			../pipex/srcs/pipex.c ../pipex/srcs/here_red.c \
			../pipex/srcs/left_tokens.c \
			../builtins/build_export_helper.c\
			../builtins/pipe_verify.c ../pipex/srcs/inits.c \
			../pipex/srcs/here_doc.c ../pipex/srcs/creator_helper.c\
			minishell2.c minishell3.c minishell4.c\
			../builtins/build_echo2.c ../builtins/extra_frees.c\
			../builtins/env_to_echo.c ../builtins/aux2.c\
			../builtins/quotes_dealer.c ../builtins/build_echo3.c
#../pipex/srcs/paths.c
Color_Off='\033[0m'       # Text Reset

IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
ICyan='\033[0;96m'        # Cyan

LINKS = $(LIBFT) -lreadline

MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(SRCS) -o $@ $(LINKS) ../get_next_line/get_next_line.c ../get_next_line/get_next_line_utils.c
	$(MSG1);
	clear

%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

$(LIBFT):
	@make -C $(LIBFT_PATH) all

$(OBJ_DIR)/%.o: sources/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean
	@rm -f *.o
	$(MSG2);

fclean: clean
	make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME) $(OBJECTS)
	$(MSG3);

re: fclean all
