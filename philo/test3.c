#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define SIZE	1000000
#define MID		(SIZE / 2)

typedef struct s_data
{
	pthread_mutex_t mute;
	int sum;
	int	*read;
	int	n_workers;
	int	count;
}	t_data;


typedef struct s_work
{
	pthread_t td;
	int id;
	pthread_mutex_t	*mute_sum;
	t_data *d;
	int		td_sum;
}	t_work;

t_work	**do_work_info(int j, t_data *d)
{
	t_work	**w;
	int i;

	w = (t_work **)malloc(sizeof(t_work *) * j);
	if (!w)
		return (NULL);
	i = 0;
	while (i < j)
	{
		w[i] = malloc(sizeof(t_work) * 1);
		if (!w[i])
		{
			while (i-- > 0)
				free(w[i]);
			free(w);
			return (NULL);
		}
		w[i]->d = d;
		w[i]->id = i;
		w[i]->td_sum = 0;
		i++;
	}
	return (w);
}


#define N_TD	2
#define HALF	1
#define MUTEX_ENABLE 1


void	*routine(void *arg)
{
	t_work	*w;

	w = (t_work *)arg;


	pthread_mutex_lock(&w->d->mute);
	while (++w->d->count < SIZE)
	{
		pthread_mutex_unlock(&w->d->mute);

		pthread_mutex_lock(&w->d->mute);
		// if (w->id >= HALF)
		// {
		// 	w->d->sum += w->d->read[w->d->count + MID];
		// 	w->td_sum += w->d->read[w->d->count + MID];
		// }
		// else
		// {
			w->d->sum += w->d->read[w->d->count];
			w->td_sum += w->d->read[w->d->count];
		//}

		pthread_mutex_unlock(&w->d->mute);

		pthread_mutex_lock(&w->d->mute);
	}

	return (NULL);
}



int main(void)
{
	t_work **w;
	t_data	d;
	int	i;
	int j;
	int array[SIZE];

	i = 0;
	j = 0;
	while (i < SIZE)
	{
		if (i >= MID)
			j = 1;
		array[i] = 1 + j;
		i++;
	}
	pthread_mutex_init(&d.mute, NULL);
	d.read = array;
	d.sum = 0;
	d.n_workers = N_TD;
	d.count = -1;
	
	w = do_work_info(N_TD, &d);
	if (!w)
		return (1);
	i = -1;
	while (++i < N_TD)
		pthread_create(&w[i]->td, NULL, &routine, (void *)w[i]);

	printf("lets do the party!\n");

	while (i-- > 0)
		pthread_join(w[i]->td, NULL);
	
	printf("sum: %d \n", d.sum);
	i = -1;
	while (++i < N_TD)
		printf("Thread %d handle this sum: %d\n", w[i]->id, w[i]->td_sum);
	i = 0;
	pthread_mutex_destroy(&d.mute);
	while (i < N_TD)
		free(w[i++]);
	free(w);

}
