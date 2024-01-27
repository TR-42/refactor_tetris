NAME	=	tetris

SRCS_DIR	=	./srcs
OBJS_DIR	=	./objs
DEPS_DIR	=	./deps

SRCS_MAIN	=\
	main.c\

SRCS_OTHER	=\
	action_funcs.c\
	block_factory.c\
	print_funcs.c\
	tetromino_funcs.c\
	time_funcs.c\

SRC_FILES	=\
	$(SRCS_MAIN)\
	$(SRCS_OTHER)\

LINKS	=\
	-lncurses\

INCLUDES	=\
	-I./headers\

CFLAGS	=	-Wall -Wextra -Werror -std=c11 -fsanitize=address -g -MMD -MP -MF $(DEPS_DIR)/$*.d

SRCS	=	$(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS	=	$(addprefix $(OBJS_DIR)/, $(SRC_FILES:.c=.o))
DEPS	=	$(addprefix $(DEPS_DIR)/, $(SRC_FILES:.c=.d))

# ref: https://qiita.com/dmystk/items/3f82b1eb763c9b9b47e8

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(LINKS) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJS_DIR):
	@mkdir -p $@
$(DEPS_DIR):
	@mkdir -p $@

$(DEPS):
-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(DEPS_DIR)/%.d | $(OBJS_DIR) $(DEPS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean: cleanobjs cleandeps cleandir
cleanobjs:
	$(RM) $(OBJS)
cleandeps:
	$(RM) $(DEPS)
cleandir:
	if [ -z "$(shell ls -A $(OBJS_DIR))" ]; then rmdir $(OBJS_DIR); fi
	if [ -z "$(shell ls -A $(DEPS_DIR))" ]; then rmdir $(DEPS_DIR); fi
cleanf:	cleanobjs cleandeps
	$(RM) -r $(OBJS_DIR) $(DEPS_DIR)

fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
