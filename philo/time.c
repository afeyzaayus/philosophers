/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 19:00:51 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 19:14:20 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval	tv;
	long long		miliseconds;

	gettimeofday(&tv, ((void *)0));
	miliseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (miliseconds);
}

void	ft_usleep(long long time_in_ms, t_data *data)
{
	long long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time_in_ms)
	{
		if (simulation_ended(data))
			return ;
		usleep(100);
	}
}

long long	find_think_time(t_data *data)
{
	long long	think_time;

	if (data->philo_num % 2 == 1)
	{
		if (data->time_to_eat == data->time_to_sleep)
			think_time = data->time_to_eat;
		else if (data->time_to_eat > data->time_to_sleep)
			think_time = 2 * data->time_to_eat - data->time_to_sleep;
		else
			think_time = 0;
	}
	else
	{
		if (data->time_to_eat == data->time_to_sleep)
			think_time = 0;
		else if (data->time_to_eat > data->time_to_sleep)
			think_time = data->time_to_eat - data->time_to_sleep;
		else
			think_time = 0;
	}
	return (think_time);
}
