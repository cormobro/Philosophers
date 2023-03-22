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

static	float	ft_atofbis(int i, char *str)
{
	float	res;
	float	comma;

	res = 0;
	while (str[i] && str[i] <= '9' && str[i] >= '0')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] && str[i++] == '.')
	{
		comma = 10;
		while (str[i] && str[i] <= '9' && str[i] >= '0')
		{
			res = res + ((str[i] - '0') / comma);
			comma *= 10;
			i++;
		}
	}
	if (res > 2147483648)
		return (0);
	return (res);
}

float	ft_atof(char *str)
{
	int		i;
	float	sign;

	if (!str)
		return (0);
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9)))
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] && (str[i] == '+' || str[i] == '-'))
		return (0);
	return (sign * ft_atofbis(i, str));
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
