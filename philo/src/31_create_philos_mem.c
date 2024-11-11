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

		ph[i]->start_delay = ph[i]->id % 2 * 50; // TO TEST EVEN PHILOS
		i++;
	}

//	if (d->nb_philos >= 2 && d->nb_philos % 2 == 0)
//	else if (d->nb_philos >= 3 && d->nb_philos % 2 != 0)
//	 	; //NEEED FUNCTION FOR THIS CASE
	
	//need function for only one philo
	return (ph);
}
