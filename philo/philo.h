/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserbest <aserbest@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 08:10:08 by aserbest          #+#    #+#             */
/*   Updated: 2025/08/15 19:13:22 by aserbest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>

# define MAX_INT 2147483647

typedef pthread_mutex_t	t_mutex;
typedef struct s_data
{
	long long	start_time;
	int			philo_num;
	int			fork_num;
	int			time_to_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			control_flag;
	int			must_eat;
	int			simulation_start;
	t_mutex		simulation_control;
	t_mutex		print_mutex;
	t_mutex		control_mutex;
	t_mutex		meal_mutex;
	t_mutex		*forks;
	pthread_t	observer_thread;
}	t_data;

typedef struct s_philo
{
	long long	last_meal_time;
	long long	think_time;
	pthread_t	thread_id;
	t_mutex		*fork_left;
	t_mutex		*fork_right;
	t_data		*data;
	int			philo_id;
	int			eat_count;
}	t_philo;

long long	get_time(void);
long long	find_think_time(t_data *data);
long		ft_atol(const char *str);
void		ft_usleep(long long time_in_ms, t_data *data);
void		print_action(t_philo *philo, char *message);
void		*observer(void *arg);
void		routine(void *arg);
void		special_situation(t_philo *philo);
void		take_the_forks(t_philo *philo);
void		update_meal_info(t_philo *philo);
void		release_the_forks(t_philo *philo);
void		init_philos(t_data *data, t_philo *philos);
void		init_data(int argc, char **argv, t_data *data);
void		cleanup_resources(t_data *data, t_philo **philos, int flag);
int			check_arguments(int argc, char **argv);
int			join_threads(t_data *data, t_philo **philos);
int			destroy_mutex(t_data *data);
int			init_mutex(t_data *data);
int			simulation_ended(t_data *data);
int			init_threads(t_data *data, t_philo *philos);
int			ft_atoi(const char *str);

#endif
