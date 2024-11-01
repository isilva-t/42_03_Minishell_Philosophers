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
