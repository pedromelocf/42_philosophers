#include "philosophers.h"

void dining(t_diner **diner)
{
    int i = 0;

    pthread_create(&(*diner)->supervisor->supervisor_pthread, NULL, &supervisor_routine, diner);
    while (i < (*diner)->data->nb_philos)
    {
        pthread_create(&(*diner)->philos[i]->philo_pthread, NULL, &philos_routine, (*diner)->philos[i]);
        i++;
    }
    pthread_join((*diner)->supervisor->supervisor_pthread, NULL);
    i = 0;
    while (i < (*diner)->data->nb_philos)
    {
        pthread_join((*diner)->philos[i]->philo_pthread, NULL);
        i++;
    }
}
