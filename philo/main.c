#include "philosophers.h"

static void    init_diner(t_diner **diner, int argc, char **argv);
static int      ft_atoi(const char *nptr);
static void 	handle_exit(char *str, int status);
static void		*philo_routine(void *arg);
static void		*supervisor_routine(void *arg);


int main(int argc, char **argv)
{
    t_diner    *diner;

    init_diner(&diner, argc, argv);
    return (0);
}

static void    init_diner(t_diner **diner, int argc, char **argv)
{
    int i = 0;

	if(argc != 5 && argc != 6)
		handle_exit(EXPECTED_ARGS, 1);
    *diner = calloc(1, sizeof(t_diner));
    (*diner)->data = calloc(1, sizeof(t_data));
    (*diner)->data->nb_philos = ft_atoi(argv[1]);
    (*diner)->data->time_to_die = ft_atoi(argv[2]);
    (*diner)->data->time_to_eat = ft_atoi(argv[3]);
    (*diner)->data->time_to_sleep = ft_atoi(argv[4]);
    (*diner)->data->nb_meals_todo = -1;
	if (argc == 6)
		(*diner)->data->nb_meals_todo = ft_atoi(argv[5]);
    (*diner)->supervisor = calloc(1, sizeof(t_supervisor));
    (*diner)->supervisor->alive = TRUE;
    (*diner)->supervisor->dining_info = *diner;
    (*diner)->philos = calloc(1, sizeof(t_philos) * (*diner)->data->nb_philos);
    (*diner)->fork = calloc(1, sizeof(t_fork) * (*diner)->data->nb_philos);
    while (i < (*diner)->data->nb_philos)
    {
        (*diner)->philos[i].alive = TRUE;
        (*diner)->philos[i].philo_id = i + 1;
        (*diner)->philos[i].time_since_beggin_last_meal = 0;
        (*diner)->philos[i].nb_meals_done = 0;
        (*diner)->philos[i].left_fork = &(*diner)->fork[i + 1];
        (*diner)->philos[i].right_fork = &(*diner)->fork[i + 2 % (*diner)->data->nb_philos];
        pthread_mutex_init(&(*diner)->fork[i].fork_mutex, NULL);
        (*diner)->fork[i].status = NOT_IN_USE;
        i++;
    }
}

//
// int main(int argc, char **argv)
// {
// 	t_test *test;
// 	pthread_t thread1;
// 	pthread_t thread2;
// 	pthread_t thread3;
//
// 	test =  malloc(sizeof(t_test));
// 	test->i = 0;
// 	test->stop = 0;
// 	pthread_mutex_init(&test->mutex, NULL);
// 	pthread_create(&thread1, NULL, &philo_routine, test);
// 	pthread_create(&thread2, NULL, &philo_routine, test);
// 	pthread_create(&thread3, NULL, &supervisor_routine, test);
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);
// 	pthread_join(thread3, NULL);
// 	pthread_mutex_destroy(&test->mutex);
// 	return (0);
// }
//
// static void	*philo_routine(void *arg)
// {
// 	t_test *test = (t_test *)arg;
//
// 	while (test->i < 500000)
// 	{
// 		pthread_mutex_lock(&test->mutex);
// 		if(test->stop == 1)
// 		{
// 			pthread_mutex_unlock(&test->mutex);
// 			break;
// 		}
// 		printf("%d\n", test->i);
// 		test->i++;
// 		pthread_mutex_unlock(&test->mutex);
// 		usleep(1);
// 	}
// 	return (NULL);
// }
//
// static void	*supervisor_routine(void *arg)
// {
// 	t_test *test = (t_test *)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&test->mutex);
// 		if (test->i >= 34908)
// 		{
// 			printf("SUP!\n\n");
// 			test->stop = 1;
// 			pthread_mutex_unlock(&test->mutex);
// 			break;
// 		}
// 		pthread_mutex_unlock(&test->mutex);
// 	}
// 	return(NULL);
// }

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
