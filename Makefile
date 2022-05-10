NAME = pipex
OBJ_DIR  = ./objs
CC = clang
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf
SRCS =	pipex_clean_end.c \
		pipex_exec.c \
		pipex_main.c \
		pipex_tokenizer.c
OBJS = ${addprefix ${OBJ_DIR}/,${SRCS:.c=.o}}

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -o $@ -c $<

$(NAME): ${OBJS}
	@make -C libft
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft
	@echo "${NAME} created"

all: ${NAME}

clean:
	@make clean -C libft
	@${RM} ${OBJ_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${NAME}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re
