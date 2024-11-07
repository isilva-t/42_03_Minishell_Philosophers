/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:49:51 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/07 11:51:01 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <bits/pthreadtypes.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

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

# define THO 1000


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


typedef struct	s_args
{
	pthread_mutex_t	mtx_fork_1;
	pthread_mutex_t	mtx_fork_2;
	long	nb_philos;
	long	forks;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nb_must_eat;
	int		error_philo;
}	t_args;

typedef struct s_philo
{
	pthread_t		td;
	unsigned int	id;
	unsigned int	fork[2];
	pthread_mutex_t	meal_lock;
	time_t			last_meal;
	t_args			*d;
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

// init vars
void	ft_init_variables(t_args *val);

// 10_Argument check
int	ft_first_args_check_have_error(int ac, char **av);

// 20_parse data
int	ft_parse_data_and_check_error(char **av, t_args *val);


//utils
int				ft_isdigit(int c);
long	ft_atol_positive(const char *nptr);
void			ft_print_user_manual();

#endif
