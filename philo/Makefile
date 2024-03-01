NAME=philo

SRCS=main.c philo.c philo_operations.c philo_utils.c utils.c
OBJS=$(SRCS:.c=.o)

COMPILER= cc -Wall -Wextra -Werror

.c.o:
	@ $(COMPILER) -c $< -o $(<:.c=.o)
	@ printf "compiling $<                                \r"

$(NAME): $(OBJS)
	@ printf "\ncompile success"
	@ $(COMPILER) $(OBJS) -o $(NAME)
	@ make clean

all: $(NAME)

clean:
	@ rm -f $(OBJS)

fclean: clean
	@ rm -f $(NAME)

re: fclean $(NAME)
