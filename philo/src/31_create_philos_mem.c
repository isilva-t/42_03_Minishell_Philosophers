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
	int		i;

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
		ph[i]->d = d;
		ph[i]->id = i + 1;
		i++;
	}
	return (ph);
}
