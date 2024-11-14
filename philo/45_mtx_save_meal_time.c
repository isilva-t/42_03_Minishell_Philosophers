#include "philo.h"

void	ft_mtx_save_meal_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->mtx_philo);
	ph->last_meal = ft_get_time();
	pthread_mutex_unlock(&ph->mtx_philo);
	ph->n_meals++;
}
