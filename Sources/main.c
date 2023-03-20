#include "../Includes/philosophers.h"

static int	ft_free(t_philo *data)
{
	free(data->dead);
	free(data->print);
	free(data->forks);
	free(data->is_alive);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	data;
	int		err;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Error: Wrong number of arguments"));
	else
	{
		if (!(ft_check_fill(argc, argv, &data)))
			return (ft_print_error("Error: Invalid arguments"));
	}
	err = ft_init_mutex(&data);
	if (err != 0)
		return (ft_free(&data));
	err = ft_destroy_mutex(&data);
	if (err != 0)
		return (ft_free(&data));
	return (ft_free(&data));
}
