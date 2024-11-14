#include "philo.h"
#include <pthread.h>


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
	pthread_t	monitor;

	if (ft_first_args_check_have_error(ac, av) == TRUE)
		return (1);
	if (ft_parse_data_and_check_error(av, &d) == TRUE)
		return (1);
	d.start_time = ft_get_time();
	usleep(50);
	ph = ft_create_philos_mem(&d);
	if (!ph)
		return (printf("Error: Can't create Philosophers memory.\n"), 1);
	d.ph = (void **)ph;

	ft_mutex_init(ph, &d);
	ft_align_forks(ph, &d);

	if (ft_let_the_game_begin(ph, &d) == FALSE)
		return (printf("Error creating threads!\n"), 1);

	usleep (500);
	pthread_create(&monitor, NULL, &ft_monitor, (void *)&d);

	while (1)
	{
		pthread_mutex_lock(&d.mtx_finish_dinner);
		if (d.finish_dinner == TRUE)
		{
			pthread_mutex_unlock(&d.mtx_finish_dinner);
			pthread_join(monitor, NULL);
			break ;
		}
		pthread_mutex_unlock(&d.mtx_finish_dinner);
		usleep (5000);

	}

	usleep(5000);
	ft_mutex_destroy(ph, &d);
	ft_free_philo_mem(ph, &d);

	return (0);
}
