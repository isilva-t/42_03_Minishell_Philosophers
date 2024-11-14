#include "philo.h"





void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;

	//ft_usleep(ph->start_delay);

	while (ph->n_meals != ph->d->nb_must_eat)
	{
		pthread_mutex_lock(&ph->d->mtx_died);
		if (ph->d->is_died == TRUE)
		{
			pthread_mutex_unlock(&ph->d->mtx_died);
			break ;
		}
		pthread_mutex_unlock(&ph->d->mtx_died);

		pthread_mutex_lock(ph->first_fork);
		ft_log(ph, S_FORK, ph->index);
		pthread_mutex_lock(ph->second_fork);
		ft_log(ph, S_FORK, ph->index);

		pthread_mutex_lock(&ph->mtx_philo);
		ph->last_meal = ft_get_time();
		pthread_mutex_unlock(&ph->mtx_philo);

		ph->n_meals++;

		ft_log(ph, S_EATING, ph->index);
		ft_usleep(ph->d->time_to_eat);

		pthread_mutex_unlock(ph->second_fork);
		pthread_mutex_unlock(ph->first_fork);

		if (ph->max_meals > 0 && ph->n_meals == ph->max_meals)
		{
			pthread_mutex_lock(&ph->mtx_eat_done);
			ph->eating_done = TRUE;
			pthread_mutex_unlock(&ph->mtx_eat_done);
			//ft_log(ph, "acabou\n", ph->index);
			break ;
		}

		ft_log(ph, S_SLEEPING, ph->index);


		pthread_mutex_lock(&ph->d->mtx_died);
		if (ph->d->is_died == TRUE)
		{
			pthread_mutex_unlock(&ph->d->mtx_died);
			break ;
		}
		pthread_mutex_unlock(&ph->d->mtx_died);

		ft_usleep(ph->d->time_to_sleep);
		ft_log(ph, S_THINKING, ph->index);
		usleep(500);
	
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
