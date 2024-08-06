/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_diner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:27 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/06 18:16:05 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_data	*init_data(int argc, char **argv);
static t_philos	*init_philos(t_diner *diner);
static t_mutex	*init_forks(t_diner *diner);

void	init_diner(t_diner **diner, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		handle_exit(EXPECTED_ARGS, 1, 0, NULL);
	*diner = calloc(1, sizeof(t_diner));
	if (*diner == NULL)
		handle_exit("Allocation failed\n", 1, 1, diner);
	(*diner)->data = init_data(argc, argv);
	if ((*diner)->data == NULL)
		handle_exit("Data initialization failed\n", 1, 1, diner);
	input_validations(diner);
	(*diner)->supervisor = calloc(1, sizeof(t_supervisor));
	(*diner)->supervisor->alive = TRUE;
	pthread_mutex_init(&(*diner)->supervisor->mutex, NULL);
	(*diner)->print = calloc(1, sizeof(t_mutex));
	if ((*diner)->print == NULL)
		handle_exit("Print initialization failed\n", 1, 1, diner);
	pthread_mutex_init(&(*diner)->print->mutex, NULL);
	(*diner)->fork = init_forks(*diner);
	if ((*diner)->fork == NULL)
		handle_exit("Forks initialization failed\n", 1, 1, diner);
	(*diner)->philos = init_philos(*diner);
	if ((*diner)->philos == NULL)
		handle_exit("Philosophers initialization failed\n", 1, 1, diner);
	(*diner)->start_time = get_time_stamp();
}

static t_mutex	*init_forks(t_diner *diner)
{
	t_mutex	*forks;
	int		i;

	i = 0;
	forks = calloc(1, sizeof(t_mutex) * diner->data->nb_philos);
	if (forks == NULL)
		return (NULL);
	while (i < diner->data->nb_philos)
	{
		pthread_mutex_init(&forks[i].mutex, NULL);
		forks[i].state = NOT_IN_USE;
		i++;
	}
	return (forks);
}

static t_philos	*init_philos(t_diner *diner)
{
	t_philos	*philos;
	int			i;

	i = 0;
	philos = calloc(1, sizeof(t_philos) * diner->data->nb_philos);
	if (philos == NULL)
		return (NULL);
	while (i < diner->data->nb_philos)
	{
		philos[i].last_meal = calloc(1, sizeof(t_mutex));
		philos[i].last_meal->state = get_time_stamp();
		pthread_mutex_init(&philos[i].last_meal->mutex, NULL);
		philos[i].philo_alive = diner->supervisor;
		philos[i].philo_id = i + 1;
		philos[i].nb_meals_done = calloc(1, sizeof(t_mutex));
		philos[i].nb_meals_done->state = 0;
		pthread_mutex_init(&philos[i].nb_meals_done->mutex, NULL);
		philos[i].start_time = get_time_stamp();
		philos[i].satisfied = calloc(1, sizeof(t_mutex));
		philos[i].satisfied->state = FALSE;
		pthread_mutex_init(&philos[i].satisfied->mutex, NULL);
		philos[i].data = diner->data;
		philos[i].print = diner->print;
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
		i++;
	}
	return (philos);
}

static t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->nb_meals_todo = -1;
	if (argc == 6)
		data->nb_meals_todo = ft_atoi(argv[5]);
	return (data);
}

void	clean_diner(t_diner **diner)
{
	short int	nb_philos;
	short int	i;

	nb_philos = (*diner)->data->nb_philos;
	i = 0;
	if ((*diner)->data)
		free((*diner)->data);
	if ((*diner)->supervisor)
	{
		pthread_mutex_destroy(&(*diner)->supervisor->mutex);
		free((*diner)->supervisor);
	}
	if ((*diner)->print)
	{
		pthread_mutex_destroy(&(*diner)->print->mutex);
		free((*diner)->print);
	}
	while (i < nb_philos)
	{
		pthread_mutex_destroy(&(*diner)->fork[i].mutex);
		pthread_mutex_destroy(&(*diner)->philos[i].last_meal->mutex);
		pthread_mutex_destroy(&(*diner)->philos[i].satisfied->mutex);
		if ((*diner)->philos[i].last_meal)
			free((*diner)->philos[i].last_meal);
		if ((*diner)->philos[i].nb_meals_done)
		{
			free((*diner)->philos[i].nb_meals_done);
		}
		i++;
	}
	if ((*diner)->philos)
		free((*diner)->philos);
	if ((*diner)->fork)
		free((*diner)->fork);
	if (*diner)
		free(*diner);
}
