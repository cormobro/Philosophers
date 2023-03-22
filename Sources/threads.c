#include "../Includes/philosophers.h"

int	ft_init_threads(t_philo *data, pthread_t *threads, int err)
{
	int	i;

	i = 0;
	while (i < data->philos)
	{
		data->id = i;
		err = pthread_create(&threads[i], NULL, &ft_philosopher, data);
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

void	*ft_philosopher(void * datas)
{
	t_philo	*data = (t_philo*) datas;
	int *r = malloc(sizeof(int));
	*r = 1;
	printf("%d\n", data->id);
	return ((void *) r);
}
