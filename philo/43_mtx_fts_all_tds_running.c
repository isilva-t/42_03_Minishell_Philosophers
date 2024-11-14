#include "philo.h"

int	ft_mtx_are_all_threads_running(t_philo *ph)
{
	pthread_mutex_lock(&ph->d->mtx_all_tds_running);
	if (ph->d->all_tds_running == ph->n_philos)
	{
		pthread_mutex_unlock(&ph->d->mtx_all_tds_running);
		return (TRUE);
	}
	pthread_mutex_unlock(&ph->d->mtx_all_tds_running);
	return (FALSE);
}

void	ft_mtx_increase_created_threads(t_args *d)
{
	pthread_mutex_lock(&d->mtx_all_tds_running);
	d->all_tds_running++;
	pthread_mutex_unlock(&d->mtx_all_tds_running);
}
