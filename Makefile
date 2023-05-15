SRCS	=	main.c\
			\
			ft_atoi.c\
			is_digit_str.c\
			ft_get_time.c\
			ft_usleep.c\
			philo_error.c\
			philo_init.c\
			data_init.c\
			philo_runner.c\
			check_death.c\

DIR_SRCS = src/

DIR_OBJS = .objs/

DIR_HEAD = ./

OBJS	=	${SRCS:%.c=${DIR_OBJS}%.o}

CC	=	gcc-10

MKDIR	=	mkdir -p

HEADERS	=	philo.h

NAME	=	philo

CFLAGS	= -Wall -Wextra -Werror -g3

all :		${NAME}

clean :
			rm -rf ${DIR_OBJS}

fclean :	clean
			rm -rf ${NAME}

re :		fclean
			$(MAKE) all

${DIR_OBJS}%.o:		${DIR_SRCS}%.c    ${addprefix ${DIR_HEAD}, ${HEADERS}} | ${DIR_OBJS}
					${CC} ${CFLAGS} -I ${DIR_HEAD} -c $< -o $@

${DIR_OBJS}			:
					${MKDIR} ${DIR_OBJS}

${NAME}	:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} -lpthread 

.PHONY:		all clean fclean re