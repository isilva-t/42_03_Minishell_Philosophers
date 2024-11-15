/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   49_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 07:55:33 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/15 09:03:49 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mtx_all_philos_eaten_all_meals(t_philo **ph, t_args *d, size_t i, size_t *all_ate)
{
	d->all_eaten = 0;
	while (++i < d->nb_philos)
	{
		pthread_mutex_lock(&ph[i]->mtx_eat_done);
		if (ph[i]->eating_done == TRUE)
		{
			pthread_mutex_unlock(&ph[i]->mtx_eat_done);
			d->all_eaten++;
			continue ;
		}
		pthread_mutex_unlock(&ph[i]->mtx_eat_done);
	}
	if (d->all_eaten == d->nb_philos)
	{
		*all_ate = TRUE;
		pthread_mutex_lock(&d->mtx_died);
		d->is_died = TRUE;
		pthread_mutex_unlock(&d->mtx_died);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_mtx_set_if_have_philo_died(t_philo **ph, t_args *d, size_t i, size_t *died)
{
	//usleep(1);

	pthread_mutex_lock(&ph[i]->mtx_philo);
	if (ft_get_time() - ph[i]->last_meal > d->time_to_die)
	{
		pthread_mutex_unlock(&ph[i]->mtx_philo);
		*died = TRUE;
		return (TRUE);
	}
	pthread_mutex_unlock(&ph[i]->mtx_philo);
	return (FALSE);
}

void	*ft_monitor(void *arg)
{
	t_args	*d;
	t_philo	**ph;
	size_t	j;
	size_t	all_ate;
	size_t	died;

	d = (t_args *)arg;
	ph = (t_philo **)d->ph;
	j = 0;
	all_ate = 0;
	died = FALSE;
	while (all_ate == FALSE)
	{
		j = -1;
		while (died == FALSE && ++j < d->nb_philos)
		{
			ft_mtx_set_if_have_philo_died(ph, d, j, &died);
			ft_log(ph[j], S_DIED, ph[j]->index);
			pthread_mutex_lock(&d->mtx_died);
			d->is_died = TRUE;
			pthread_mutex_unlock(&d->mtx_died);

		}
		if (died == TRUE)
			break;
		ft_mtx_all_philos_eaten_all_meals(ph, d, -1, &all_ate);
		//i = (i + 1) % d->nb_philos;
	}
	usleep(150000);
	ft_stop_the_game(ph, d);
	pthread_mutex_lock(&d->mtx_finish_dinner);
	d->finish_dinner = TRUE;
	pthread_mutex_unlock(&d->mtx_finish_dinner);
	return (NULL);
}
