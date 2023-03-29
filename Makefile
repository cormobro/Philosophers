SRCS = $(addprefix Sources/, main.c error.c utils.c checker.c mutex.c threads.c utils_thread.c)

NAME = philosophers

INC = -I ./

FLAGS = -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

${NAME} : ${OBJS}
			gcc ${FLAGS} ${INC} $(OBJS) -lpthread -g3 -fsanitize=address  -o $(NAME)

all : ${NAME}

%.o:%.c
		gcc ${FLAGS} -c $< -o $@

clean :
		rm -rf ${OBJS}

fclean : clean
		rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re NAME
