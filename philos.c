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
	if (philos->data->nb_philos == 1)
	{
		pthread_mutex_lock(&philos->right_fork->mutex);
		philos->right_fork->state = IN_USE;
		printf(TAKEN_FORK, get_time_stamp() - philos->start_time, philos->philo_id);
		ft_usleep(philos->data->time_to_die + 1);
	}
	else if (philos->philo_id % 2 == 0)
	{
		ft_usleep(2);
		pthread_mutex_lock(&philos->right_fork->mutex);
		philos->right_fork->state = IN_USE;
		pthread_mutex_lock(&philos->left_fork->mutex);
		philos->left_fork->state = IN_USE;
	}
	else if (philos->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&philos->left_fork->mutex);
		philos->left_fork->state = IN_USE;
		pthread_mutex_lock(&philos->right_fork->mutex);
		philos->right_fork->state = IN_USE;
	}
	if(philos->data->nb_philos != 1)
		printf(TAKEN_FORK, get_time_stamp() - philos->start_time, philos->philo_id);
}

void	eating(t_philos *philos)
{
	pthread_mutex_lock(&philos->philo_alive->mutex);
	if (philos->philo_alive->alive == TRUE)
	{
		pthread_mutex_lock(&philos->last_meal->mutex);
		philos->last_meal->state = get_time_stamp();
		pthread_mutex_unlock(&philos->last_meal->mutex);
		printf(EATING, get_time_stamp() - philos->start_time, philos->philo_id);
		ft_usleep(philos->data->time_to_eat);
		pthread_mutex_lock(&philos->nb_meals_done->mutex);
		philos->nb_meals_done->state++;
		pthread_mutex_unlock(&philos->nb_meals_done->mutex);
		philos->left_fork->state = NOT_IN_USE;
		philos->right_fork->state = NOT_IN_USE;
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
	}
	else
	{
		pthread_mutex_unlock(&philos->left_fork->mutex);
		if (philos->data->nb_philos != 1)
			pthread_mutex_unlock(&philos->right_fork->mutex);
	}
	pthread_mutex_unlock(&philos->philo_alive->mutex);
}

void	sleeping(t_philos *philos)
{
	pthread_mutex_lock(&philos->philo_alive->mutex);
	if (philos->philo_alive->alive == TRUE)
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
	if (philos->philo_alive->alive == TRUE)
		printf(THINKING, get_time_stamp() - philos->start_time, philos->philo_id);
	pthread_mutex_unlock(&philos->philo_alive->mutex);
}
