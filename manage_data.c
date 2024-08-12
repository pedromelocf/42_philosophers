/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_diner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:27 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/09 17:00:14 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_data	*init_data(int argc, char **argv);

void	init_diner(t_diner **diner, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		handle_exit(EXPECTED_ARGS, 1, 0, NULL);
	*diner = calloc(1, sizeof(t_diner));
	if (*diner == NULL)
		handle_exit("Allocation failed\n", 1, 0, diner);
	(*diner)->data = init_data(argc, argv);
	if ((*diner)->data == NULL)
		handle_exit("Data initialization failed\n", 1, 1, diner);
	input_validations(diner);
	(*diner)->supervisor = calloc(1, sizeof(t_supervisor));
	if ((*diner)->supervisor == NULL)
		handle_exit("Supervisor initialization failed\n", 1, 2, diner);
	if (pthread_mutex_init(&(*diner)->supervisor->mutex, NULL) != 0)
		handle_exit("Mutex init failed\n", 1, 3 , diner);
	(*diner)->supervisor->alive = TRUE;
	(*diner)->print = calloc(1, sizeof(t_mutex));
	if ((*diner)->print == NULL)
		handle_exit("Print initialization failed\n", 1, 3, diner);
	if (pthread_mutex_init(&(*diner)->print->mutex, NULL) != 0)
		handle_exit("Mutex init failed\n", 1, 4 , diner);
	(*diner)->fork = init_forks(*diner);
	if ((*diner)->fork == NULL)
		handle_exit("Forks initialization failed\n", 1, 4, diner);
	(*diner)->philos = init_philos(*diner);
	if ((*diner)->philos == NULL)
		handle_exit("Philosophers initialization failed\n", 1, 4, diner);
	(*diner)->start_time = get_time_stamp();
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
	pthread_mutex_destroy(&(*diner)->supervisor->mutex);
	free((*diner)->supervisor);
	pthread_mutex_destroy(&(*diner)->print->mutex);
	free((*diner)->print);
	clean_philos(*diner, (*diner)->data->nb_philos);
	free((*diner)->data);
	free(*diner);
}

void clean_philos(t_diner *diner, int x)
{
	int i;

	i = 0;
	while (i < x)
	{
		if (diner->philos[i].last_meal)
		{
			pthread_mutex_destroy(&diner->philos[i].last_meal->mutex);
			free(diner->philos[i].last_meal);
		}
		if (diner->philos[i].nb_meals_done)
		{
			pthread_mutex_destroy(&diner->philos[i].nb_meals_done->mutex);
			free(diner->philos[i].nb_meals_done);
		}
		if (diner->philos[i].satisfied)
		{
			pthread_mutex_destroy(&diner->philos[i].satisfied->mutex);
			free(diner->philos[i].satisfied);
		}
		i++;
	}
	free(diner->philos);
	clean_forks(diner);
}

void	clean_forks(t_diner *diner)
{
	int i;

	i  = 0;
	while (i < diner->data->nb_philos)
	{
		pthread_mutex_destroy(&diner->fork[i].mutex);
		i++;
	}
	free(diner->fork);
}