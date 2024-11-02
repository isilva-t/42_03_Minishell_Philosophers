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



int	main(int ac, char **av)
{
	t_args	val;
	pthread_t	th_id;
	int 	i;

	if (ft_first_args_check_have_error(ac, av) == TRUE)
		return (1);
	if (ft_parse_data_and_check_error(av, &val) == TRUE)
		return (1);



	return (0);


	printf("before thread\n");
	i = 0;
	while (i++ < 4)
	{
		pthread_create(&th_id, NULL, my_thread, NULL);
	}
	pthread_join(th_id, NULL);
	
	printf("end\n");
	return (0);
}
