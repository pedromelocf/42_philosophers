#include "philosophers.h"

static int stop_diner(t_philos *philos);

void	*philos_routine(void *arg)
{
    t_philos *philos;

    philos = (t_philos *)arg;
    while (stop_diner(philos) != 1)
    {

        usleep(1000);
    }

    return(NULL);
}

void	*supervisor_routine(void *arg)
{
    t_diner **diner;
    int i;

    diner = (t_diner **)arg;
    i = 0;
    while (i < (*diner)->data->nb_philos)
    {
        pthread_mutex_lock(&(*diner)->philos[i].last_meal->mutex);
        if (get_time_stamp() - (*diner)->philos[i].last_meal->state < (*diner)->data->time_to_die)
        {
            pthread_mutex_lock(&(*diner)->supervisor->mutex);
            (*diner)->supervisor->alive = FALSE;
            printf(DIED, get_time_stamp() - (*diner)->start_time, (*diner)->philos[i].philo_id);
            pthread_mutex_unlock(&(*diner)->supervisor->mutex);
            pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
            break;
        }
        pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
        i++;
        if (i == (*diner)->data->nb_philos)
            i = 0;
        usleep(1000);
    }
    return(NULL);
}

static int stop_diner(t_philos *philos)
{
    int value;

    value = 0;
    pthread_mutex_lock(&philos->philo_alive->mutex);
    if (philos->philo_alive->alive == FALSE)
        value = 1;
    pthread_mutex_unlock(&philos->philo_alive->mutex);
    return (value);
}