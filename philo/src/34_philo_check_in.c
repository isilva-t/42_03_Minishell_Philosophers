#include "philo.h"


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

	pthread_mutex_lock(&ph->d->mtx_meal_time[ph->index]);
	while (ph->n_meals != ph->d->nb_must_eat && ph->d->is_died == 0)
	{
	
		ph->last_meal = ft_get_time();
		ph->n_meals++;
		pthread_mutex_unlock(&ph->d->mtx_meal_time[ph->index]);
		ft_log(ph, S_EATING);
		if (ph->n_meals == ph->max_meals)
		{
			pthread_mutex_lock(&ph->d->mtx_all_eaten);
			ph->d->all_eaten++;
			pthread_mutex_unlock(&ph->d->mtx_all_eaten);
			break ;
		}

		ft_usleep(ph->d->time_to_eat);
		ft_log(ph, S_SLEEPING);
		ft_usleep(ph->d->time_to_sleep);
		ft_log(ph, S_THINKING);
	
		pthread_mutex_lock(&ph->d->mtx_meal_time[ph->index]);
	}
	return (NULL);
}

int	ft_let_the_game_begin(t_philo **ph, t_args *d)
{
	size_t	j;



	j = 0;
	while (j < d->nb_philos)
	{
		pthread_create(&(ph[j]->td), NULL,
			&ft_philo_dinner_plan, (void *)ph[j]); //NEED SECURE
		j++;
	}
	return (TRUE);
}
