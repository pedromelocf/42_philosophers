#include "philosophers.h"

void	*philos_routine(void *arg)
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