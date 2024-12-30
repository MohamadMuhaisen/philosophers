/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 03:10:01 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/30 03:10:47 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	return ((c >= 48 && c <= 57));
}

int	ft_isspace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * nb);
}

int	validate_args(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if ((ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
			|| (ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60
				|| ft_atoi(av[4]) < 60) || (ac == 6 && ft_atoi(av[5]) < 1))
		{
			printf("Invalid args :(\n");
			return (0);
		}
		return (1);
	}
	return (0);
}
