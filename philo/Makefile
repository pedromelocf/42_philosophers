#PHILO
NAME = philo
PHILO_SRC_PATH = ./
PHILO_INCLUDES = ./philosophers.h
PHILO_OBJ = $(addprefix $(PHILO_SRC_PATH), $(PHILO_SRCS:.c=.o))

PHILO_SRCS = main.c

#FLAGS
FLAGS = -Wall -Werror -Wextra -pthread
CC = gcc -fsanitize=thread

#MESSAGES
MESSAGE1 = "------------------Compiling philo Objects!-------------------"
MESSAGE2 = "---------------Objects Compiled Successfully!----------------"
MESSAGE3 = "---------------./philo Compiled Successfully!----------------"
MESSAGE4 = "-------------------- All Objects cleaned!--------------------"
MESSAGE5 = "-------------------- All Binaries cleaned!-------------------"

all: $(NAME)

$(NAME): $(PHILO_OBJ)
	@ echo ' '
	@ echo $(MESSAGE1)
	@ $(CC) $(FLAGS) $(PHILO_OBJ) -o $(NAME)
	@ echo ' '
	@ echo $(MESSAGE2)
	@ echo ' '
	@ echo $(MESSAGE3)
	@ echo ' '
	@ echo ' '

$(PHILO_SRC_PATH)%.o: $(PHILO_SRC_PATH)%.c $(PHILO_INCLUDES)
	@ $(CC) $(FLAGS) -c $< -o $@

clean :
	@ rm -f $(PHILO_OBJ)
	@ echo ' '
	@ echo $(MESSAGE4)
	@ echo ' '

fclean : clean
	@ rm -f $(NAME)
	@ echo $(MESSAGE5)
	@ echo ' '

re : fclean all

.PHONY: all clean fclean re
