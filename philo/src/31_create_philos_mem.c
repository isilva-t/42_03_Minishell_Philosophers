/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   31_create_philos_mem.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:14:21 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/07 12:15:48 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_align_forks_for_even_number(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;
	{
		while (i < d->nb_philos)
		{
			ph[i]->first_fork = &d->mtx_fork[i];
			if (i == d->nb_philos - 1)
				ph[i]->second_fork = &d->mtx_fork[0];
			else
				ph[i]->second_fork = &d->mtx_fork[i + 1];
			i++;
		}
	}
	return (TRUE);
}


t_philo	**ft_create_philos_mem(t_args *d)
{
	t_philo	**ph;
	size_t		i;

	ph = (t_philo **)malloc(sizeof(t_philo *) * d->nb_philos);
	if (!ph)
		return (NULL);
	i = 0;
	while (i < d->nb_philos)
	{
		ph[i] = malloc(sizeof(t_philo) * 1);
		if (!ph[i])
		{
			while (i-- > 0)
				free(ph[i]);
			free(ph);
			return (NULL);
		}
		ph[i]->last_meal = d->start_time;
		ph[i]->d = d;
		ph[i]->index = i;
		ph[i]->id = i + 1;
		ph[i]->n_meals = 0;
		ph[i]->all_eaten = 0;
		ph[i]->max_meals = d->nb_must_eat;
		i++;
	}

	// if (d->nb_philos >= 2 && d->nb_philos % 2 == 0)
	// 	ft_align_forks_for_even_number(ph, d);
	// else if (d->nb_philos >= 3 && d->nb_philos % 2 != 0)
	// 	; //NEEED FUNCTION FOR THIS CASE
	
	//need function for only one philo
	return (ph);
}
