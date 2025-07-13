NAME 	= minishell

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g -I../pipex/srcs -Iincludes

SRC_DIR = src
OBJ_DIR = objects
SRCS	= $(shell find $(SRC_DIR) -name '*.c') \
		  get_next_line/get_next_line.c \
		  get_next_line/get_next_line_utils.c
OBJS	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

LINKS = $(LIBFT) -lreadline

# Cores e mensagens
Color_Off='\033[0m'
IGreen='\033[0;92m'
IYellow='\033[0;93m'
ICyan='\033[0;96m'
MSG1 = @echo ${IGreen}"Compiled Successfully ✔︎"${Color_Off}
MSG2 = @echo ${IYellow}"Cleaned Successfully ✔︎"${Color_Off}
MSG3 = @echo ${ICyan}"Cleaned ${NAME} Successfully ✔︎"${Color_Off}

# Regra padrão
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKS)
	$(MSG1)

# Compilação de objetos
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Libft
$(LIBFT):
	@make -C $(LIBFT_PATH) all

# Limpeza
clean:
	@make -C $(LIBFT_PATH) clean
	@rm -rf $(OBJ_DIR)
	$(MSG2)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	$(MSG3)

# Atalhos
re: fclean all

r:
	make re && clear && ./minishell

v:
	make re && clear && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --suppressions=readline.supp ./minishell