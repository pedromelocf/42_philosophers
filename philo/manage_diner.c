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
    (*diner)->philos = calloc(1, sizeof(t_philos) * (*diner)->data->nb_philos);
    (*diner)->fork = calloc(1, sizeof(t_fork) * (*diner)->data->nb_philos);
    (*diner)->start_time = get_time_stamp();
    while (i < (*diner)->data->nb_philos)
    {
        (*diner)->philos[i] = calloc(1, sizeof(t_philos));
		(*diner)->philos[i]->last_meal = calloc(1, sizeof(t_last_meal));
        (*diner)->philos[i]->philo_alive = calloc(1, sizeof(t_alive));
        (*diner)->philos[i]->philo_id = i + 1;
        (*diner)->philos[i]->last_meal->time_since_last_meal = (*diner)->start_time;
		pthread_mutex_init(&(*diner)->philos[i]->last_meal->last_meal_mutex, NULL);
		(*diner)->philos[i]->nb_meals_done = 0;
        (*diner)->philos[i]->start_time = (*diner)->start_time;
        pthread_mutex_init(&(*diner)->philos[i]->philo_alive->alive_mutex, NULL);
        (*diner)->philos[i]->philo_alive->alive = TRUE;
		(*diner)->philos[i]->satisfied = FALSE;
        (*diner)->philos[i]->data = (*diner)->data;
        pthread_mutex_init(&(*diner)->fork[i].fork_mutex, NULL);
		(*diner)->fork[i].state = NOT_IN_USE;
		if (i % 2  == 0)
		{
			(*diner)->philos[i]->left_fork = &(*diner)->fork[i];
			(*diner)->philos[i]->right_fork = &(*diner)->fork[i + 1];
		}
		else
		{
			(*diner)->philos[i]->left_fork = &(*diner)->fork[i];
			(*diner)->philos[i]->right_fork = &(*diner)->fork[i - 1];
		}
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
        free((*diner)->supervisor);
    while (i < nb_philos)
    {
        pthread_mutex_destroy(&(*diner)->fork[i].fork_mutex);
        pthread_mutex_destroy(&(*diner)->philos[i]->philo_alive->alive_mutex);
		pthread_mutex_destroy(&(*diner)->philos[i]->last_meal->last_meal_mutex);
		i++;
    }
    if ((*diner)->philos)
        free((*diner)->philos);
    if ((*diner)->fork)
        free((*diner)->fork);
    if(*diner)
        free(*diner);
}
