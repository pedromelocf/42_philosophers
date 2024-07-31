/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:45 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/07/31 12:44:02 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	taking_fork(t_philos *philos)
{
	printf(TAKEN_FORK, get_time_stamp() - philos->start_time, philos->philo_id);
}

void	eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->last_meal->mutex);
	philos->last_meal->state = get_time_stamp();
	pthread_mutex_unlock(&philos->last_meal->mutex);
	printf(EATING, get_time_stamp() - philos->start_time, philos->philo_id);
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_lock(&philos->nb_meals_done->mutex);
	philos->nb_meals_done->state++;
	pthread_mutex_unlock(&philos->nb_meals_done->mutex);
}

void	sleeping(t_philos *philos)
{
	pthread_mutex_lock(&philos->philo_alive->mutex);
	if (philos->philo_alive->alive != FALSE)
	{
		printf(SLEEPING, get_time_stamp() - philos->start_time, philos->philo_id);
		pthread_mutex_unlock(&philos->philo_alive->mutex);
		ft_usleep(philos->data->time_to_sleep);
	}
	else
		pthread_mutex_unlock(&philos->philo_alive->mutex);
}

void	thinking(t_philos *philos)
{
	pthread_mutex_lock(&philos->philo_alive->mutex);
	if (philos->philo_alive->alive != FALSE)
		printf(THINKING, get_time_stamp() - philos->start_time, philos->philo_id);
	pthread_mutex_unlock(&philos->philo_alive->mutex);
	usleep(10);
}
