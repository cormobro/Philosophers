/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febonaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:19:55 by febonaer          #+#    #+#             */
/*   Updated: 2023/04/07 15:39:03 by febonaer         ###   ########.fr       */
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
	else if (nb == 3)
	{
		free(data->forks);
		free(data->dead);
		free(data->print);
		return (0);
	}
	free(data->forks);
	free(data->dead);
	free(data->print);
	free(data->is_alive);
	return (0);
}

static int	ft_fill(int argc, char **argv, t_philo *data)
{
	data->philos = ft_atoi(argv[1]);
	data->stuffed = 0;
	data->servings = 2147483647;
	if (argc == 6)
		data->servings = ft_atoi(argv[5]);
	if (data->philos == 1)
		data->servings = 1;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
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
	data->is_ready = malloc(sizeof(int) * data->philos);
	if (!data->is_ready)
		return (ft_free_fill(data, 4));
	data->is_alive[0] = 1;
	return (1);
}

int	ft_check_fill(int argc, char **argv, t_philo *data)
{
	int	i;

	if (ft_atoi(argv[1]) <= 0)
		return (0);
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (0);
	}
	if (ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0)
		return (0);
	if (!ft_fill(argc, argv, data))
		return (0);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (ft_free_fill(data, 4));
	i = -1;
	return (1);
}
