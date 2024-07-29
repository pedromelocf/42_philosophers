#include "philosophers.h"

void	*philos_routine(void *arg)
{
    t_philos *philos;

    philos = (t_philos *)arg;
    while (philos->philo_alive->alive == TRUE)
    {
        if (get_time_stamp() - philos->time_since_beggin_last_meal > philos->data->time_to_die)
        {
            pthread_mutex_lock(&philos->philo_alive->alive_mutex);
            philos->philo_alive->alive = FALSE;
            pthread_mutex_unlock(&philos->philo_alive->alive_mutex);
            break;
        }
        if (philos->philo_id % 2 == 0)
            sleeping(philos);
        taking_fork(philos);
        eating(philos);
        sleeping(philos);
        thinking(philos);
    }
    return(NULL);
}

void	*supervisor_routine(void *arg)
{
    t_diner **diner;
    int i;

    diner = (t_diner **)arg;
    while ((*diner)->supervisor->alive == TRUE)
    {
        i = 0;
        while (i < (*diner)->data->nb_philos && (*diner)->supervisor->alive)
        {
            pthread_mutex_lock(&(*diner)->philos[i]->philo_alive->alive_mutex);
            if ((*diner)->philos[i]->philo_alive->alive == FALSE)
            {
                printf("SUP OWN THIS SH*T!\n\n");
                (*diner)->supervisor->alive = FALSE;
                (*diner)->philos[i]->philo_alive = FALSE;
                pthread_mutex_unlock(&(*diner)->philos[i]->philo_alive->alive_mutex);
                break;
            }
            pthread_mutex_unlock(&(*diner)->philos[i]->philo_alive->alive_mutex);
            usleep(1);
            i++;
        }
    }
    return(NULL);
}