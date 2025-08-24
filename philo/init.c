/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:09:52 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 20:22:31 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	init_data(int argc, char **argv, t_data *data)
{
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->fork_num = data->philo_num;
}

void	init_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		philos[i].philo_id = i + 1;
		philos[i].fork_left = &data->forks[i];
		philos[i].fork_right = &data->forks[(i + 1) % data->philo_num];
		philos[i].eat_count = 0;
		philos[i].think_time = find_think_time(data);
		philos[i].data = data;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(t_mutex) * data->fork_num);
	if (!data->forks)
		return (0);
	while (++i < data->fork_num)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
	if (pthread_mutex_init(&data->control_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->simulation_control, NULL) != 0)
		return (0);
	return (1);
}
