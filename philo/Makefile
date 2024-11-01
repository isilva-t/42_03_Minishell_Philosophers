

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
EFLAGS = -Wall -Wextra -Werror
RM	    = rm -rf

##############################
#          FILES
##############################

vpath %.h includes
vpath %.c src

HEADER = philo.h
SRCS = \
	  src/main.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) $(EFLAGS) -c $< -o $@

##############################
#          RULES
##############################

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(EFLAGS) $(OBJS) -o $(NAME)



.PHONY: clean
clean:
	@ $(RM) -f $(OBJS)
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✅"


.PHONY: fclean
fclean: clean
	@ $(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✅"


.PHONY: re
re : fclean all



