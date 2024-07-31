/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:51 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/07/31 12:46:43 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	stop_diner(t_philos *philos);

void	*philos_routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	while (stop_diner(philos) != 1)
	{
		taking_fork(philos);
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
	return (NULL);
}

void	*supervisor_routine(void *arg)
{
	t_diner	**diner;
	int		i;

	diner = (t_diner **)arg;
	i = 0;
	while (i < (*diner)->data->nb_philos)
	{
		pthread_mutex_lock(&(*diner)->philos[i].last_meal->mutex);
		if (get_time_stamp()
			- (*diner)->philos[i].last_meal->state > (*diner)->data->time_to_die)
		{
			pthread_mutex_lock(&(*diner)->supervisor->mutex);
			(*diner)->supervisor->alive = FALSE;
			printf(DIED, get_time_stamp() - (*diner)->start_time,
					(*diner)->philos[i].philo_id);
			pthread_mutex_unlock(&(*diner)->supervisor->mutex);
			pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
			break ;
		}
		pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
		if ((*diner)->data->nb_meals_todo != -1)
		{
			pthread_mutex_lock(&(*diner)->philos[i].nb_meals_done->mutex);
			if ((*diner)->philos[i].nb_meals_done->state >= (*diner)->data->nb_meals_todo)
			{
				pthread_mutex_lock(&(*diner)->supervisor->mutex);
				(*diner)->supervisor->alive = FALSE;
				pthread_mutex_unlock(&(*diner)->supervisor->mutex);
				pthread_mutex_unlock(&(*diner)->philos[i].nb_meals_done->mutex);
				break ;
			}
			pthread_mutex_unlock(&(*diner)->philos[i].nb_meals_done->mutex);
		}
		i++;
		if (i == (*diner)->data->nb_philos)
			i = 0;
		usleep(10);
	}
	return (NULL);
}

static int	stop_diner(t_philos *philos)
{
	int value;

	value = 0;
	pthread_mutex_lock(&philos->philo_alive->mutex);
	if (philos->philo_alive->alive == FALSE)
		value = 1;
	pthread_mutex_unlock(&philos->philo_alive->mutex);
	return (value);
}