/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:45 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/09 17:04:25 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	update_philo_satisfaction(t_philos *philos);

void	taking_fork(t_philos *philos)
{
	if (philo_died(philos) == FALSE && philo_satisfied(philos) == FALSE)
	{
		if (philos->data->nb_philos == 1)
			philo_solo(philos);
		else if (philos->philo_id % 2 == 0)
			taking_fork_even(philos);
		else if (philos->philo_id % 2 == 1)
			taking_fork_odd(philos);
	}
}

void	eating(t_philos *philos)
{
	if (philo_died(philos) == FALSE && philo_satisfied(philos) == FALSE)
	{
		pthread_mutex_lock(&philos->last_meal->mutex);
		philos->last_meal->state = get_time_stamp();
		pthread_mutex_unlock(&philos->last_meal->mutex);
		safe_print(EATING, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
		ft_usleep(philos->data->time_to_eat);
		philos->left_fork->state = NOT_IN_USE;
		philos->right_fork->state = NOT_IN_USE;
		pthread_mutex_unlock(&philos->left_fork->mutex);
		pthread_mutex_unlock(&philos->right_fork->mutex);
		pthread_mutex_lock(&philos->nb_meals_done->mutex);
		philos->nb_meals_done->state++;
		update_philo_satisfaction(philos);
	}
	else
	{
		pthread_mutex_unlock(&philos->left_fork->mutex);
		if (philos->data->nb_philos != 1)
			pthread_mutex_unlock(&philos->right_fork->mutex);
	}
}

void	sleeping(t_philos *philos)
{
	if (philo_died(philos) == FALSE && philo_satisfied(philos) == FALSE)
	{
		safe_print(SLEEPING, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
		ft_usleep(philos->data->time_to_sleep);
	}
}

void	thinking(t_philos *philos)
{
	if (philo_died(philos) == FALSE && philo_satisfied(philos) == FALSE)
	{
		safe_print(THINKING, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
		usleep(1);
	}
}

static void	update_philo_satisfaction(t_philos *philos)
{
	if (philos->nb_meals_done->state >= philos->data->nb_meals_todo
		&& philos->data->nb_meals_todo != -1)
	{
		pthread_mutex_lock(&philos->satisfied->mutex);
		philos->satisfied->state = TRUE;
		pthread_mutex_unlock(&philos->satisfied->mutex);
	}
	pthread_mutex_unlock(&philos->nb_meals_done->mutex);
}
