#include "philosophers.h"

void eating(t_philos *philos)
{
    printf(EATING, get_time_stamp() - philos->init_diner_time, philos->philo_id);
    philos->time_since_beggin_last_meal = get_time_stamp();
    usleep(philos->data->time_to_eat * 1000);
    philos->nb_meals_done++;
    pthread_mutex_unlock(&philos->philo_mutex);
    pthread_mutex_unlock(&philos->left_fork->fork_mutex);
    pthread_mutex_unlock(&philos->right_fork->fork_mutex);
}

void thinking(t_philos *philos)
{
    printf(THINKING, get_time_stamp() - philos->init_diner_time, philos->philo_id);
    usleep(1);
}

void taking_fork(t_philos *philos)
{
    pthread_mutex_lock(&philos->philo_mutex);
    pthread_mutex_lock(&philos->left_fork->fork_mutex);
    pthread_mutex_lock(&philos->right_fork->fork_mutex);
    printf(TAKEN_FORK, get_time_stamp() - philos->init_diner_time, philos->philo_id);
}

void sleeping(t_philos *philos)
{
    printf(SLEEPING, get_time_stamp() - philos->init_diner_time, philos->philo_id);
    usleep(philos->data->time_to_sleep / 2 * 1000);
}
