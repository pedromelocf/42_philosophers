#include "philosophers.h"

void dining(t_diner **diner)
{
    int i = 0;

    (*diner)->start_time = get_time_stamp();
    pthread_create(&(*diner)->supervisor->thread_supervisor, NULL, &supervisor_routine, diner);
    while (i < (*diner)->data->nb_philos)
    {
        pthread_create(&(*diner)->philos[i].philo_pthread, NULL, &philos_routine, &(*diner)->philos[i]);
        i++;
    }
    pthread_join((*diner)->supervisor->thread_supervisor, NULL);
    i = 0;
    while (i < (*diner)->data->nb_philos)
    {
        pthread_join((*diner)->philos[i].philo_pthread, NULL);
        i++;
    }
}
