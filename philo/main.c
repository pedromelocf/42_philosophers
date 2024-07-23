#include "philosophers.h"

static void     init_philo(t_philo **philo, int argc, char **argv);
static int      ft_atoi(const char *nptr);
static void 	handle_exit(char *str, int status);

int main(int argc, char **argv)
{
    t_philo    *philo;

    init_philo(&philo, argc, argv);
	printf(THINKING, philo->data->nb_philos, philo->philo_id);
	//philo = philo->next;
    return (0);
}

static void    init_philo(t_philo **philo, int argc, char **argv)
{
	int		i;
	t_data	*data;

	i = 0;
    if(argc != 5 && argc != 6)
		handle_exit(EXPECTED_ARGS, 1);
	data = &(t_data){
			ft_atoi(argv[1]), ft_atoi(argv[2]),ft_atoi(argv[3]),
			ft_atoi(argv[4]), 0
	};
	if (argc == 6)
		data->nb_meals_todo = ft_atoi(argv[5]);
	while (i++ < data->nb_philos)
	{
		(*philo) = malloc(sizeof(t_philo));
		memset((*philo), 0, sizeof(t_philo));
		(*philo)->data = data;
		(*philo)->nb_meals_done = 0;
		(*philo)->philo_id = (short int)i;
		(*philo) = (*philo)->next;
	}
}

static void handle_exit(char *str, int status)
{
    printf("%s", str);
    exit(status);
}

static int	ft_atoi(const char *nptr)
{
    size_t	i;
    size_t	c;
    size_t	sign;

    c = 0;
    i = 0;
    sign = 1;
    while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign *= -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        c = c * 10 + nptr[i] - '0';
        i++;
    }
    return (sign * c);
}
