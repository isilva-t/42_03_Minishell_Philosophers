#include "philo.h"

void	*my_thread(void *arg)
{
	(void)arg;
	usleep(5000);
	printf("Print fron Thread\n");
	usleep(5000);
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	th_id;

	(void)ac;
	(void)av;

	printf("before thread\n");
	pthread_create(&th_id, NULL, my_thread, NULL);
	pthread_join(th_id, NULL);
	printf("after\n");
}
