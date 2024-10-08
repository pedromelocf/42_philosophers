#PHILO
NAME = philo
PHILO_SRC_PATH = ./
PHILO_INCLUDES = ./philosophers.h
PHILO_OBJ_PATH = philos_object
PHILO_OBJ = $(addprefix $(PHILO_OBJ_PATH)/, $(notdir $(PHILO_SRCS:.c=.o)))

PHILO_SRCS = clean_utils.c \
	dining.c \
	main.c \
	manage_data.c \
	manage_data_utils.c \
	philos.c \
	routines.c \
	routines_utils.c \
	safe_print.c \
	taking_forks_aux.c \
	utils.c

FLAGS = -Wall -Werror -Wextra -pthread -fsanitize=thread
CC = gcc

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

$(PHILO_OBJ_PATH)/%.o: $(PHILO_SRC_PATH)/%.c $(PHILO_INCLUDES)
	@ mkdir -p $(PHILO_OBJ_PATH)
	@ $(CC) $(FLAGS) -c $< -o $@

clean :
	@ rm -rf $(PHILO_OBJ_PATH)
	@ echo ' '
	@ echo $(MESSAGE4)
	@ echo ' '

fclean : clean
	@ rm -f $(NAME)
	@ echo $(MESSAGE5)
	@ echo ' '

re : fclean all

.PHONY: all clean fclean re
