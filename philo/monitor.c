/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:30:14 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/13 20:45:00 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printf_status(t_philo *philo, char *status)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->print_lock);
	timestamp = get_time_in_ms() - philo->start_time;
	if (!*(philo->dead))
		printf("%zu %d %s\n", timestamp, philo->ph_id, status);
	pthread_mutex_unlock(philo->print_lock);
}

int	philosophers_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_time_lock);
	if (get_time_in_ms() - philo->last_meal_time >= time_to_die)
	{
		pthread_mutex_unlock(philo->meal_time_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_time_lock);
	return (0);
}

int	if_philosophers_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].number_of_philosophers)
	{
		if (philosophers_dead(&philo[i], philo[i].time_to_die))
		{
			print_action(&philo[i], "died");
			pthread_mutex_lock(philo[0].dead_lock);
			*philo[0].dead = 1;
			pthread_mutex_unlock(philo[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	if_all_ate(t_philo *philo)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 0;
	if (philo[0].num_times_to_eat == -1)
		return (0);
	while (i < philo[0].number_of_philosophers)
	{
		pthread_mutex_lock(philo[i].meal_time_lock);
		if (philo[i].meals_eaten >= philo[i].num_times_to_eat)
			all_ate++;
		pthread_mutex_unlock(philo[i].meal_time_lock);
		i++;
	}
	if (all_ate == philo[0].number_of_philosophers)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo[0].dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

void *monitor(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while (1)
    {
        if (if_philosophers_dead(philo) == 1)
            break;
        if (if_all_ate(philo) == 1)
            break;
        usleep(1000);
    }
    return (arg);
}

