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
	{
		rt = printf("Number of arguments incorrect!\n");
	}
	else if (ft_have_only_digits_in_numbers(av) == FALSE)
	{
		rt = printf("Only acceptable numbers on arguments!\n");
	}
	if (rt > 0)
		return (TRUE);
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
