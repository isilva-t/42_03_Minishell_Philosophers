#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

unsigned int	ft_atoui(const char *nptr)
{
	unsigned int	i;
	unsigned int	num;

	i = 0;
	num = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		num = num * 10 + nptr[i++] - '0';
	return (num);
}

void	ft_print_user_manual()
{
	printf("Use between FOUR or FIVE arguments. ");
	printf("Fifth argument is optional.\n");
	printf("Arguments description:\n");
	printf("[0] prog_name\n");
	printf("[1] number_of_philos\n");
	printf("[2] time_to_die\n");
	printf("[3] time_to_eat\n");
	printf("[4] time_to_sleep\n");
	printf("[5] number_of_times_each_philosopher_must_eat\n\n");
	printf("Example:\n./philo 5 800 200 200 7\n\n");
}

