#include "philosophers.h"

void	*philos_routine(void *arg)
{
    t_philos *philos;

    philos = (t_philos *)arg;
    while (TRUE)
    {
		if(philos->nb_meals_done >= philos->data->nb_meals_todo && philos->data->nb_meals_todo != -1)
		{
			philos->satisfied = TRUE;
			break;
		}
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
	i = 0;
	while (i < (*diner)->data->nb_philos)
	{
        pthread_mutex_lock(&(*diner)->philos[i]->last_meal->last_meal_mutex);
        if (get_time_stamp() - (*diner)->philos[i]->last_meal->time_since_last_meal > (*diner)->philos[i]->data->time_to_die)
        {
        	printf(DIED, get_time_stamp() - (*diner)->philos[i]->last_meal->time_since_last_meal, (*diner)->philos[i]->philo_id);
			break;
		}
		pthread_mutex_unlock(&(*diner)->philos[i]->last_meal->last_meal_mutex);
		if ((*diner)->philos[i]->satisfied == TRUE)
			break;
		i++;
		usleep(100);
		if (i == (*diner)->data->nb_philos - 1)
			i = 0;
	}
    return(NULL);
}
