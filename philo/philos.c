#include "philosophers.h"

void eating(int philo_id, t_diner **diner)
{
    printf(EATING, get_time_stamp() - (*diner)->time, philo_id);
    (*diner)->philos->time_since_beggin_last_meal = get_time_stamp();
    usleep((*diner)->data->time_to_eat / 1000);
    (*diner)->philos->nb_meals_done++;
    pthread_mutex_unlock(&(*diner)->philos[philo_id].philo_mutex);
    pthread_mutex_unlock(&(*diner)->philos[philo_id].left_fork->fork_mutex);
    pthread_mutex_unlock(&(*diner)->philos[philo_id].right_fork->fork_mutex);
}

void thinking(int philo_id, t_diner **diner)
{
    printf(THINKING, get_time_stamp() - (*diner)->time, philo_id);
    usleep(1);
}

void taking_fork(int philo_id, t_diner **diner)
{
    pthread_mutex_lock(&(*diner)->philos[philo_id].philo_mutex);
    pthread_mutex_lock(&(*diner)->philos[philo_id].left_fork->fork_mutex);
    pthread_mutex_lock(&(*diner)->philos[philo_id].right_fork->fork_mutex);
    printf(TAKEN_FORK, get_time_stamp() - (*diner)->time, philo_id);
}

void sleeping(int philo_id, t_diner **diner)
{
    printf(SLEEPING, get_time_stamp() - (*diner)->time, philo_id);
    usleep((*diner)->data->time_to_sleep / 1000);
}
