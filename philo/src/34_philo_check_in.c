#include "philo.h"
#include <pthread.h>


// void	ft_set_meal_time(size_t *last_meal)
// {
// 	*last_meal = ft_get_time();
// }
// 					

void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;

	//ft_usleep(ph->start_delay);

	pthread_mutex_lock(&ph->d->mtx_meal_time[ph->index]);
	while (ph->n_meals != ph->d->nb_must_eat && ph->d->is_died == 0)
	{
		pthread_mutex_lock(ph->first_fork);
		ft_log(ph, S_FORK);
		pthread_mutex_lock(ph->second_fork);
		ft_log(ph, S_FORK);

		ph->last_meal = ft_get_time();
		ph->n_meals++;
		pthread_mutex_unlock(&ph->d->mtx_meal_time[ph->index]);
		ft_log(ph, S_EATING);
		ft_usleep(ph->d->time_to_eat);
		if (ph->n_meals == ph->max_meals)
		{
			pthread_mutex_unlock(ph->first_fork);
			pthread_mutex_unlock(ph->second_fork);


			pthread_mutex_lock(&ph->d->mtx_all_eaten);
			ph->d->all_eaten++;
			pthread_mutex_unlock(&ph->d->mtx_all_eaten);
			break ;
		}

		pthread_mutex_unlock(ph->first_fork);
		pthread_mutex_unlock(ph->second_fork);

		ft_log(ph, S_SLEEPING);
		ft_usleep(ph->d->time_to_sleep);
		ft_log(ph, S_THINKING);
		usleep(500);
	
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
