#include "../Includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*data;

	if (argc < 5 || argc > 6)
		return (ft_print_error("Error: Wrong number of arguments"));
	else
	{
		if (!(ft_check_fill(argc, argv, &data)))
			return (ft_print_error("Error: Invalid arguments"));
	}
}
