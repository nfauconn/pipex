TARGET = pipex_bonus

SRC_DIR  = ./srcs
BUILD_DIR  = ./objs
INC_DIR = ./includes
LIBFT = ../libft/

SRCS := \
		./srcs/bonus_clean_end.c \
		./srcs/bonus_clean_utils.c \
		./srcs/bonus_cmd_exec.c \
		./srcs/bonus_cmd_path.c \
		./srcs/bonus_cmd_tokenizer.c \
		./srcs/bonus_data_init.c \
		./srcs/bonus_data_fill.c \
		./srcs/bonus_handling.c \
		./srcs/bonus_main.c

OBJS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}:${INC_DIR}:${BUILD_DIR}:${LIBFT}

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
LD_FLAGS = -L ${LIBFT}
INCLUDES = -I includes -I ../libft/includes
COMP = ${CC} ${CFLAGS}
RM = rm -rf

all: libftcreat ${TARGET}

libftcreat:
	@make -C ${LIBFT}

${TARGET}: ${OBJS}
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${BUILD_DIR}
	@echo create: ${@:%=%}
	${COMP} ${INCLUDES} -c $< -o $@

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
