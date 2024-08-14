/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_data_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:09:13 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/14 14:13:14 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_mutex	*init_mutex(void);
static void		init_philo_data(t_philos *philos, t_diner *diner, int i);

t_mutex	*init_forks(t_diner *diner)
{
	t_mutex	*forks;
	int		i;

	i = 0;
	forks = calloc(1, sizeof(t_mutex) * diner->data->nb_philos);
	if (forks == NULL)
		return (NULL);
	while (i < diner->data->nb_philos)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&forks[i].mutex);
				i--;
			}
			free(forks);
			return (NULL);
		}
		forks[i].state = NOT_IN_USE;
		i++;
	}
	return (forks);
}

t_philos	*init_philos(t_diner *diner)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = calloc(1, sizeof(t_philos) * diner->data->nb_philos);
	if (philos == NULL)
		return (NULL);
	while (i < diner->data->nb_philos)
	{
		philos[i].last_meal = init_mutex();
		if (philos[i].last_meal == NULL)
			return (clean_philos(diner, i));
		philos[i].nb_meals_done = init_mutex();
		if (philos[i].nb_meals_done == NULL)
			return (clean_philos(diner, i));
		philos[i].satisfied = init_mutex();
		if (philos[i].satisfied == NULL)
			return (clean_philos(diner, i));
		init_philo_data(philos, diner, i);
		i++;
	}
	return (philos);
}

static void	init_philo_data(t_philos *philos, t_diner *diner, int i)
{
	philos[i].last_meal->state = get_time_stamp();
	philos[i].nb_meals_done->state = 0;
	philos[i].satisfied->state = FALSE;
	philos[i].data = diner->data;
	philos[i].print = diner->print;
	philos[i].philo_alive = diner->supervisor;
	philos[i].start_time = get_time_stamp();
	philos[i].philo_id = i + 1;
	if (i == 0)
	{
		philos[i].left_fork = &diner->fork[i];
		philos[i].right_fork = &diner->fork[philos->data->nb_philos - 1];
	}
	else
	{
		philos[i].left_fork = &diner->fork[i];
		philos[i].right_fork = &diner->fork[i - 1];
	}
}

static t_mutex	*init_mutex(void)
{
	t_mutex	*mutex;

	mutex = calloc(1, sizeof(t_mutex));
	if (mutex == NULL)
		return (NULL);
	if (pthread_mutex_init(&mutex->mutex, NULL) != 0)
	{
		free(mutex);
		return (NULL);
	}
	return (mutex);
}
