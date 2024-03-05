NAME=philo

SRCS=main.c philo.c philo_operations.c philo_utils.c philo_forks.c utils.c
OBJS=$(SRCS:.c=.o)

DEBUG_FLAGS=-fsanitize=thread -g
COMPILER= cc -Wall -Wextra -Werror

.c.o:
	@ $(COMPILER) -c $< -o $(<:.c=.o)
	@ printf "compiling $<                                \r"

$(NAME): $(OBJS)
	@ printf "\ncompile success\n"
	@ $(COMPILER) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(NAME)

re: fclean $(NAME)



#ARG					=	1 800 200 200   # The philosopher should not eat and should die
#ARG					=	5 800 200 200   # No philosopher should die.
#ARG					=	5 800 200 200 7 # No philosopher should die.
#ARG					=	4 410 200 200   # No philosopher should die.
#ARG					=	4 310 200 100 7 # One philosopher should die.
#ARG					=	4 400 200 200 # No philosopher should die.

#ARG					=	5 410 200 100 7 # One philosopher should die.
#ARG					=	5 120 80 80 	# Moana tolds all will die
#ARG					=	2 200 50 50 1
#ARG					=	50 1000 60 60 1
#ARG					=	2 110 50 50 2

test: re
	@ ./$(NAME) $(ARG)

valgrind:				re
						valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(NAME) $(ARG)

hell:				re
						valgrind --tool=helgrind ./$(NAME) $(ARG)
