/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:31:40 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/06 19:32:04 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	supervisor_check_satisfied(t_diner **diner, int *all_satisfied, int i)
{
	if ((*diner)->data->nb_meals_todo != -1)
	{
		pthread_mutex_lock(&(*diner)->philos[i].nb_meals_done->mutex);
		if ((*diner)->philos[i].nb_meals_done->state
			>= (*diner)->philos[i].data->nb_meals_todo)
			*all_satisfied = TRUE;
		else
			*all_satisfied = FALSE;
		pthread_mutex_unlock(&(*diner)->philos[i].nb_meals_done->mutex);
	}
}

int	supervisor_check_alive(t_diner **diner, int i)
{
	pthread_mutex_lock(&(*diner)->philos[i].last_meal->mutex);
	if (get_time_stamp() - (*diner)->philos[i].last_meal->state
		> (*diner)->data->time_to_die)
	{
		pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
		pthread_mutex_lock(&(*diner)->supervisor->mutex);
		(*diner)->supervisor->alive = FALSE;
		pthread_mutex_unlock(&(*diner)->supervisor->mutex);
		safe_print(DIED, get_time_stamp() - (*diner)->start_time,
			(*diner)->philos[i].philo_id, (*diner)->print);
		return (FALSE);
	}
	pthread_mutex_unlock(&(*diner)->philos[i].last_meal->mutex);
	return (TRUE);
}

void	update_loop(t_diner **diner, int all_satisfied, int *i)
{
	if (*i + 1 == (*diner)->data->nb_philos)
	{
		if (all_satisfied == FALSE)
			*i = 0;
		else
			*i += 1;
	}
	else
		*i += 1;
}
