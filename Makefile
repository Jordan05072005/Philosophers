SRC = mandatory/main.c mandatory/life.c mandatory/init.c mandatory/utils.c mandatory/del.c mandatory/ft_split.c mandatory/brain.c

OBJ = ${SRC:.c=.o}

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o}

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
NAME = philo

all : ${NAME}

${NAME}: ${OBJ}
	@${CC} ${FLAGS} ${OBJ} -o philo
	@echo "Arguments : \n -number_of_philosophers_and_fork\n -time_to_die\n -time_to_eat\n -time_to_sleep\n -[number_of_times_each_philosopher_must_eat] (optional)"

clean : 
	@${RM} mandatory/*o

fclean : clean
	@${RM} ${NAME}

re : fclean all clean

.PHONY: all clean fclean re