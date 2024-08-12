#include "philosophers.h"

void	handle_exit(char *str, int status, int clean, t_diner **diner)
{
    printf("%s", str);
    if (clean == 1)
        free(*diner);
    if (clean == 2)
    {
        free((*diner)->data);
        free(*diner);
    }
    if (clean == 3)
    {
        free((*diner)->supervisor);
        free((*diner)->data);
        free(*diner);
    }
    if (clean == 4)
    {
        pthread_mutex_destroy(&(*diner)->supervisor->mutex);
        free((*diner)->print);
        free((*diner)->supervisor);
        free((*diner)->data);
        free(*diner);
    }
    exit(status);
}

void	clean_diner(t_diner **diner)
{
    pthread_mutex_destroy(&(*diner)->supervisor->mutex);
    free((*diner)->supervisor);
    pthread_mutex_destroy(&(*diner)->print->mutex);
    free((*diner)->print);
    clean_philos(*diner, (*diner)->data->nb_philos);
    free((*diner)->data);
    free(*diner);
}

void	*clean_philos(t_diner *diner, int x)
{
    int i;

    i = 0;
    while (i++ < x)
    {
        if (diner->philos[i].last_meal)
        {
            pthread_mutex_destroy(&diner->philos[i].last_meal->mutex);
            free(diner->philos[i].last_meal);
        }
        if (diner->philos[i].nb_meals_done)
        {
            pthread_mutex_destroy(&diner->philos[i].nb_meals_done->mutex);
            free(diner->philos[i].nb_meals_done);
        }
        if (diner->philos[i].satisfied)
        {
            pthread_mutex_destroy(&diner->philos[i].satisfied->mutex);
            free(diner->philos[i].satisfied);
        }
    }
    free(diner->philos);
    return (clean_forks(diner));
}

void	*clean_forks(t_diner *diner)
{
    int i;

    i  = 0;
    while (i++ < diner->data->nb_philos)
        pthread_mutex_destroy(&diner->fork[i].mutex);
    free(diner->fork);
    return (NULL);
}