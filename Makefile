NAME		=	philo

DIR_OBJS	=	./

DIR_SRCS	=	./src/

HEAD	=	philo.h

SRCS	=	main.c\
			\
			${DIR_SRCS}ft_atoi.c\
			${DIR_SRCS}is_digit_str.c\
			${DIR_SRCS}ft_get_time.c\
			${DIR_SRCS}ft_usleep.c\
			${DIR_SRCS}philo_error.c\
			${DIR_SRCS}philo_init.c\
			${DIR_SRCS}data_init.c\
			${DIR_SRCS}philo_runner.c\
			${DIR_SRCS}check_death.c\


OBJS	=	${SRCS:%.c=${DIR_OBJS}%.o}


CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I/${HEAD} -g3 #-fsanitize=address 
#-O3 -g -pg 


RM		=	rm -rf
MKDIR	=	mkdir -p


all		:	${NAME}


${NAME}	:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -lpthread 


clean			:
					${RM} ${OBJS}

fclean			:	clean
					${RM} ${NAME}

re				:	fclean
					${MAKE} all
normy:
				norminette $(SRCS)
				norminette $(HEAD)

.PHONY:	all clean fclean re fclean_all normy 
