/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febonaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:50:45 by febonaer          #+#    #+#             */
/*   Updated: 2023/04/03 18:50:47 by febonaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosophers.h"

long long int	ft_atoi(const char *str)
{
	long long	i;
	long long	r;
	long long	s;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			s = s * -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0') * s;
		i++;
		if (r > 2147483647 || r < -2147483648)
			return (2147483648);
		if (r * s < 0 && s == 1)
			return (-1);
		if (r * s < 0 && s != 1)
			return (0);
	}
	return (r);
}

void	ft_stuffed(t_philo *data)
{
	int	i;

	i = 0;
	if (data->is_stuffed[0])
	{
		while (data->is_stuffed[i] == data->servings)
			i++;
		if (i == data->philos)
			data->stuffed = 1;
	}
}
