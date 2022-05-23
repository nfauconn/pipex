TARGET = pipex
BONUS_TARGET = pipex_bonus

INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft

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
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
DEPS := $(OBJS:.o=.d)
VPATH = $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

all: ${TARGET}

makelib:
	make -C libft

$(TARGET): makelib ${OBJS}
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"
#	@make -C libft

#${BONUS_TARGET}:${BONUS_OBJS}

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${BUILD_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $< -o $@

# Place dependency files in build directory
# automatically generate dependency rules
$(BUILD_DIR)%.d: %.c
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MD -MP -MT"$@" -MT"$(OBJS)" "$<"
# -MF  write the generated dependency rule to a file
# -MG  assume missing headers will be generated and don't stop with an error
# -MM  generate dependency rule for prerequisite, skipping system headers
# -MP  add phony target for each header to prevent errors when header is missing
# -MT  add a target to the generated dependency

clean:
	@make clean -C libft
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${TARGET}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re
