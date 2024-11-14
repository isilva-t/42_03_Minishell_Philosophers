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

int	ft_mtx_are_all_threads_running(t_philo *ph)
{
	pthread_mutex_lock(&ph->d->mtx_all_tds_running);
	if (ph->d->all_tds_running == ph->n_philos)
	{
		pthread_mutex_unlock(&ph->d->mtx_all_tds_running);
		return (TRUE);
	}
	pthread_mutex_unlock(&ph->d->mtx_all_tds_running);
	return (FALSE);
}

void	*ft_philo_dinner_plan(void *arg)
{
	t_philo			*ph;

	ph = (t_philo *)arg;
	while (1)
		if (ft_mtx_are_all_threads_running(ph) == TRUE)
			break ;
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
		//usleep(500);
	}
	return (NULL);
}

void	ft_mtx_increase_created_threads(t_args *d)
{
	pthread_mutex_lock(&d->mtx_all_tds_running);
	d->all_tds_running++;
	pthread_mutex_unlock(&d->mtx_all_tds_running);
}

void	ft_mtx_save_start_time(t_philo *ph, size_t start_time)
{
	pthread_mutex_lock(&ph->mtx_philo);
	ph->last_meal = start_time;
	pthread_mutex_unlock(&ph->mtx_philo);
}

void	ft_set_start_time(t_args *d, t_philo **ph)
{
	size_t i;
	size_t nb_philos;
	size_t start_time;

	i = 0;
	nb_philos = d->nb_philos;

	start_time = ft_get_time();
	d->start_time = start_time;
	while (i < nb_philos)
	{
		ft_mtx_save_start_time(ph[i++], start_time);
	}
}

int	ft_let_the_game_begin(t_philo **ph, t_args *d)
{
	size_t	i;

	i = 0;
	if (d->nb_philos == 0)
		return (FALSE);
	// else if (d->nb_philos == 1)
	// 	pthread_create(&(ph[0]->td), NULL,
	// 		&ft_one_philo_case, (void *)ph[0]);
	while (i < d->nb_philos)
	{
		pthread_create(&(ph[i]->td), NULL,
			&ft_philo_dinner_plan, (void *)ph[i]);
		i++;
		if (i == d->nb_philos)
			ft_set_start_time(d, ph);
		ft_mtx_increase_created_threads(d);
	}
	return (TRUE);
}
