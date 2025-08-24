/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 20:21:55 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 20:22:48 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	destroy_mutex(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->fork_num)
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			return (0);
	if (pthread_mutex_destroy(&data->control_mutex) != 0)
		return (0);
	if (pthread_mutex_destroy(&data->meal_mutex))
		return (0);
	if (pthread_mutex_destroy(&data->print_mutex))
		return (0);
	if (pthread_mutex_destroy(&data->simulation_control))
		return (0);
	return (1);
}

void	cleanup_resources(t_data *data, t_philo **philos, int flag)
{
	if (flag)
		if (!destroy_mutex(data))
			return ;
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	if (*philos)
	{
		free(*philos);
		*philos = NULL;
	}
}
