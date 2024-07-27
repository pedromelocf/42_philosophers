#include "philosophers.h"

void    init_diner(t_diner **diner, int argc, char **argv)
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
        (*diner)->philos[i] = calloc(1, sizeof(t_philos));
        pthread_mutex_init(&(*diner)->philos[i]->philo_mutex, NULL);
        (*diner)->philos[i]->left_fork = &(*diner)->fork[i + 1];
        (*diner)->philos[i]->right_fork = &(*diner)->fork[i + 2 % (*diner)->data->nb_philos];
        (*diner)->philos[i]->philo_id = i + 1;
        (*diner)->philos[i]->time_since_beggin_last_meal = (*diner)->time;
        (*diner)->philos[i]->nb_meals_done = 0;
        (*diner)->philos[i]->init_thread_time  = 0;
        (*diner)->philos[i]->init_diner_time = (*diner)->time;
        (*diner)->philos[i]->philo_alive = TRUE;
        (*diner)->philos[i]->data = (*diner)->data;
        pthread_mutex_init(&(*diner)->fork[i].fork_mutex, NULL);
        i++;
    }
}

void clean_diner(t_diner **diner)
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
        pthread_mutex_destroy(&(*diner)->philos[i]->philo_mutex);
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
