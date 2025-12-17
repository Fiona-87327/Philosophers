/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aktion.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:09:03 by jiyawang          #+#    #+#             */
/*   Updated: 2025/12/17 21:33:38 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, const char *action)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->print_lock);
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 0)
	{
		timestamp = get_time_in_ms() - philo->start_time;
		printf("%zu %d %s\n", timestamp, philo->ph_id + 1, action);
	}
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_unlock(philo->print_lock);
}

void	sleep_action(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

void	think_action(t_philo *philo)
{
	print_action(philo, "is thinking");
}

void	eat_action(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	if (philo->number_of_philosophers == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->meal_time_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(philo->meal_time_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

// void	die_action(t_philo *philo)
// {
// 	size_t	timestamp;

// 	pthread_mutex_lock(philo->dead_lock);
// 	*(philo->dead) = 1;
// 	pthread_mutex_unlock(philo->dead_lock);
// 	pthread_mutex_lock(philo->print_lock);
// 	timestamp = get_time_in_ms() - philo->start_time;
// 	printf("%zu %d died", timestamp, philo->ph_id + 1);
// 	pthread_mutex_unlock(philo->print_lock);
// }

void	die_action(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	*(philo->dead) = 1;
	pthread_mutex_unlock(philo->dead_lock);
}
