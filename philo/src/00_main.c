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

int	ft_have_only_digits_in_numbers(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) == FALSE)
				return (FALSE);
		}
	}
	return (TRUE);
}

int	ft_first_args_check_have_error(int ac, char **av)
{
	int	rt;

	rt = 0;
	if (ac < 5 || ac > 6)
		rt = printf("\nNumber of arguments incorrect!\n");
	else if (ft_have_only_digits_in_numbers(av) == FALSE)
		rt = printf("Only acceptable positive numbers on arguments!\n");
	if (rt > 0)
	{
		printf("Use between FOUR or FIVE arguments. ");
		printf("Fifth argument is optional.\n");
		printf("Arguments description:\n[0] prog_name\n");
		printf("[1] number_of_philos\n");
		printf("[2] time_to_die\n[3] time_to_eat\n[4] time_to_sleep\n");
		printf("[5] number_of_times_each_philosopher_must_eat\n\n");
		printf("Example:\n./philo 5 800 200 200 7\n\n");
		return (TRUE);
	}
	return (FALSE);
}

int	main(int ac, char **av)
{
	pthread_t	th_id;
	int			i;

	if (ft_first_args_check_have_error(ac, av) == TRUE)
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
