#include "../Includes/philosophers.h"

int	ft_init_threads(t_philo *data, pthread_t *threads, int err)
{
	int			i;
	t_philos	philos[data->philos];

	i = 0;
	while (i < data->philos)
	{
		philos[i].data = data;
		philos[i].id = i;
		i++;
	}
	usleep(100);
	i = 0;
	while (i < data->philos)
	{
		err = pthread_create(&threads[i], NULL, &ft_philosopher, &philos[i]);
		if (err != 0)
			return (1);
		i++;
	}
	usleep(100);
	return (err);
}

int	ft_join_threads(t_philo *data, pthread_t *threads, int err)
{
	int	i;
	int	*r;

	i = 0;
	while (i < data->philos)
	{
		err = pthread_join(threads[i], (void **) &r);
		free(r);
		if (err != 0)
			return (1);
		i++;
	}
	//usleep(1000000);
	return (err);
}

void	*ft_philosopher(void * datas)
{
	t_philos	*philos = (t_philos*)	datas;
	int *r = malloc(sizeof(int));
	*r = 1;
	int	left;
	int	right;
	int eaten;

	eaten = 0;
	left = philos->id;
	right = (left + 1) % philos->data->philos;
	while (eaten < philos->data->servings)
	{
		if (left < right)
		{
			pthread_mutex_lock(&philos->data->forks[left]);
			pthread_mutex_lock(&philos->data->forks[right]);
		}
		else
		{
			pthread_mutex_lock(&philos->data->forks[right]);
			pthread_mutex_lock(&philos->data->forks[left]);
		}
		ft_print(philos, 1);
		//printf("Le philosophe %d mange.\n", philos->id);
		pthread_mutex_unlock(&philos->data->forks[left]);
		pthread_mutex_unlock(&philos->data->forks[right]);
		//usleep(philos->data->time_to_sleep * 1000);
		//usleep(1000);
		eaten++;
	}
	printf("%d\n", philos->id);
	//printf("%d\n", right);
	//usleep(100000);
	return ((void *) r);
}
