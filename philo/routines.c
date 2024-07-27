#include "philosophers.h"

void	*philos_routine(void *arg)
{
    t_philos *philos;

    philos = (t_philos *)arg;
    while (philos->philo_alive == TRUE)
    {
        philos->time_since_beggin_last_meal = get_time_stamp();
        if(philos->philo_id % 2 == 0)
            sleeping(philos);
        taking_fork(philos);
        eating(philos);
        sleeping(philos);
        thinking(philos);
        usleep(1);
    }
    return (NULL);
}

void	*supervisor_routine(void *arg)
{
    t_diner **diner;
    int i;

    diner = (t_diner **)arg;
    while ((*diner)->supervisor->alive)
    {
        i = 0;
        while (i < (*diner)->data->nb_philos && (*diner)->supervisor->alive)
        {
            pthread_mutex_lock(&(*diner)->philos[i]->philo_mutex);
            if (get_time_stamp() - (*diner)->philos[i]->time_since_beggin_last_meal > (*diner)->data->time_to_die)
            {
                printf("SUP OWN THIS SH*T!\n\n");
                (*diner)->supervisor->alive = FALSE;
                (*diner)->philos[i]->philo_alive = FALSE;
                pthread_mutex_unlock(&(*diner)->philos[i]->philo_mutex);
                break;
            }
            pthread_mutex_unlock(&(*diner)->philos[i]->philo_mutex);
            i++;
            usleep(1);
        }
    }
    return(NULL);
}