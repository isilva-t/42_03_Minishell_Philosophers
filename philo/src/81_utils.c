#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_atol_positive(const char *nptr)
{
	int	i;
	size_t	num;

	i = 0;
	num = 0;
	while (nptr[i] && nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		num = num * 10 + nptr[i++] - '0';
	return (num);
}

void	ft_print_user_manual()
{
	printf("\nTo start the dinner, use between FOUR or FIVE arguments.\n");
	printf("Fifth argument is optional.\n");
	printf("Do not use negative numbers, or above INT_MAX.\n");
	printf("Arguments description:\n");
	printf("[0] prog_name\n");
	printf("[1] number_of_philos\n");
	printf("[2] time_to_die\n");
	printf("[3] time_to_eat\n");
	printf("[4] time_to_sleep\n");
	printf("[5] number_of_times_each_philosopher_must_eat\n\n");
	printf("Examples (with or without fifth argument:\n");
	printf("./philo 5 800 200 200 7\n");
	printf("./philo 2 800 200 200\n\n");
}

size_t	ft_get_time(void)
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_log(t_philo *ph, char *what_are_doing)
{
	printf("%zu\t%d %s\n", ft_get_time() - ph->d->start_time, ph->id, what_are_doing);
}

void	local(char *str)
{
	printf("%s\n", str); //to_delete
}

