
#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define RED "\e[1;3;31m"
# define GREEN "\e[1;3;32m"
# define YELLOW "\e[1;3;93m"
# define RESET "\e[0m"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "DIED"
# define LEFT 0
# define RIGHT 1

# define INVALID -1
# define TRUE 1
# define FALSE 0


# define MAX_PHILO 250
# define MIN_TIME 60


typedef struct s_table
{
	time_t	start_time;
	unsigned int	n_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
}	t_table;

typedef struct s_philo
{
	pthread_t	thd;
	unsigned int	id;
	unsigned int	time_to_eat;
	unsigned int	fork[2];
	pthread_mutex_t	meal_lock;
	time_t			last_meal;
}	t_philo;


typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;


//utils
int				ft_isdigit(int c);
unsigned int	ft_atoui(const char *nptr);

#endif
