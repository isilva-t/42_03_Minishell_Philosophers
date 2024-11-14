#include "philo.h"

int	ft_mtx_have_reached_max_meals(t_philo *ph)
{
	if (ph->n_meals == ph->max_meals)
	{
		pthread_mutex_lock(&ph->mtx_eat_done);
		ph->eating_done = TRUE;
		pthread_mutex_unlock(&ph->mtx_eat_done);
		return (TRUE);
	}
	return (FALSE);
}
