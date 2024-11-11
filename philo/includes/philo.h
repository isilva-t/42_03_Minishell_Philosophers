/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:49:51 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/07 14:08:27 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

# define S_FORK "has taken a fork"
# define S_EATING "is eating"
# define S_SLEEPING "is sleeping"
# define S_THINKING "is thinking"
# define S_DIED "died"
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

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

typedef struct	s_args
{
	pthread_mutex_t	*mtx_meal_time;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t is_dead_lock[2];
	pthread_mutex_t	mtx_all_eaten;
	size_t	start_time;
	size_t	nb_philos;
	size_t	forks;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	is_died;
	size_t	all_eaten;
	long	nb_must_eat;
	int		error_philo;
}	t_args;

typedef struct s_philo
{
	pthread_t		td;
	unsigned int	index;
	unsigned int	id;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	size_t			last_meal;
	unsigned int	n_meals;
	unsigned int	max_meals;
	unsigned int	all_eaten;
	size_t	start_delay;
	enum e_status		status;
	t_args			*d;
}	t_philo;


// init vars
void	ft_init_variables(t_args *val);

// 10_Argument check
int	ft_first_args_check_have_error(int ac, char **av);

// 20_parse data
int	ft_parse_data_and_check_error(char **av, t_args *val);

// 30_prepare restaurafile:///home/isilva-t/Pictures/Screenshot_20241108_122307.pngnt (memmory :D )
t_philo	**ft_create_philos_mem(t_args *d);
int	ft_let_the_game_begin(t_philo **ph, t_args *d);

// 40_let the game begin
void	ft_stop_the_game(t_philo **ph, t_args *d);

//utils
int				ft_isdigit(int c);
size_t	ft_atol_positive(const char *nptr);
void			ft_print_user_manual();
size_t	ft_get_time(void);
void	ft_log(t_philo *ph, char *what_are_doing);
void	ft_usleep(size_t time);

// to delete
void	local(char *str); // to delete
#endif
