NAME = pipex
OBJ_DIR  = ./objs
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf
SRCS = main.c
OBJS = ${addprefix ${OBJ_DIR}/,${SRCS:.c=.o}}

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -o $@ -c $<

$(NAME): ${OBJS}
	@${COMP} ${INCLUDES} ${OBJS} -o ${NAME}
	@echo "${NAME} created"

all: ${NAME}

clean:
	@${RM} ${OBJ_DIR}
	@echo "objs deleted"

fclean: clean
	@${RM} ${NAME}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re
