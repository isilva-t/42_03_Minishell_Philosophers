#include "philo.h"

void	ft_init_variables(t_args *val)
{
	val->nb_philos = 0;
	val->forks = 0;
	val->time_to_die = 0;
	val->time_to_eat = 0;
	val->time_to_sleep = 0;
	val->nb_must_eat = 0;
	val->is_died = 0;
	val->error_philo = 0;
	val->all_eaten = 0;
}
