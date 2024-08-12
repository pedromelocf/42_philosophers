/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:38 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/09 17:03:13 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	size_t	c;
	size_t	sign;

	c = 0;
	i = 0;
	sign = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		c = c * 10 + nptr[i] - '0';
		i++;
	}
	if (nptr[i] != '\0')
		return (-2);
	return (sign * c);
}

void	handle_exit(char *str, int status, int clean, t_diner **diner)
{
	printf("%s", str);
	if (clean == 1)
		free(*diner);
	if (clean == 2)
	{
		free((*diner)->data);
		free(*diner);
	}
	if (clean == 3)
	{
		free((*diner)->supervisor);
		free((*diner)->data);
		free(*diner);
	}
	if (clean == 4)
	{
		pthread_mutex_destroy(&(*diner)->supervisor->mutex);
		free((*diner)->print);
		free((*diner)->supervisor);
		free((*diner)->data);
		free(*diner);
	}
	exit(status);
}

void	input_validations(t_diner **diner)
{
	if ((*diner)->data->nb_philos == -2 || (*diner)->data->time_to_die == -2
		|| (*diner)->data->time_to_eat == -2 || (*diner)->data->time_to_sleep
		== -2 || (*diner)->data->nb_meals_todo == -2)
		handle_exit(WRONG_ARGS, 1, 2, diner);
}

long int	get_time_stamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	usleep(time * 1000);
}
