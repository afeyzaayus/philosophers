/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:57:22 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 20:12:34 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	is_valid_number(char *str)
{
	long long	num;
	int			i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	while (str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) > 11)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	num = ft_atol(str);
	if (num > MAX_INT || num <= 0)
		return (0);
	return (1);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (!(write(2, "Invalid arguments number!\n", 26)));
	while (argv[i])
	{
		if (!is_valid_number(argv[i]))
			return (!(write(2, "Invalid argument!\n", 18)));
		i++;
	}
	return (1);
}
