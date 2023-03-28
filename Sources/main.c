#include "../Includes/philosophers.h"

static int	ft_free(t_philo *data)
{
	if (data->dead)
		free(data->dead);
	if (data->print)
		free(data->print);
	if (data->forks)
		free(data->forks);
	if (data->is_alive)
		free(data->is_alive);
	return (0);
}

static int	philosophers(t_philo *data)
{
	int		err;
	pthread_t	threads[data->philos];

	err = ft_init_mutex(data);
	if (err != 0)
		return (ft_free(data));
	//DESTROY MUTEXES IF THREADS FAIL?
	err = ft_init_threads(data, threads, err);
	if (err != 0)
		return (ft_free(data));
	//while (data->is_alive[0] == 1 && data->stuffed == 0)
	//	ft_stuffed(data);
	err = ft_join_threads(data, threads, err);
	if (err != 0)
		return (0);
	err = ft_destroy_mutex(data);
	if (err != 0)
		return (ft_free(data));
	return (ft_free(data));
}

int	main(int argc, char **argv)
{
	t_philo	data;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Error: Wrong number of arguments"));
	else
	{
		if (!(ft_check_fill(argc, argv, &data)))
			return (ft_print_error("Error: Invalid arguments"));
	}
	return (philosophers(&data));
}
