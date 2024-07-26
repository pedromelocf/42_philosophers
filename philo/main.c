#include "philosophers.h"

static void     init_diner(t_diner **diner, int argc, char **argv);
static int      ft_atoi(const char *nptr);
static void 	handle_exit(char *str, int status);
static void     dining(t_diner **diner);
static void		*philos_routine(void *arg);
static void		*supervisor_routine(void *arg);
static void 	clean_diner(t_diner **diner);
static void 	sleeping(int philo_id, t_diner **diner);
static void 	taking_fork(int philo_id, t_diner **diner);
static void 	eating(int philo_id, t_diner **diner);
static void 	thinking(int philo_id, t_diner **diner);
static long int get_time_stamp(void);

int main(int argc, char **argv)
{
    t_diner    *diner;

    init_diner(&diner, argc, argv);
    dining(&diner);
	clean_diner(&diner);
    return (0);
}

static long int get_time_stamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	*supervisor_routine(void *arg)
{
    t_diner **diner;
	int i;

    diner = (t_diner **)arg;
    while ((*diner)->supervisor->alive)
    {
		i = 0;
		while (i < (*diner)->data->nb_philos && (*diner)->supervisor->alive)
		{
			pthread_mutex_lock(&(*diner)->philos[i].philo_mutex);
			if (get_time_stamp() - (*diner)->philos[i].time_since_beggin_last_meal > (*diner)->data->time_to_die)
			{
				printf("SUP OWN THIS SH*T!\n\n");
				(*diner)->supervisor->alive = FALSE;
				pthread_mutex_unlock(&(*diner)->philos[i].philo_mutex);
				break;
			}
			pthread_mutex_unlock(&(*diner)->philos[i].philo_mutex);
			i++;
			usleep(1000100);
		}
    }
    return(NULL);
}

static void	*philos_routine(void *arg)
{
    t_diner **diner;

    diner = (t_diner **)arg;
    while ((*diner)->supervisor->alive)
    {
		if((*diner)->philos->philo_id % 2 == 0)
			sleeping((*diner)->philos->philo_id, diner);
		taking_fork((*diner)->philos->philo_id, diner);
		eating((*diner)->philos->philo_id, diner);
		sleeping((*diner)->philos->philo_id, diner);
		thinking((*diner)->philos->philo_id, diner);
    }
    return (NULL);
}

static void eating(int philo_id, t_diner **diner)
{
	printf(EATING, get_time_stamp() - (*diner)->time, philo_id);
	(*diner)->philos->time_since_beggin_last_meal = get_time_stamp();
	usleep((*diner)->data->time_to_eat / 1000);
	(*diner)->philos->nb_meals_done++;
	pthread_mutex_unlock(&(*diner)->philos[philo_id].philo_mutex);
	pthread_mutex_unlock(&(*diner)->philos[philo_id].left_fork->fork_mutex);
	pthread_mutex_unlock(&(*diner)->philos[philo_id].right_fork->fork_mutex);
}

static void thinking(int philo_id, t_diner **diner)
{
	printf(THINKING, get_time_stamp() - (*diner)->time, philo_id);
	usleep(1);
}

static void taking_fork(int philo_id, t_diner **diner)
{
	pthread_mutex_lock(&(*diner)->philos[philo_id].philo_mutex);
	pthread_mutex_lock(&(*diner)->philos[philo_id].left_fork->fork_mutex);
	pthread_mutex_lock(&(*diner)->philos[philo_id].right_fork->fork_mutex);
	printf(TAKEN_FORK, get_time_stamp() - (*diner)->time, philo_id);
}

static void sleeping(int philo_id, t_diner **diner)
{
	printf(SLEEPING, get_time_stamp() - (*diner)->time, philo_id);
	usleep((*diner)->data->time_to_sleep / 1000);
}

static void dining(t_diner **diner)
{
	int i = 0;

	pthread_create(&(*diner)->supervisor->supervisor_pthread, NULL, &supervisor_routine, diner);
	while (i < (*diner)->data->nb_philos)
	{
		(*diner)->philos->time_since_beggin_last_meal = get_time_stamp();
		pthread_create(&(*diner)->philos[i].philo_pthread, NULL, &philos_routine, diner);
		i++;
	}
	pthread_join((*diner)->supervisor->supervisor_pthread, NULL);
	i = 0;
	while (i < (*diner)->data->nb_philos)
	{
		pthread_join((*diner)->philos[i].philo_pthread, NULL);
		i++;
	}
}

static void    init_diner(t_diner **diner, int argc, char **argv)
{
    short int i = 0;

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
	(*diner)->time = get_time_stamp();
	pthread_mutex_init(&(*diner)->supervisor->supervisor_mutex, NULL);
    (*diner)->philos = calloc(1, sizeof(t_philos) * (*diner)->data->nb_philos);
    (*diner)->fork = calloc(1, sizeof(t_fork) * (*diner)->data->nb_philos);
    while (i < (*diner)->data->nb_philos)
    {
		pthread_mutex_init(&(*diner)->philos[i].philo_mutex, NULL);
        (*diner)->philos[i].philo_id = i + 1;
        (*diner)->philos[i].time_since_beggin_last_meal = 0;
        (*diner)->philos[i].nb_meals_done = 0;
        (*diner)->philos[i].left_fork = &(*diner)->fork[i + 1];
        (*diner)->philos[i].right_fork = &(*diner)->fork[i + 2 % (*diner)->data->nb_philos];
        pthread_mutex_init(&(*diner)->fork[i].fork_mutex, NULL);
        i++;
    }
}

static void clean_diner(t_diner **diner)
{
	short int nb_philos = (*diner)->data->nb_philos;
	short int i = 0;

	if ((*diner)->data)
		free((*diner)->data);
	if ((*diner)->supervisor)
	{
		pthread_mutex_destroy(&(*diner)->supervisor->supervisor_mutex);
		free((*diner)->supervisor);
	}
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&(*diner)->philos[i].philo_mutex);
		pthread_mutex_destroy(&(*diner)->fork[i].fork_mutex);
		i++;
	}
	if ((*diner)->philos)
		free((*diner)->philos);
	if ((*diner)->fork)
		free((*diner)->fork);
	if(*diner)
		free(*diner);
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
