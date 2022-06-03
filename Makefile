TARGET = pipex
BONUS_TARGET = pipex_bonus

SRC_DIR  = ./srcs
BUILD_DIR  = ./objs
INC_DIR = ./includes
LIBFT_DIR = ./libft
LIBFT_INC_DIR = ./libft/includes
BONUS_DIR = ./bonus

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
LD_FLAGS = -L ${LIBFT_DIR}
INCLUDES = -I ${INC_DIR} -I ${LIBFT_INC_DIR}
COMP = ${CC} ${CFLAGS}
MAKE_C = make -C
CLEAN_C = make clean -C
FCLEAN_C = make fclean -C
MKDIR = mkdir -p
RM = rm -rf

all: libftcreat ${TARGET}

libftcreat:
	@${MAKE_C} ${LIBFT_DIR}

bonus:
	@${MAKE_C} ${BONUS_DIR}
	@cp -R bonus/pipex_bonus .

${TARGET}: ${OBJS}
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

${BUILD_DIR}/%.o: %.c
	@${MKDIR} ${BUILD_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $< -o $@

clean:
	@${CLEAN_C} ${LIBFT_DIR}
	@${CLEAN_C} ${BONUS_DIR}
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@${FCLEAN_C} ${LIBFT_DIR}
	@${FCLEAN_C} ${BONUS_DIR}
	@${RM} ${TARGET}
	@${RM} ${BONUS_TARGET}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re bonus
