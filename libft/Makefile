NAME = libft.a

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_strlen.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strcmp.c ft_strncmp.c ft_strrchr.c ft_memcmp.c ft_memchr.c ft_strnstr.c ft_atoi.c	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c alpha_num.c

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS = $(SRC:.c=.o)

OBJECTS_BONUS = $(BONUS:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJECTS) $(OBJECTS_BONUS)
	ar rcs $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all

bonus:  $(OBJECTS_BONUS) $(OBJECTS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re bonus
