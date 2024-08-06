/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:51 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/06 18:16:38 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philos_routine(void *arg)
{
	t_philos	*philos;

	philos = (t_philos *)arg;
	pthread_mutex_lock(&philos->last_meal->mutex);
	philos->last_meal->state = get_time_stamp();
	pthread_mutex_unlock(&philos->last_meal->mutex);
	while (philo_died(philos) == FALSE && philo_satisfied(philos) == FALSE)
	{
		taking_fork(philos);
		eating(philos);
		sleeping(philos);
		thinking(philos);
		usleep(10);
	}
	return (NULL);
}

void	*supervisor_routine(void *arg)
{
	t_diner	**diner;
	int		i;
	int		all_satisfied;

	diner = (t_diner **)arg;
	i = 0;
	while (i < (*diner)->data->nb_philos)
	{
		all_satisfied = FALSE;
		pthread_mutex_lock(&(*diner)->philos[i].last_meal->mutex);
		if (get_time_stamp()
			- (*diner)->philos[i].last_meal->state > (*diner)->data->time_to_die)
		{
			pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
			pthread_mutex_lock(&(*diner)->supervisor->mutex);
			(*diner)->supervisor->alive = FALSE;
			pthread_mutex_unlock(&(*diner)->supervisor->mutex);
			safe_print(DIED, get_time_stamp() - (*diner)->start_time,
				(*diner)->philos[i].philo_id, (*diner)->print);
			break ;
		}
		pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
		if ((*diner)->data->nb_meals_todo != -1)
		{
			pthread_mutex_lock(&(*diner)->philos[i].nb_meals_done->mutex);
			if ((*diner)->philos[i].nb_meals_done->state >= (*diner)->philos[i].data->nb_meals_todo)
				all_satisfied = TRUE;
			else
				all_satisfied = FALSE;
			pthread_mutex_unlock(&(*diner)->philos[i].nb_meals_done->mutex);
		}
		i++;
		if (i == (*diner)->data->nb_philos)
		{
			if (all_satisfied == FALSE)
				i = 0;
		}
		usleep(10);
	}
	return (NULL);
}

int	philo_died(t_philos *philos)
{
	int	value;

	value = FALSE;
	pthread_mutex_lock(&philos->philo_alive->mutex);
	if (philos->philo_alive->alive == FALSE)
		value = TRUE;
	pthread_mutex_unlock(&philos->philo_alive->mutex);
	return (value);
}

int	philo_satisfied(t_philos *philos)
{
	int	value;

	value = FALSE;
	pthread_mutex_lock(&philos->satisfied->mutex);
	if (philos->satisfied->state == TRUE)
		value = TRUE;
	pthread_mutex_unlock(&philos->satisfied->mutex);
	return (value);
}
