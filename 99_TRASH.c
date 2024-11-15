void	ft_mtx_save_start_time(t_philo *ph, size_t start_time)
{
	//pthread_mutex_lock(&ph->mtx_philo);
	ph->last_meal = start_time;
	//pthread_mutex_unlock(&ph->mtx_philo);
}
