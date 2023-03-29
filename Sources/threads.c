#include "../Includes/philosophers.h"

int	ft_init_threads(t_philo *data, pthread_t *threads, int err)
{
	int			i;
	t_philos	*philos;

	philos = malloc(sizeof(t_philos) * data->philos);
	if (!philos)
		return (0);
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
		usleep(100);
	}
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
	return (err);
}

/*static int	is_stuffed(t_philos *philos)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < philos->data->philos)
	{
		if (philos->data->is_stuffed[i] != 1)
		{
			res = 0;
			break ;
		}
		i++;
	}
	return (res);
}*/

/*static void	*ft_monitor(void * datas)
{
	t_philos	*philos = (t_philos*) datas;


}*/

void	*ft_philosopher(void * datas)
{
	t_philos	*philos = (t_philos*)	datas;
	//pthread_t	*monitor;
	int *r = malloc(sizeof(int));
	*r = 1;
	int	left;
	int	right;
	int eaten;

	printf("time is: %ld\n", ft_gettime());
	//monitor = malloc(sizeof(pthread_t));
	//if (pthread_create(&monitor, NULL, &ft_monitor, philos))
	//	return ;
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
		pthread_mutex_unlock(&philos->data->forks[left]);
		pthread_mutex_unlock(&philos->data->forks[right]);
		usleep(philos->data->time_to_sleep * 1000);
		eaten++;
	}
	philos->data->is_stuffed[philos->id] = 1;
	return ((void *) r);
}
