NAME = Minishell
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra #-fsanitize=thread
src = main.c\
		utils.c\
		parssing.c\
		ft_split.c\
		
OBJECTS = ${src:.c=.o}

all	:	$(NAME)

$(NAME):	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -lreadline -o $(NAME)
		
clean :
	$(RM) $(OBJECTS)
fclean : clean
	$(RM) $(NAME)
re : fclean all
.PHONY: all clean fclean re
