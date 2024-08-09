/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_forks_aux.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:58:04 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/09 16:58:43 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_solo(t_philos *philos)
{
	pthread_mutex_lock(&philos->right_fork->mutex);
	philos->right_fork->state = IN_USE;
	safe_print(TAKEN_FORK, get_time_stamp() - philos->start_time,
		philos->philo_id, philos->print);
	ft_usleep(philos->data->time_to_die + 5);
}

void	taking_fork_even(t_philos *philos)
{
	ft_usleep(1);
	pthread_mutex_lock(&philos->right_fork->mutex);
	philos->right_fork->state = IN_USE;
	if (philo_died(philos) == FALSE)
	{
		safe_print(TAKEN_FORK, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
	}
	pthread_mutex_lock(&philos->left_fork->mutex);
	philos->left_fork->state = IN_USE;
	if (philo_died(philos) == FALSE)
	{
		safe_print(TAKEN_FORK, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
	}
}

void	taking_fork_odd(t_philos *philos)
{
	pthread_mutex_lock(&philos->left_fork->mutex);
	philos->left_fork->state = IN_USE;
	if (philo_died(philos) == FALSE)
	{
		safe_print(TAKEN_FORK, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
	}
	pthread_mutex_lock(&philos->right_fork->mutex);
	philos->right_fork->state = IN_USE;
	if (philo_died(philos) == FALSE)
	{
		safe_print(TAKEN_FORK, get_time_stamp() - philos->start_time,
			philos->philo_id, philos->print);
	}
}
