#include "philosophers.h"

static void    init_diner(t_diner **diner, int argc, char **argv);
static int      ft_atoi(const char *nptr);
static void 	handle_exit(char *str, int status);
static void     dining(t_diner **diner);
static void		*philos_routine(void *arg);
static void		*supervisor_routine(void *arg);


int main(int argc, char **argv)
{
    t_diner    *diner;

    init_diner(&diner, argc, argv);
    dining(&diner);
    return (0);
}

static void	*supervisor_routine(void *arg)
{
    t_diner **diner;

    diner = (t_diner **)arg;
    while (1)
    {
        pthread_mutex_lock(&(*diner)->philos[0].philo_mutex);
        if ((*diner)->philos[0].nb_meals_done >= (*diner)->data->nb_meals_todo)
        {
            (*diner)->supervisor->alive = FALSE;
            break;
        }
        usleep(1);
        pthread_mutex_unlock(&(*diner)->philos[0].philo_mutex);
    }
    return(NULL);
}

static void	*philos_routine(void *arg)
{
    t_diner **diner;

    diner = (t_diner **)arg;
    while (1)
    {
        if ((*diner)->supervisor->alive == FALSE)
        {
            printf("SUP OWNS!\n");
            break;
        }
        pthread_mutex_lock(&(*diner)->philos[0].philo_mutex);
        printf("%d\n", (*diner)->philos[0].nb_meals_done);
       (*diner)->philos[0].nb_meals_done++;
        pthread_mutex_unlock(&(*diner)->philos[0].philo_mutex);
        usleep(1);
    }
    return (NULL);
}

static void dining(t_diner **diner)
{
    pthread_create(&(*diner)->supervisor->supervisor_pthread, NULL, &supervisor_routine, diner);
    pthread_create(&(*diner)->philos->philo_pthread, NULL, &philos_routine, diner);
    pthread_join((*diner)->supervisor->supervisor_pthread, NULL);
    pthread_join((*diner)->philos->philo_pthread, NULL);
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
        pthread_mutex_init(&(*diner)->philos[i].philo_mutex, NULL);
        // pthread_mutex_init(&(*diner)->fork[i].fork_mutex, NULL);
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

//


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
