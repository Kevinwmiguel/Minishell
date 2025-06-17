NAME 	= minishell

CC 		= cc

CFLAGS 	= -Wall -Wextra -Werror -g -I../pipex/srcs -Iincludes #-fsanitize=address

OBJ_DIR = objects
OBJECTS= $(SRC:sources/%.c=%.o)

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

SRCS 	=	src/*.c \
			src/utils/*.c \
			src/core/*.c \
			src/parsing/*.c

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
	@$(CC) $(CFLAGS) $(SRCS) -o $@ $(LINKS)
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

r:
	make re && clear && ./minishell

v:
	make re && clear  && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --suppressions=readline.supp ./minishell

re: fclean all
