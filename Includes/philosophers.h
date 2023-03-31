#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t *forks;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*print;
	int	*is_alive;
	int	*is_stuffed;
	int	philos;
	int	servings;
	int	stuffed;
	float	time_to_die;
	float	time_to_eat;
	float	time_to_sleep;

}	t_philo;

typedef struct s_philos
{
	t_philo		*data;
	int			id;
	long int	last_dinner;
}	t_philos;

int				main(int argc, char **argv);
int				ft_print_error(char *str);
int				ft_check_fill(int argc, char **argv, t_philo *data);
int				ft_init_mutex(t_philo *data);
int				ft_destroy_mutex(t_philo *data);
int				ft_init_threads(t_philo *data, pthread_t *threads, int err);
int				ft_join_threads(t_philo *data, pthread_t *threads, int err);
long int		ft_gettime();
long long int	ft_atoi(const char *str);
float			ft_atof(char *str);
void				ft_stuffed(t_philo *data);
void				*ft_philosopher(void * data);
void			ft_print(t_philos *philos, char *str);

#endif
