TARGET = pipex

BUILD_DIR  = ./objs
SRC_DIR  = ./srcs

SRCS := \
		./srcs/clean_end.c \
		./srcs/clean_utils.c \
		./srcs/cmd_exec.c \
		./srcs/cmd_path.c \
		./srcs/cmd_tokenizer.c \
		./srcs/data_init.c \
		./srcs/data_fill.c \
		./srcs/main.c

OBJS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}:${INC_DIR}:${BUILD_DIR}

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LD_FLAGS = -L libft
INCLUDES = -I includes -I libft/includes
COMP = ${CC} ${CFLAGS}
RM = rm -rf

all: libftcreat ${TARGET}

libftcreat:
	@make -C libft

${TARGET}: ${OBJS}
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${BUILD_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $< -o $@

clean:
	@make clean -C libft
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${TARGET}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re bonus
