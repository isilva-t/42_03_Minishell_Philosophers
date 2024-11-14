/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42_let_the_game_begin_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isilva-t <isilva-t@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:01:29 by isilva-t          #+#    #+#             */
/*   Updated: 2024/11/14 10:02:52 by isilva-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_mtx_have_reached_max_meals(t_philo *ph)
{
	if (ph->n_meals == ph->max_meals)
	{
		pthread_mutex_lock(&ph->mtx_eat_done);
		ph->eating_done = TRUE;
		pthread_mutex_unlock(&ph->mtx_eat_done);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_mtx_save_meal_time(t_philo *ph)
{
	pthread_mutex_lock(&ph->mtx_philo);
	ph->last_meal = ft_get_time();
	pthread_mutex_unlock(&ph->mtx_philo);
}

void	ft_mtx_take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->first_fork);
	ft_log(ph, S_FORK, ph->index);
	pthread_mutex_lock(ph->second_fork);
	ft_log(ph, S_FORK, ph->index);
}

void	ft_mtx_leave_forks(t_philo *ph)
{
	pthread_mutex_unlock(ph->second_fork);
	pthread_mutex_unlock(ph->first_fork);
}
