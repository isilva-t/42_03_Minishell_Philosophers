#include "philo.h"

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
	d.start_time = ft_get_time();
	printf("start time: %zu \n", d.start_time);
	usleep(50);
	ph = ft_create_philos_mem(&d);
		if (!ph)
			return (printf("Error: Can't create Philosophers memory.\n"), 1);
	if (ft_philo_checkin_is_ok(ph, &d) == FALSE)
		return (printf("Error on checkin!\n"), 1);


	ft_let_the_game_begin(ph, &d);


	// printf("curent time: %zu\n", ft_get_time() - d.start_time);
	// sleep(1);
	// printf("curent time: %zu\n", ft_get_time() - d.start_time);

	pthread_mutex_destroy(&d.mtx_fork_1);
	pthread_mutex_destroy(&d.mtx_fork_1);


	return (0);
}
