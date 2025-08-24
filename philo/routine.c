/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:17:55 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/13 19:40:04 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_is_eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->philo_num == 1)
	{
		special_situation(philo);
		return ;
	}
	take_the_forks(philo);
	print_action(philo, "is eating");
	ft_usleep(data->time_to_eat, data);
	release_the_forks(philo);
	update_meal_info(philo);
}

static void	philo_is_sleeping(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

static void	philo_is_thinking(t_philo *philo)
{
	print_action(philo, "is thinking");
	ft_usleep(philo->think_time, philo->data);
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 1)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (1)
	{
		if (simulation_ended(philo->data))
			break ;
		philo_is_eating(philo);
		if (simulation_ended(philo->data))
			break ;
		philo_is_sleeping(philo);
		if (simulation_ended(philo->data))
			break ;
		philo_is_thinking(philo);
	}
}
