#include "philo.h"


t_philo	**ft_create_philos_mem(t_args *d)
{
	t_philo	**ph;
	int i;

	ph = (t_philo **)malloc(sizeof(t_philo *) * d->nb_philos);
	if (!ph)
		return (NULL);
	i = 0;
	while (i < d->nb_philos)
	{
		ph[i] = malloc(sizeof(t_philo) * 1);
		if (!ph[i])
		{
			while (i-- > 0)
				free(ph[i]);
			free(ph);
			return (NULL);
		}
		ph[i]->d = d;
		ph[i]->id = i;
		i++;
	}
	return (ph);
}




void	*ft_philo_dinner(void *arg)
{
	t_philo	*ph;
	int	i;

	ph = (t_philo *)arg;
	
	i = -1;
	while (i < ph->d->nb_philos)
	{
		printf("Hello, I'm %d st philosopher\n", ph->id);
		i++;
	}


}

int	ft_philo_checkin_is_ok(t_philo **ph, t_args *d)
{
	int	i;

	i = 0;
	while (i < d->nb_philos)
	{
		pthread_create(&(ph[i]->td), NULL, &ft_philo_dinner, (void *)ph[i]);
		i++;
	}
	return (TRUE);
}


int	main(int ac, char **av)
{
	t_args		d;
	t_philo		**ph;


	if (ft_first_args_check_have_error(ac, av) == TRUE)
		return (1);
	if (ft_parse_data_and_check_error(av, &d) == TRUE)
		return (1);
	pthread_mutex_init(&d.mtx_fork_1, NULL);
	pthread_mutex_init(&d.mtx_fork_2, NULL);
	ph = ft_create_philos_mem(&d);
		if (!ph)
			return (printf("Error: Can't create Philosophers.\n"), 1);
	if (ft_philo_checkin_is_ok(ph, &d) == FALSE)
		return (printf("error on checkin!\n"), 1);


	pthread_mutex_destroy(&d.mtx_fork_1);
	pthread_mutex_destroy(&d.mtx_fork_1);


	


	return (0);
}
