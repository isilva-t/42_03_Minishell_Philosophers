/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_let_the_game_begin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:35:45 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/14 09:35:48 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;
	//while thread running
	//usleep....
	while (ph->n_meals != ph->d->nb_must_eat)
	{
		if (ft_mtx_have_died_philo(ph) == TRUE)
			break ;
		ft_mtx_take_forks(ph);
		ft_mtx_save_meal_time(ph);
		ph->n_meals++;
		ft_log(ph, S_EATING, ph->index);
		ft_usleep(ph->d->time_to_eat);
		ft_mtx_leave_forks(ph);
		if (ph->max_meals > 0 && ft_mtx_have_reached_max_meals(ph) == TRUE)
			break ;
		ft_log(ph, S_SLEEPING, ph->index);
		if (ft_mtx_have_died_philo(ph) == TRUE)
			break ;
		ft_usleep(ph->d->time_to_sleep);
		ft_log(ph, S_THINKING, ph->index);
		usleep(500);
	}
	return (NULL);
}

int	ft_let_the_game_begin(t_philo **ph, t_args *d)
{
	size_t	j;

	j = 0;
	if (d->nb_philos == 0)
		return (FALSE);
	// else if (d->nb_philos == 1)
	// 	pthread_create(&(ph[0]->td), NULL,
	// 		&ft_one_philo_case, (void *)ph[0]);
	while (j < d->nb_philos)
	{
		pthread_create(&(ph[j]->td), NULL,
			&ft_philo_dinner_plan, (void *)ph[j]);
		j++;
	}
	return (TRUE);
}
