NAME=philo

SRCS=main.c philo.c philo_operations.c philo_utils.c philo_forks.c utils.c
OBJS=$(SRCS:.c=.o)

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

#ARG					=	5 800 200 200   # No philosopher should die.
#ARG					=	5 800 200 200 7 # No philosopher should die.
#ARG					=	4 410 200 200   # No philosopher should die.
#ARG					=	4 310 200 100 7 # One philosopher should die.
#ARG					=	1 800 200 200   # The philosopher should not eat and should die
#ARG					=	5 410 200 100 7 # One philosopher should die.
#ARG					=	5 120 80 80 	# Moana tolds all will die
#ARG					=	2 200 50 50 1

test: re
	@ ./$(NAME) $(ARG)

valgrind:				re
						valgrind --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(NAME) $(ARG)

helgrind:				re
						valgrind --tool=helgrind ./$(NAME) $(ARG)
