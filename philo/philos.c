#include "philosophers.h"

void taking_fork(t_philos *philos)
{
    pthread_mutex_lock(&philos->philo_mutex);
    if (philos->philo_id % 2 != 0)
    {
        pthread_mutex_lock(&philos->left_fork->fork_mutex);
        pthread_mutex_lock(&philos->right_fork->fork_mutex);
    }
    if (philos->philo_id % 2 == 0)
    {
        pthread_mutex_lock(&philos->right_fork->fork_mutex);
        pthread_mutex_lock(&philos->left_fork->fork_mutex);
    }
    printf(TAKEN_FORK, get_time_stamp() - philos->start_time, philos->philo_id);
    usleep(philos->data->time_to_eat * 1000);
}

void eating(t_philos *philos)
{
    printf(EATING, get_time_stamp() - philos->start_time, philos->philo_id);
    philos->time_since_beggin_last_meal = get_time_stamp();
    philos->nb_meals_done++;
    pthread_mutex_unlock(&philos->left_fork->fork_mutex);
    pthread_mutex_unlock(&philos->right_fork->fork_mutex);
    pthread_mutex_unlock(&philos->philo_mutex);
}

void sleeping(t_philos *philos)
{
    printf(SLEEPING, get_time_stamp() - philos->start_time, philos->philo_id);
    usleep(philos->data->time_to_sleep / 2 * 1000);
}

void thinking(t_philos *philos)
{
    printf(THINKING, get_time_stamp() - philos->start_time, philos->philo_id);
    usleep(1);
}
