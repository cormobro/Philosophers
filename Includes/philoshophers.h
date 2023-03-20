#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_philo
{
	int	philos;
	int	servings;
	float	time_to_die;
	float	time_to_eat;
	float	time_to_sleep;
}	t_philo;

int	main(int argc, char **argv);

#endif
