#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

void	ft_usleep(size_t time)
{
	usleep(time * 1000);
}

void	ft_set_meal_time(size_t *last_meal)
{
	*last_meal = ft_get_time();
}

// enum e_status	ft_set_philo_status(t_philo *ph, enum e_status status)
// {
// 	if (ft_get_time() - ph->last_meal > ph->d->time_to_die && ph->n_meals != 0)
// 	{
// 		ft_log(ph, S_DIED);
// 		ph->status = DIED;
// 		return (DIED);
// 	}
// 	else if (status == EATING)
// 	{
// 		ft_set_meal_time(ph);
// 		ft_log(ph, S_EATING);
// 		ph->status = status;
// 		return (EATING);
// 	}
// 	else if (status == SLEEPING)
// 	{
// 		ft_log(ph, S_SLEEPING);
// 		ph->status = status;
// 		return (SLEEPING);
// 	}
// 	else
// 	{
// 		ft_log(ph, S_THINKING);
// 		ph->status = status;
// 		return (THINKING);
// 	}
// }
					

void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;

	pthread_mutex_lock(&ph->d->meal_time_lock[ph->id - 1]);
	while (ph->n_meals != ph->d->nb_must_eat && ph->d->is_died == 0)
	{
	
		ph->last_meal = ft_get_time();
		pthread_mutex_unlock(&ph->d->meal_time_lock[ph->id - 1]);
		ft_log(ph, S_EATING);
		ph->n_meals++;
		ft_usleep(ph->d->time_to_eat);
		ft_log(ph, S_SLEEPING);
		ft_usleep(ph->d->time_to_sleep);
		ft_log(ph, S_THINKING);
	
		pthread_mutex_lock(&ph->d->meal_time_lock[ph->id - 1]);
	}
	return (NULL);
}

int	ft_philo_checkin_is_ok(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;
	while (i < d->nb_philos)
	{
		pthread_create(&(ph[i]->td), NULL,
			&ft_philo_dinner_plan, (void *)ph[i]); //NEED SECURE
		i++;
	}
	return (TRUE);
}
