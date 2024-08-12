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

static void	init_data(int argc, char **argv, t_diner **diner);
static void	init_supervisor_mutex(t_diner **diner);
static void init_print_mutex(t_diner **diner);
static void	input_validations(t_diner **diner);

void	init_diner(t_diner **diner, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		handle_exit(EXPECTED_ARGS, 1, 0, NULL);
	*diner = calloc(1, sizeof(t_diner));
	if (*diner == NULL)
		handle_exit("Allocation failed\n", 1, 0, diner);
	init_data(argc, argv, diner);
	input_validations(diner);
	init_supervisor_mutex(diner);
	init_print_mutex(diner);
	(*diner)->fork = init_forks(*diner);
	if ((*diner)->fork == NULL)
		handle_exit("Forks initialization failed\n", 1, 4, diner);
	(*diner)->philos = init_philos(*diner);
	if ((*diner)->philos == NULL)
		handle_exit("Philosophers initialization failed\n", 1, 4, diner);
}

static void	init_data(int argc, char **argv, t_diner **diner)
{
	(*diner)->data = calloc(1, sizeof(t_data));
	if ((*diner)->data == NULL)
		handle_exit("Data initialization failed\n", 1, 1, diner);
	(*diner)->data->nb_philos = ft_atoi(argv[1]);
	(*diner)->data->time_to_die = ft_atoi(argv[2]);
	(*diner)->data->time_to_eat = ft_atoi(argv[3]);
	(*diner)->data->time_to_sleep = ft_atoi(argv[4]);
	(*diner)->data->nb_meals_todo = -1;
	if (argc == 6)
		(*diner)->data->nb_meals_todo = ft_atoi(argv[5]);
}

static void	init_supervisor_mutex(t_diner **diner)
{
	(*diner)->supervisor = calloc(1, sizeof(t_supervisor));
	if ((*diner)->supervisor == NULL)
		handle_exit("Supervisor initialization failed\n", 1, 2, diner);
	if (pthread_mutex_init(&(*diner)->supervisor->mutex, NULL) != 0)
		handle_exit("Mutex init failed\n", 1, 3 , diner);
	(*diner)->supervisor->alive = TRUE;
}

static void init_print_mutex(t_diner **diner)
{
	(*diner)->print = calloc(1, sizeof(t_mutex));
	if ((*diner)->print == NULL)
		handle_exit("Print initialization failed\n", 1, 3, diner);
	if (pthread_mutex_init(&(*diner)->print->mutex, NULL) != 0)
		handle_exit("Mutex init failed\n", 1, 4 , diner);
}

static void	input_validations(t_diner **diner)
{
	if ((*diner)->data->nb_philos == -2 || (*diner)->data->time_to_die == -2
		|| (*diner)->data->time_to_eat == -2 || (*diner)->data->time_to_sleep
		== -2 || (*diner)->data->nb_meals_todo == -2)
		handle_exit(WRONG_ARGS, 1, 2, diner);
}
