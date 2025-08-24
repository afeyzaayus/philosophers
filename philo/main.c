/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:10:02 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 20:20:27 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	start(int argc, char **argv, t_data *data, t_philo **philos)
{
	init_data(argc, argv, data);
	*philos = malloc(sizeof(t_philo) * data->philo_num);
	if (!(*philos))
		return (!write(2, "Error: Failed to allocate memory for philos\n", 44));
	if (!init_mutex(data))
	{
		write(2, "Error: Failed to initialize mutexes\n", 37);
		cleanup_resources(data, philos, 0);
		return (0);
	}
	init_philos(data, *philos);
	if (!init_threads(data, *philos))
	{
		write(2, "Error: Failed to create threads\n", 32);
		cleanup_resources(data, philos, 1);
		return (0);
	}
	if (!join_threads(data, philos))
	{
		write(2, "Error: Failed to join threads\n", 30);
		cleanup_resources(data, philos, 1);
		return (0);
	}
	cleanup_resources(data, philos, 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (!check_arguments(argc, argv))
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (!start(argc, argv, &data, &philo))
		return (1);
	return (0);
}
