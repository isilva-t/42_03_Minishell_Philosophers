#include "philo.h"

int	ft_mutex_init(t_args *d)
{
	size_t	i;

	i = 0;

	d->mtx_meal_time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d->nb_philos);
	if (!d->mtx_meal_time)
		return (FALSE);

	d->mtx_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d->nb_philos);
	if (!d->mtx_fork)
		return (FALSE);

	while (i < d->nb_philos)
	{
		pthread_mutex_init(&d->mtx_meal_time[i], NULL); // need to secure
		pthread_mutex_init(&d->mtx_fork[i], NULL); // need to secure
		i++;
	}





	pthread_mutex_init(&d->mtx_all_eaten, NULL); //need secure
	return (TRUE);
}

int	ft_mutex_destroy(t_args *d)
{
	size_t	i;

	i = d->nb_philos;

	while (i-- > 0)
		pthread_mutex_destroy(&d->mtx_meal_time[i]); // need to secure
	free (d->mtx_meal_time);

	pthread_mutex_destroy(&d->mtx_all_eaten); //need secure
	return (TRUE);
}

int	ft_align_forks(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;
	while (i < d->nb_philos)
	{
		if (ph[i]->id % 2 == 0)
		{
			ph[i]->first_fork = &d->mtx_fork[i];

			if (i == d->nb_philos - 1)
				ph[i]->second_fork = &d->mtx_fork[0];
			else
				ph[i]->second_fork = &d->mtx_fork[i + 1];
		}
		else
		{
			if (i == d->nb_philos - 1)
				ph[i]->first_fork = &d->mtx_fork[0];
			else
				ph[i]->first_fork = &d->mtx_fork[i + 1];

			ph[i]->second_fork = &d->mtx_fork[i];
		}

		i++;
	}
	return (TRUE);
}


int	main(int ac, char **av)
{
	t_args		d;
	t_philo		**ph;
	size_t			i;

	if (ft_first_args_check_have_error(ac, av) == TRUE)
		return (1);
	if (ft_parse_data_and_check_error(av, &d) == TRUE)
		return (1);
	d.start_time = ft_get_time();
	usleep(50);
	ph = ft_create_philos_mem(&d);
	if (!ph)
		return (printf("Error: Can't create Philosophers memory.\n"), 1);
	
	ft_mutex_init(&d);


	ft_align_forks(ph, &d);


	i = 0;
	if (ft_let_the_game_begin(ph, &d) == FALSE)
		return (printf("Error creating threads!\n"), 1);
	
	while (i < d.nb_philos)
	{

		pthread_mutex_lock(&d.mtx_all_eaten);
		if (d.all_eaten == d.nb_philos)
		{
			pthread_mutex_unlock(&d.mtx_all_eaten);
			ft_stop_the_game(ph, &d);
			break;
		}
		pthread_mutex_unlock(&d.mtx_all_eaten);
		
		pthread_mutex_lock(&d.mtx_meal_time[i]);
		if (ft_get_time() - ph[i]->last_meal > d.time_to_die)
		{
			d.is_died = 1;
			pthread_mutex_unlock(&d.mtx_meal_time[i]);
			ft_stop_the_game(ph, &d);
			ft_log(ph[i], S_DIED);
			break;
		}
		pthread_mutex_unlock(&d.mtx_meal_time[i]);

		i = (i + 1) % d.nb_philos;
	}


	ft_mutex_destroy(&d);


	return (0);
}
