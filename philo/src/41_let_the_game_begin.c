/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   41_let_the_game_begin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:48:42 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/07 14:22:56 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stop_the_game(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;
	//printf("nr philos %lu\n", d->nb_philos);
	//usleep(1000);
	while (i < d->nb_philos)
	{
		pthread_join(ph[i]->td, NULL);
		i++;
	}
}
