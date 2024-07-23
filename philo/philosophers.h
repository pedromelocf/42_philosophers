#ifndef PHILO_H

# define PHILO_H

#ifndef EXPECTED_ARGS
# define EXPECTED_ARGS "expected: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
#endif

#ifndef TAKEN_FORK
# define TAKEN_FORK "%d %d has taken a fork\n"
#endif

#ifndef TAKEN_FORK
# define TAKEN_FORK "%d %d has taken a fork\n"
#endif

#ifndef EATING
# define EATING "%d %d is eating\n"
#endif

#ifndef THINKING
# define THINKING "%d %d is thinking\n"
#endif

#ifndef DIED
# define DIED "%d %d died\n"
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_data
{
    short int    nb_philos;
    int          time_to_die;
    int          time_to_eat;
    int          time_to_sleep;
    int          nb_meals_todo;
}    t_data;

typedef struct s_philo
{
    struct s_data   *data;
    struct s_philo  *next;
    short int       philo_id;
    int             nb_meals_done;
}    t_philo;

#endif