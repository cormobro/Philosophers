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
		philos[i].eaten = 0;
		philos[i].left = philos[i].id;
		philos[i].right = (philos[i].left + 1) % philos[i].data->philos;
		philos[i].data->is_ready[i] = 0;
		i++;
	}
	philos[0].data->start_time = ft_gettime();
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

static void	*ft_monitor(void * datas)
{
	t_philos	*philos = (t_philos*) datas;
	int	timer;
	int	i;
	long int	time;

	timer = philos->data->time_to_eat + philos->data->time_to_sleep + 30;
	if (timer < philos->data->time_to_die)
		timer = philos->data->time_to_die + 10;
	i = 0;
	while (i <= timer)
	{
		pthread_mutex_lock(philos->data->death);
		time = ft_gettime();
		if (philos->last_dinner && time - philos->last_dinner >= philos->data->time_to_die && philos->data->is_alive[0] == 1)
		{
			pthread_mutex_lock(philos->data->dead);
			philos->data->is_alive[0] = 0;
			pthread_mutex_unlock(philos->data->dead);
			pthread_mutex_lock(philos->data->print);
			printf("%ld %d has died", time - philos->data->start_time, philos->id + 1);
			pthread_mutex_unlock(philos->data->print);
			pthread_mutex_unlock(philos->data->death);
			return (0);
		}
		pthread_mutex_unlock(philos->data->death);
		pthread_mutex_lock(philos->data->dead);
		if (!philos->data->is_alive[0])
		{
			pthread_mutex_unlock(philos->data->dead);
			return (0);
		}
		pthread_mutex_unlock(philos->data->dead);
		ft_usleep(1);
		i++;
	}
	return (0);
}

/*static int	ft_ready(void * datas)
{
	t_philos	*philos = (t_philos*) datas;
	int		i;
	int		res;

	i = 0;
	res = 1;
	while (i < philos->data->philos)
	{
		if (philos->data->is_ready[i] == 0)
			res = 0;
		i++;
	}
	return (res);
}*/

void	*ft_philosopher(void * datas)
{
	t_philos	*philos = (t_philos*)	datas;
	pthread_t	*monitor;

	/*philos->data->is_ready[philos->id] = 1;
	while (!ft_ready(philos))
		usleep(10);*/
	philos->last_dinner = ft_gettime();
	if (philos->id % 2 == 1)
		usleep(100);
	pthread_mutex_lock(philos->data->dead);
	while (philos->eaten < philos->data->servings && philos->data->is_alive[0])
	{
		pthread_mutex_unlock(philos->data->dead);
		monitor = malloc(sizeof(pthread_t));
		if (!monitor)
			return (0);
		if (pthread_create(monitor, NULL, &ft_monitor, philos))
			return (0);
		ft_print(philos, "is thinking");
		if (philos->left < philos->right)
		{
			pthread_mutex_lock(&philos->data->forks[philos->left]);
			ft_print(philos, "has taken a fork");
			pthread_mutex_lock(&philos->data->forks[philos->right]);
			ft_print(philos, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&philos->data->forks[philos->right]);
			ft_print(philos, "has taken a fork");
			if (philos->data->philos != 1)
			{
				pthread_mutex_lock(&philos->data->forks[philos->left]);
				ft_print(philos, "has taken a fork");
			}
		}
		if (philos->data->philos != 1)
		{
			pthread_mutex_lock(philos->data->death);
			philos->last_dinner = ft_gettime();
			pthread_mutex_unlock(philos->data->death);
			ft_print(philos, "is eating");
		}
		ft_usleep(philos->data->time_to_eat);
		if (philos->data->philos != 1)
			pthread_mutex_unlock(&philos->data->forks[philos->left]);
		pthread_mutex_unlock(&philos->data->forks[philos->right]);
		if (philos->data->philos != 1)
			ft_print(philos, "is sleeping");
		ft_usleep(philos->data->time_to_sleep);
		philos->eaten++;
		pthread_detach(*monitor);
		pthread_mutex_lock(philos->data->dead);
	}
	pthread_mutex_unlock(philos->data->dead);
	ft_usleep(philos->data->time_to_die + philos->data->time_to_eat + philos->data->time_to_sleep);
	return (NULL);
}
