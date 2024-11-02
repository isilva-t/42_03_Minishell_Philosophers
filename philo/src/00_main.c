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

void	ft_init_variables(t_args *val)
{
	val->nb_philos = 0;
	val->time_to_die = 0;
	val->time_to_eat = 0;
	val->time_to_sleep = 0;
	val->nb_must_eat = 0;
	val->error_philo = 0;
}

void	ft_convert_user_input_to_long_vars(char **av, t_args *val)
{
	val->nb_philos = ft_atol_positive(av[1]);
	val->time_to_die = ft_atol_positive(av[2]);
	val->time_to_eat = ft_atol_positive(av[3]);
	val->time_to_sleep = ft_atol_positive(av[4]);
	if (av[5])
		val->nb_must_eat = ft_atol_positive(av[5]);
	else
		val->nb_must_eat = -1;
}

void	ft_check_if_have_bigger_than_int_max(t_args *val)
{
	if (val->nb_philos > INT_MAX)
		val->error_philo = (1 << 5) | val->error_philo;
	if (val->time_to_die > INT_MAX)
		val->error_philo = (1 << 4) | val->error_philo;
	if (val->time_to_eat > INT_MAX)
		val->error_philo = (1 << 3) | val->error_philo;
	if (val->time_to_sleep > INT_MAX)
		val->error_philo = (1 << 2) | val->error_philo;
	if (val->nb_must_eat > INT_MAX)
		val->error_philo = 1 | val->error_philo;
}

void	ft_print_what_happen(int error)
{
	printf("\nError on some input(s):\n\n");
	if (((error >> 5) & 1) == TRUE)
		printf("	=> number_of_philosophers\n");
	if (((error >> 4) & 1) == TRUE)
		printf("	=> time_to_die\n");
	if (((error >> 3) & 1) == TRUE)
		printf("	=> time_to_eat\n");
	if (((error >> 2) & 1) == TRUE)
		printf("	=> time_to_sleep\n");
	if ((error & 1) == TRUE)
		printf("	=> number_of_times_each_philosopher_must_eat\n");
	printf("\nYou tried higher than INT_MAX value(s) on above list.\n");
		ft_print_user_manual();
}

int	ft_parse_data_have_error(char **av, t_args *val)
{
	ft_init_variables(val);
	ft_convert_user_input_to_long_vars(av, val);
	ft_check_if_have_bigger_than_int_max(val);
	if (val->error_philo >= TRUE)
		return (ft_print_what_happen(val->error_philo), TRUE);


	return (FALSE);
}

int	main(int ac, char **av)
{
	t_args	val;
	pthread_t	th_id;
	int 	i;

	if (ft_first_args_check_have_error(ac, av) == TRUE)
		return (1);
	if (ft_parse_data_have_error(av, &val) == TRUE)
		return (1);

	return (0);


	printf("before thread\n");

	i = 0;
	while (i++ < 4)
	{
		pthread_create(&th_id, NULL, my_thread, NULL);
	}

	pthread_join(th_id, NULL);
	printf("after\n");
}
