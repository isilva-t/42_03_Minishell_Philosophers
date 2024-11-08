#include "philo.h"

void	ft_usleep(size_t time)
{
	usleep(time * 1000);
}

void	ft_set_meal_time(t_philo *ph)
{
	ph->last_meal = ft_get_time() - ph->d->start_time;
}

void	ft_log(t_philo *ph, char *what_are_doing)
{
	printf("%zu %d %s\n", ft_get_time() - ph->d->start_time, ph->id, what_are_doing);
}

enum e_status	ft_set_philo_status(t_philo *ph, enum e_status status)
{
	if (ft_get_time() - ph->last_meal > ph->d->time_to_die && ph->n_meals != 0)
	{
		ft_log(ph, S_DIED);
		ph->status = DIED;
		return (DIED);
	}
	else if (status == EATING)
	{
		ft_set_meal_time(ph);
		ft_log(ph, S_EATING);
		ph->status = status;
		return (EATING);
	}
	else if (status == SLEEPING)
	{
		ft_log(ph, S_SLEEPING);
		ph->status = status;
		return (SLEEPING);
	}
	else
	{
		ft_log(ph, S_THINKING);
		ph->status = status;
		return (THINKING);
	}
}
					

void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;
	
	while (ph->n_meals == 0 || ph->status > DIED)
	{
		ft_set_meal_time(ph);

		if (ft_set_philo_status(ph, EATING) == DIED && ph->n_meals > 0)
			break ;
		ph->n_meals++;
		ft_usleep(ph->d->time_to_eat);

		if (ft_set_philo_status(ph, SLEEPING) == DIED)
			break ;
		ft_usleep(ph->d->time_to_sleep);

		if (ft_set_philo_status(ph, THINKING) == DIED)
			break ;
	
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
