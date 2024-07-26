#ifndef PHILO_H

# define PHILO_H

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

#ifndef EXPECTED_ARGS
# define EXPECTED_ARGS "expected: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
#endif

#ifndef TAKEN_FORK
# define TAKEN_FORK "%d %d has taken a fork\n"
#endif

#ifndef EATING
# define EATING "%d %d is eating\n"
#endif

#ifndef SLEEPING
# define SLEEPING "%d %d is sleeping\n"
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
    short int		nb_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             nb_meals_todo;
}    t_data;

typedef struct s_fork
{
    pthread_mutex_t fork_mutex;
}   t_fork;

typedef struct s_philos
{
    t_fork          *left_fork;
    t_fork          *right_fork;
    pthread_t       philo_pthread;
    pthread_mutex_t philo_mutex;
    short int       philo_id;
    int             time_since_beggin_last_meal;
    int             nb_meals_done;
}    t_philos;

typedef struct s_diner
{
    struct s_supervisor *supervisor;
    struct s_philos     *philos;
    struct s_data       *data;
    struct s_fork       *fork;
	struct timeval		*time;
}   t_diner;

typedef struct s_supervisor
{
    short int       alive;
	pthread_mutex_t supervisor_mutex;
    pthread_t       supervisor_pthread;
    t_diner         *dining_info;
}  t_supervisor;

#endif