#include "philo.h"

void	ft_stop_the_game(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;
	while (i < d->nb_philos)
	{
		pthread_join(ph[i]->td, NULL);
		i++;
	}
}
