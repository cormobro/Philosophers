/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febonaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:49:05 by febonaer          #+#    #+#             */
/*   Updated: 2023/04/03 16:26:42 by febonaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

void		ft_usleep(int time)
{
	long int	currenttime;

	currenttime = ft_gettime();
	if (!currenttime)
		return ;
	while (ft_gettime() - currenttime < time)
		usleep(10);
}

long int	ft_gettime()
{
	struct timeval	time;
	long int		res;

	if (gettimeofday(&time, NULL) != 0)
		return (0);
	if (time.tv_usec >= 1000)
		res = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	else if (time.tv_usec < 1000 && time.tv_usec > 500)
		res = (time.tv_sec * 1000) + 1;
	else
		res = (time.tv_sec * 1000);
	return (res);
}
