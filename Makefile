NAME = pipex
OBJ_DIR  = ./objs
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf
SRCS =	clean_end.c \
		clean_utils.c \
		cmd_exec.c \
		cmd_path.c \
		cmd_tokenizer.c \
		data_init.c \
		data_fill.c \
		main.c
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
