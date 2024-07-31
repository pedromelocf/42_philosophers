/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:43:38 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/07/31 12:59:44 by pmelo-ca         ###   ########.fr       */
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
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		c = c * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * c);
}

void	handle_exit(char *str, int status, int clean, t_diner **diner)
{
	printf("%s", str);
	if (clean == 1)
		clean_diner(diner);
	exit(status);
}

long int	get_time_stamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(int time, t_philos *philo)
{
	long int	start;
	int			divider;

	if (time > 10000)
		divider = 100;
	else if (time > 1000)
		divider = 10;
	else if (time > 500)
		divider = 4;
	else
		divider = 1;
	start = get_time_stamp();
	while (get_time_stamp() - start < time)
	{
		pthread_mutex_lock(&philo->philo_alive->mutex);
		if (philo->philo_alive->alive == FALSE)
		{
			pthread_mutex_unlock(&philo->philo_alive->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->philo_alive->mutex);
		usleep(time / divider * 1000);
	}
}

void	safe_print(char *message, t_mutex *print)
{
	pthread_mutex_lock(&print->mutex);
	printf("%s", message);
	pthread_mutex_unlock(&print->mutex);
}
