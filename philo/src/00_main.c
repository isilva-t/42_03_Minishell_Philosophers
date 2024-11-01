#include "philo.h"


void	*my_thread(void *arg)
{
	(void)arg;
	static int s;

	int	g = 0;
	
	usleep(500000);
	printf("Local %d, In Thread %d\n", ++g, ++s);
	usleep(500000);
	return (NULL);
}

void	ft_init_args(t_args *val)
{
	val->nb_philos = 0;
	val->time_to_die = 0;
	val->time_to_eat = 0;
	val->time_to_sleep = 0;
	val->nb_must_eat = 0;
	val->error_philo = 0;
}



int	ft_second_args_check_have_error(char **av)
{
	t_args	val;

	ft_init_args(&val);
	val.nb_philos = ft_atoui(av[1]);
	val.time_to_die = ft_atoui(av[2]);
	val.time_to_eat = ft_atoui(av[3]);
	val.time_to_sleep = ft_atoui(av[4]);
	if (av[5])
		val.nb_must_eat = ft_atoui(av[5]);
	if (MAX_PHILO < val.nb_philos)
		val.error_philo = (1 << 8) | val.error_philo;
	if (val.time_to_die < 200)
		val.error_philo = (1 << 16) & 0xF;
	printf("number error: %d\n", val.error_philo);

	return (FALSE);
}

int	main(int ac, char **av)
{
	pthread_t	th_id;
	int			i;
	int			j;
	char		k;

	k = 1;
	j = 0;
	j = (k << 2) | j;
	printf ("j = %d\n", j);

	if (ft_first_args_check_have_error(ac, av) == TRUE)
		return (1);
	if (ft_second_args_check_have_error(av) == TRUE)
		return (1);



	printf("before thread\n");

	i = 0;
	while (i++ < 4)
	{
		pthread_create(&th_id, NULL, my_thread, NULL);
	}

	pthread_join(th_id, NULL);
	printf("after\n");
}
