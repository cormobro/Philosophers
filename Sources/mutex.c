/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febonaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:04:39 by febonaer          #+#    #+#             */
/*   Updated: 2023/03/20 19:32:01 by febonaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

int	ft_destroy_mutex(t_philo *data)
{
	int	i;
	int	err;

	i = 0;
	err = pthread_mutex_destroy(data->dead);
	if (err != 0)
		return (1);
	err = pthread_mutex_destroy(data->print);
	if (err != 0)
		return (1);
	i = 0;
	while (i < data->philos)
	{
		err = pthread_mutex_destroy(&data->forks[i++]);
		if (err != 0)
			return (1);
	}
	return (err);
}

int ft_init_mutex(t_philo *data)
{
	int	i;
	int	err;

	i = 0;
	while (i < data->philos)
	{
		err = pthread_mutex_init(&data->forks[i++], NULL);
		if (err != 0)
			return (1);
	}
	err = pthread_mutex_init(data->dead, NULL);
	if (err != 0)
		return (1);
	err = pthread_mutex_init(data->print, NULL);
	if (err != 0)
		return (1);
	return (err);
}