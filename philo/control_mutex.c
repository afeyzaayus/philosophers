/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:20:59 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/13 16:18:12 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	special_situation(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(philo->fork_left);
	print_action(philo, "has taken a fork");
	ft_usleep(data->time_to_die, data);
	pthread_mutex_unlock(philo->fork_left);
}

int	simulation_ended(t_data *data)
{
	pthread_mutex_lock(&data->control_mutex);
	if (data->control_flag == 1)
	{
		pthread_mutex_unlock(&data->control_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->control_mutex);
	return (0);
}

void	take_the_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_left);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_action(philo, "has taken a fork");
	}
}

void	update_meal_info(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	release_the_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}
