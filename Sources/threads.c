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
		philos[i].last_dinner = 0;
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

static void	*ft_monitor(void * datas)
{
	t_philos	*philos = (t_philos*) datas;
	int	timer;
	int	i;

	timer = (philos->data->time_to_eat + philos->data->time_to_sleep) / philos->data->time_to_die;
	i = 0;
	usleep((philos->data->time_to_die) / 10);
	while (i <= timer + 1)
	{
		pthread_mutex_lock(philos->data->death);
		if (philos->last_dinner && ft_gettime() - philos->last_dinner >= philos->data->time_to_die && philos->data->is_alive[0] == 1)
		{
			pthread_mutex_lock(philos->data->dead);
			philos->data->is_alive[0] = 2;
			pthread_mutex_unlock(philos->data->dead);
			pthread_mutex_lock(philos->data->print);
			printf("%ld %d has died", ft_gettime(), philos->id);
			pthread_mutex_unlock(philos->data->print);
			pthread_mutex_unlock(philos->data->death);
			return (0);
		}
		pthread_mutex_unlock(philos->data->death);
		usleep(philos->data->time_to_die);
		i++;
	}
	return (0);
}

void	*ft_philosopher(void * datas)
{
	t_philos	*philos = (t_philos*)	datas;
	pthread_t	*monitor;
	int *r = malloc(sizeof(int));
	*r = 1;
	int	left;
	int	right;
	int eaten;

	eaten = 0;
	left = philos->id;
	right = (left + 1) % philos->data->philos;
	while (eaten < philos->data->servings && philos->data->is_alive[0] == 1)
	{
		monitor = malloc(sizeof(pthread_t));
		if (!monitor)
			return (0);
		if (pthread_create(monitor, NULL, &ft_monitor, philos))
			return (0);
		if (philos->data->is_alive[0] == 1)
			ft_print(philos, "is thinking");
		if (left < right && philos->data->is_alive[0] == 1)
		{
			pthread_mutex_lock(&philos->data->forks[left]);
			ft_print(philos, "has taken a fork");
			pthread_mutex_lock(&philos->data->forks[right]);
			ft_print(philos, "has taken a fork");
		}
		else if (philos->data->is_alive[0] == 1)
		{
			pthread_mutex_lock(&philos->data->forks[right]);
			ft_print(philos, "has taken a fork");
			pthread_mutex_lock(&philos->data->forks[left]);
			ft_print(philos, "has taken a fork");
		}
		pthread_mutex_lock(philos->data->death);
		philos->last_dinner = ft_gettime();
		pthread_mutex_unlock(philos->data->death);
		if (philos->data->is_alive[0] == 1)
			ft_print(philos, "is eating");
		usleep(philos->data->time_to_eat * 1000);
		pthread_mutex_unlock(&philos->data->forks[left]);
		pthread_mutex_unlock(&philos->data->forks[right]);
		usleep(philos->data->time_to_sleep * 1000);
		if (philos->data->is_alive[0] == 1)
			ft_print(philos, "is sleeping");
		eaten++;
		pthread_detach(*monitor);
	}
	philos->data->is_stuffed[philos->id] = 1;
	return ((void *) r);
}
