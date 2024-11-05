#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data
{
	pthread_t td;
	int id;
	pthread_mutex_t	*mute;
	int	*point;
	int	sum;
}	t_data;

void	*routine(void *arg)
{
	int i;
	t_data *d;

	d = (t_data *)arg;
	printf(" th.id = %d\n\n", d->id);
	i = 0;
	while (i < 5)
	{
		if (d->id == 1)
			 d->sum = d->sum + d->point[i + 5];
		else
			 d->sum = d->sum + d->point[i];
		i++;
	}
	return (NULL);
}

int main(void)
{
	t_data	d[2];
	int	i;
	int prime[10] = {1,1,1,1,1, 3, 3, 3, 3, 0};
	pthread_mutex_t mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < 2)
	{
		d[i].sum = 0;
		d[i].point = prime;
		d[i].id = i;
		d[i].mute = &mutex;
		i++;
	}
	i = 0;
	while (i < 2)
	{
		pthread_create(&d[i].td, NULL, &routine, (void *)&d[i]);
		i++;
	}
	while (i-- > 0)
	{
		pthread_join(d[i].td, NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("sum: %d \n", d[1].sum + d[0].sum);

}
