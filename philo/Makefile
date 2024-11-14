

##############################
#          PAINTING
##############################

CLR_RMV = \033[0m
RED	    = \033[1;31m
GREEN	= \033[1;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
CYAN	= \033[1;36m

##############################
#          CONFIGS
##############################

NAME = philo
CC = cc
CFLAGS = -Iincludes
EFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
RM	    = rm -rf

##############################
#          FILES
##############################

#vpath %.h includes
#vpath %.c src

HEADER = philo.h
SRCS = \
	  00_main.c \
	  01_init.c \
	  11_first_args_check.c \
	  21_parse_data.c \
	  31_create_philos_mem.c \
	  41_let_the_game_begin.c \
	  42_monitor.c \
	  61_stop_the_game.c \
	  71_mutex_init_and_destroy.c \
	  81_utils.c \
	  91_free_and_cleanup.c

OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(EFLAGS) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) $(EFLAGS) -c $< -o $@

##############################
#          RULES
##############################

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(CC) $(CFLAGS) $(EFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created[0m ✅"

te:	re
	@echo -n "./philo "; read args; ./philo $$args

hel:	re
	@echo -n "valgrind --tool=helgrind ./philo "; read args; ./philo $$args

drd:	re
	@echo -n "valgrind --tool=drd ./philo "; read args; ./philo $$args


.PHONY: clean
clean:
	@ $(RM) -f $(OBJ_DIR)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✅"


.PHONY: fclean
fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✅"


.PHONY: re
re : fclean all



