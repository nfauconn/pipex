TARGET = pipex
BONUS_TARGET = pipex_bonus

LIBFT = -C libft
INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft

BUILD_DIR  = ./objs
SRC_DIR  = ./srcs

SRCS := \
		./srcs/bonus_handling.c \
		./srcs/clean_end.c \
		./srcs/clean_utils.c \
		./srcs/cmd_exec.c \
		./srcs/cmd_path.c \
		./srcs/cmd_tokenizer.c \
		./srcs/data_init.c \
		./srcs/data_fill.c \
		./srcs/handling.c \
		./srcs/main.c

BONUS_SRCS := \
		./srcs/bonus_clean_end.c \
		./srcs/bonus_clean_utils.c \
		./srcs/bonus_cmd_exec.c \
		./srcs/bonus_cmd_path.c \
		./srcs/bonus_cmd_tokenizer.c \
		./srcs/bonus_data_init.c \
		./srcs/bonus_data_fill.c \

OBJS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
BONUS_OBJS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${BONUS_SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}:${INC_DIR}:${BUILD_DIR}

################################################################################
#####                           COMPILER OPTIONS                           #####
################################################################################

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

################################################################################
#####                            LIBFT RULES                             #####
################################################################################

makelibft:
	@make ${LIBFT}
cleanlibft:
	@make clean ${LIBFT}
fcleanlibft:
	@make fclean ${LIBFT}

################################################################################
#####                            GENERAL RULES                             #####
################################################################################

all: makelibft ${TARGET}

bonus: makelibft ${BONUS_TARGET}

builddir:
	@mkdir -p ${BUILD_DIR}

${TARGET}: builddir ${OBJS}
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

${BUILD_DIR}/%.o: %.c
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $< -o $@

${BONUS_TARGET}: builddir ${OBJS} ${BONUS_OBJS}
	@${COMP} ${LD_FLAGS} ${OBJS} ${BONUS_OBJS} -o ${BONUS_TARGET} -lft
	@echo "${BONUS_TARGET} created"

clean: cleanlibft
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean fcleanlibft
	@${RM} ${TARGET}
	@${RM} ${BONUS_TARGET}
	@echo "program deleted"


################################################################################
#####                            BONUS RULES                               #####
################################################################################

#bonus: makelibft ${BONUS_TARGET}





re: fclean all

.PHONY: all clean fclean re bonus
