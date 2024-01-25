NAME	=	tetris

SRCS_DIR	=	./srcs
SRCS_MAIN	=\
	main.c\

SRCS_OTHER	=\
	functions.c\
	utils.c\

SRCS	=\
	$(addprefix $(SRCS_DIR)/, $(SRCS_MAIN))\
	$(addprefix $(SRCS_DIR)/, $(SRCS_OTHER))\

LINKS	=\
	-lncurses\

INCLUDES	=\
	-I./headers\

$(NAME): $(SRCS)
	$(CC) $(LINKS) $(INCLUDES) $^ -o $@
