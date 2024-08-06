/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelo-ca <pmelo-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:55:56 by pmelo-ca          #+#    #+#             */
/*   Updated: 2024/08/06 20:26:53 by pmelo-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define TRUE 1
# define FALSE 0
# define IN_USE 1
# define NOT_IN_USE 0
# define EXPECTED_ARGS "expected: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define WRONG_ARGS "invalid input: use numbers >= 0\n"
# define TAKEN_FORK " has taken a fork\n"
# define EATING " is eating\n"
# define SLEEPING " is sleeping\n"
# define THINKING " is thinking\n"
# define DIED " died\n"

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_mutex
{
	pthread_mutex_t		mutex;
	long int			state;
}						t_mutex;

typedef struct s_supervisor
{
	pthread_mutex_t		mutex;
	short				alive;
	pthread_t			thread_supervisor;
}						t_supervisor;

typedef struct s_data
{
	short int			nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_meals_todo;
}						t_data;

typedef struct s_philos
{
	pthread_t			philo_pthread;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_mutex				*last_meal;
	t_mutex				*nb_meals_done;
	t_mutex				*satisfied;
	struct s_supervisor	*philo_alive;
	struct s_data		*data;
	struct s_mutex		*print;
	short int			philo_id;
	long int			start_time;
}						t_philos;

typedef struct s_diner
{
	struct s_supervisor	*supervisor;
	struct s_philos		*philos;
	struct s_data		*data;
	struct s_mutex		*fork;
	struct s_mutex		*print;
	long int			start_time;
}						t_diner;

void					init_diner(t_diner **diner, int argc, char **argv);
int						ft_atoi(const char *nptr);
void					handle_exit(char *str, int status, int clean,
							t_diner **diner);
void					dining(t_diner **diner);
void					*philos_routine(void *arg);
void					*supervisor_routine(void *arg);
void					clean_diner(t_diner **diner);
void					sleeping(t_philos *philo);
void					taking_fork(t_philos *philo);
void					eating(t_philos *philo);
void					thinking(t_philos *philo);
long int				get_time_stamp(void);
void					ft_usleep(int time);
void					safe_print(char *message, long int time, short int id,
							t_mutex *print);
int						philo_died(t_philos *philos);
void					input_validations(t_diner **diner);
int						philo_satisfied(t_philos *philos);
void					update_loop(t_diner **diner, int all_satisfied, int *i);
int						supervisor_check_alive(t_diner **diner, int i);
void					supervisor_check_satisfied(t_diner **diner,
							int *all_satisfied, int i);

#endif