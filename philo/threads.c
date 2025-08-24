/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:10:16 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 19:36:52 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join((*philos)[i].thread_id, NULL) != 0)
			return (0);
	}
	if (pthread_join(data->observer_thread, NULL) != 0)
		return (0);
	return (1);
}

static void	*wait(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		pthread_mutex_lock(&data->simulation_control);
		if (data->simulation_start)
		{
			pthread_mutex_unlock(&data->simulation_control);
			break ;
		}
		pthread_mutex_unlock(&data->simulation_control);
	}
	routine(philo);
	return (NULL);
}

int	init_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		if (pthread_create(&philos[i].thread_id, NULL, &wait, &philos[i]) != 0)
			return (0);
	data->start_time = get_time();
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->meal_mutex);
		philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	pthread_mutex_lock(&data->simulation_control);
	data->simulation_start = 1;
	pthread_mutex_unlock(&data->simulation_control);
	if (pthread_create(&data->observer_thread, NULL, &observer,
			(void *)philos) != 0)
		return (0);
	return (1);
}
