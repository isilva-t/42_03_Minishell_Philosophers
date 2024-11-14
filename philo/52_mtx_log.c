/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   52_mtx_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:54:21 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/14 09:55:19 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_log(t_philo *ph, char *what_are_doing, size_t n_philos)
{
	size_t	i;
	size_t	actual_time;

	actual_time = 0;
	i = 0;
	pthread_mutex_lock(&ph->d->mtx_died);
	if (ph->d->is_died == FALSE)
	{
		pthread_mutex_lock(&ph->d->mtx_log);
		while (i < n_philos)
		{
			printf("\t\t\t\t");
			i++;
		}
		actual_time = ft_get_time() - ph->d->start_time;
		printf("%zu\t%d %s\n", actual_time, ph->id, what_are_doing);
		pthread_mutex_unlock(&ph->d->mtx_log);
	}
	pthread_mutex_unlock(&ph->d->mtx_died);
}
