#include "philo.h"

void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;
	unsigned int	i;

	ph = (t_philo *)arg;
	i = 0;
	while (i < ph->d->nb_philos)
	{
		if ((i + 1) == ph->id)
		{
			printf("Hello, I'm %dst philosopher\n", ph->id);
			printf("curent time: %zu\n", ft_get_time() - ph->d->start_time);
		}
		i++;
	}
	return (NULL);
}

int	ft_philo_checkin_is_ok(t_philo **ph, t_args *d)
{
	int	i;

	i = 0;
	while (i < d->nb_philos)
	{
		pthread_create(&(ph[i]->td), NULL,
			&ft_philo_dinner_plan, (void *)ph[i]); //NEED SECUR
		i++;
	}
	return (TRUE);
}
