#include "philosophers.h"

static void     init_philo(t_philo **philo, int argc, char **argv);
static int      ft_atoi(const char *nptr);
static void handle_exit(char *str, int status);

int main(int argc, char **argv)
{
    t_philo    *philo;

    init_philo(&philo, argc, argv);
    printf(THINKING, philo->data->nb_philos, philo->philo_id);
    return (0);
}

static void    init_philo(t_philo **philo, int argc, char **argv)
{
    if (argc != 5 && argc != 6)
        handle_exit(EXPECTED_ARGS, 1);
    memset(*philo, 0, sizeof(t_philo));
    (*philo)->data->nb_philos = ft_atoi(argv[1]);
    (*philo)->data->time_to_die = ft_atoi(argv[2]);
    (*philo)->data->time_to_eat = ft_atoi(argv[3]);
    (*philo)->data->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        (*philo)->data->nb_philos = ft_atoi(argv[5]);
    (*philo)->nb_meals_done = 0;
    (*philo)->philo_id = 1;
}

static void handle_exit(char *str, int status)
{
    printf(str);
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
