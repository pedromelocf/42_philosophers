#include "philosophers.h"

void taking_fork(t_philos *philos)
{
    printf(TAKEN_FORK, get_time_stamp() - philos->start_time, philos->philo_id);
}

void eating(t_philos *philos)
{
    printf(EATING, get_time_stamp() - philos->start_time, philos->philo_id);
    ft_usleep(philos->data->time_to_eat, philos);
    pthread_mutex_lock(&philos->nb_meals_done->mutex);
    philos->nb_meals_done->state++;
    pthread_mutex_unlock(&philos->nb_meals_done->mutex);

}

void sleeping(t_philos *philos)
{
    printf(SLEEPING, get_time_stamp() - philos->start_time, philos->philo_id);
    ft_usleep(philos->data->time_to_sleep, philos);
}

void thinking(t_philos *philos)
{
    printf(THINKING, get_time_stamp() - philos->start_time, philos->philo_id);
    usleep(1);
}
