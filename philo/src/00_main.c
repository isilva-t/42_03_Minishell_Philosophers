#include "philo.h"
#include <pthread.h>

int	ft_mutex_init(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;

	(void)ph;
	d->mtx_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * d->nb_philos);
	if (!d->mtx_fork)
		return (FALSE);
	while (i < d->nb_philos)
	{
		pthread_mutex_init(&d->mtx_fork[i], NULL); // need to secure
		pthread_mutex_init(&ph[i]->mtx_philo, NULL);
		pthread_mutex_init(&ph[i]->mtx_eat_done, NULL);
		i++;
	}
	

	pthread_mutex_init(&d->mtx_log, NULL); // need to secure
	pthread_mutex_init(&d->mtx_died, NULL); // need to secure
	pthread_mutex_init(&d->mtx_finish_dinner, NULL); // need to secure
	return (TRUE);
}

int	ft_mutex_destroy(t_philo **ph, t_args *d)
{
	size_t	i;

	(void)ph;
	i = d->nb_philos;
	while (i-- > 0)
	{
		pthread_mutex_destroy(&d->mtx_fork[i]);
		pthread_mutex_destroy(&ph[i]->mtx_philo);
		pthread_mutex_destroy(&ph[i]->mtx_eat_done);
	}
	free (d->mtx_fork);


	pthread_mutex_destroy(&d->mtx_log); //need secure
	pthread_mutex_destroy(&d->mtx_died);
	pthread_mutex_destroy(&d->mtx_finish_dinner); //need secure
	
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


int	ft_free_philo_mem(t_philo **ph, t_args *d)
{
	size_t i;

	i = 0;
	while (i < d->nb_philos)
	{
		free(ph[i]);
		i++;
	}
	free(ph);
	return (TRUE);
}

void	*ft_monitor(void *arg)
{
	t_args	*d;
	t_philo **ph;
	size_t		i;
	d = (t_args *)arg;
	ph = (t_philo **)d->ph;

	i = 0;
	//ft_log(ph[i], "test\n", 0);
	while (1)
		{
			
			pthread_mutex_lock(&ph[i]->mtx_eat_done);
			if (d->nb_must_eat > 0 && ph[i]->eating_done == TRUE)
			{
				ph[i]->eating_done = TRUE_VERIFYED;
				pthread_mutex_unlock(&ph[i]->mtx_eat_done);
				d->all_eaten++;
				if (d->nb_must_eat > 0 && d->all_eaten == d->nb_philos)
				{
					ft_stop_the_game(ph, d);
					pthread_mutex_lock(&d->mtx_finish_dinner);
					d->finish_dinner = TRUE;
					pthread_mutex_unlock(&d->mtx_finish_dinner);
					break;
				}
			}
			pthread_mutex_unlock(&ph[i]->mtx_eat_done);

			pthread_mutex_lock(&ph[i]->mtx_philo);
			if (ft_get_time() - ph[i]->last_meal > d->time_to_die)
			{
				pthread_mutex_unlock(&ph[i]->mtx_philo);

				//printf("olha\n");
				pthread_mutex_lock(&d->mtx_died);

				//printf("aqui\n");
				d->is_died = TRUE;
				pthread_mutex_unlock(&d->mtx_died);

				ft_stop_the_game(ph, d);
				printf("___%zu MORREU\n", i + 1);
				//ft_log(ph[i], S_DIED, 0); 
				//FALTA CORRIGIR ESTA MACACADA POR CAUSA DO "DIED" ESTAR A 1 AQUI

				pthread_mutex_lock(&d->mtx_finish_dinner);
				d->finish_dinner = TRUE;
				pthread_mutex_unlock(&d->mtx_finish_dinner);
				break;
			}
			pthread_mutex_unlock(&ph[i]->mtx_philo);

			i = (i + 1) % d->nb_philos;
		}
	return (NULL);
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
	pthread_create(&monitor, NULL, &ft_monitor, (void *)&d); //NEED SECURE

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
