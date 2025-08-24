/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:10:05 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 18:58:19 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_starvation(t_philo *philo, t_data *data, int i)
{
	long long	current_time;
	long long	time_since_last_meal;

	current_time = get_time();
	time_since_last_meal = current_time - philo[i].last_meal_time;
	if (time_since_last_meal > data->time_to_die)
	{
		pthread_mutex_lock(&data->control_mutex);
		data->control_flag = 1;
		pthread_mutex_unlock(&data->control_mutex);
		print_action(&philo[i], "died");
		return (1);
	}
	return (0);
}

static int	check_philo_situation(t_philo *philo, t_data *data, int *all_philos)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (check_starvation(philo, data, i))
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (1);
		}
		if ((data->must_eat != -1) && (philo[i].eat_count >= data->must_eat))
			(*all_philos)++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

static int	did_everyone_eat(t_data *data, int all_philos)
{
	if (data->must_eat != -1 && all_philos == data->philo_num)
	{
		pthread_mutex_lock(&data->control_mutex);
		data->control_flag = 1;
		pthread_mutex_unlock(&data->control_mutex);
		return (1);
	}
	return (0);
}

void	*observer(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	int			all_philos;

	philo = (t_philo *)arg;
	data = philo[0].data;
	while (1)
	{
		all_philos = 0;
		if (check_philo_situation(philo, data, &all_philos))
			return (NULL);
		if (did_everyone_eat(data, all_philos))
			return (NULL);
	}
	return (NULL);
}
