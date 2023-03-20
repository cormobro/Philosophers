/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febonaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:19:55 by febonaer          #+#    #+#             */
/*   Updated: 2023/03/20 17:55:57 by febonaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

static int	ft_free_fill(t_philo *data, int nb)
{
	if (nb == 1)
	{
		free(data->forks);
		return (0);
	}
	else if (nb == 2)
	{
		free(data->forks);
		free(data->dead);
		return (0);
	}
	else
	{
		free(data->forks);
		free(data->dead);
		free(data->print);
		return (0);
	}
}

static int	ft_fill(int argc, char **argv, t_philo *data)
{
	data->philos = ft_atoi(argv[1]);
	if (argc == 6)
		data->servings = ft_atoi(argv[5]);
	data->time_to_die = ft_atof(argv[2]);
	data->time_to_eat = ft_atof(argv[3]);
	data->time_to_sleep = ft_atof(argv[4]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philos);
	if (!data->forks)
		return (0);
	data->dead = malloc(sizeof(pthread_mutex_t));
	if (!data->dead)
		return (ft_free_fill(data, 1));
	data->print = malloc(sizeof(pthread_mutex_t));
	if (!data->print)
		return (ft_free_fill(data, 2));
	data->is_alive = malloc(sizeof(int));
	if (!data->is_alive)
		return (ft_free_fill(data, 3));
	data->is_alive[0] = 1;
	return (1);
}

int	ft_check_fill(int argc, char **argv, t_philo *data)
{
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (0);
	}
	if (ft_atof(argv[2]) <= 0 || ft_atof(argv[3]) <= 0 || ft_atof(argv[4]) <= 0)
		return (0);
	if (!ft_fill(argc, argv, data))
		return (0);
	return (1);
}
