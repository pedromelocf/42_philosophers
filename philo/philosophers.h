#ifndef PHILO_H

# define PHILO_H

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

#ifndef IN_USE
# define IN_USE 1
#endif

#ifndef NOT_IN_USE
# define NOT_IN_USE 0
#endif

#ifndef EXPECTED_ARGS
# define EXPECTED_ARGS "expected: ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
#endif

#ifndef TAKEN_FORK
# define TAKEN_FORK "%ld %d has taken a fork\n"
#endif

#ifndef EATING
# define EATING "%ld %d is eating\n"
#endif

#ifndef SLEEPING
# define SLEEPING "%ld %d is sleeping\n"
#endif

#ifndef THINKING
# define THINKING "%ld %d is thinking\n"
#endif

#ifndef DIED
# define DIED "%ld %d died\n"
#endif

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_alive
{
    pthread_mutex_t alive_mutex;
    short int   alive;
}   t_alive;

typedef struct s_fork
{
    pthread_mutex_t fork_mutex;
	short int	state;
}   t_fork;

typedef struct s_last_meal
{
	pthread_mutex_t last_meal_mutex;
	long int		time_since_last_meal;
}	t_last_meal;

typedef struct s_data
{
	short int		nb_philos;
	int             time_to_die;
	int             time_to_eat;
	int             time_to_sleep;
	int             nb_meals_todo;
}    t_data;

typedef struct s_philos
{
    t_fork          *left_fork;
    t_fork          *right_fork;
	t_last_meal     *last_meal;
    pthread_t       philo_pthread;
    short int       philo_id;
    int             nb_meals_done;
    long int        start_time;
	short int		satisfied;
    t_alive         *philo_alive;
    struct s_data   *data;
}   t_philos;

typedef struct s_diner
{
    struct s_supervisor *supervisor;
    struct s_philos     **philos;
    struct s_data       *data;
    struct s_fork       *fork;
    long int            start_time;
}   t_diner;

typedef struct s_supervisor
{
    short int       alive;
    pthread_t       supervisor_pthread;
    t_diner         *dining_info;
}  t_supervisor;

void        init_diner(t_diner **diner, int argc, char **argv);
int         ft_atoi(const char *nptr);
void 	    handle_exit(char *str, int status);
void        dining(t_diner **diner);
void	    *philos_routine(void *arg);
void	    *supervisor_routine(void *arg);
void 	    clean_diner(t_diner **diner);
void 	    sleeping(t_philos *philo);
void       	taking_fork(t_philos *philo);
void 	    eating(t_philos *philo);
void 	    thinking(t_philos *philo);
long int    get_time_stamp(void);

#endif