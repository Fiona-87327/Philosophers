/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:10:50 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/11 19:20:05 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->ph_id % 2 == 0)
		ft_usleep(100);
	while (!dead_check(philo))
	{
		eat_action(philo);
		sleep_action(philo);
		think_action(philo);
	}
	return (arg);
}

int	thread_create(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	monitor_thread;
	int			i;

	if (pthread_create(&monitor_thread, NULL, &monitor, program->philos) != 0)
		dstroy_all("Thread creation failed", program, forks);
	i = 0;
	while (i < program->philos[0].number_of_philosophers)
	{
		if (pthread_create(&program->philos[i].thread_id, NULL, &philo_thread,
				&program->philos[i]) != 0)
			return (dstroy_all("Thread creation failed", program, forks), 1);
		i++;
	}
	i = 0;
	if (pthread_join(monitor_thread, NULL) != 0)
		dstroy_all("Thread join failed", program, forks);
	while (i < program->philos[0].number_of_philosophers)
	{
		if (pthread_join(program->philos[i].thread_id, NULL) != 0)
			return (dstroy_all("Thread join failed", program, forks), 1);
		i++;
	}
	return (0);
}
