/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:28:23 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/10 16:47:08 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	input_init(t_philo *philo, char **argv)
{
	philo->number_of_philosophers = ft_atoi(argv[1]);
	philo->time_to_die = (size_t)ft_atoi(argv[2]);
	philo->time_to_eat = (size_t)ft_atoi(argv[3]);
	philo->time_to_sleep = (size_t)ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philo(t_philo *philo, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].ph_id = i;
		philo[i].meals_eaten = 0;
		philo[i].eating = 0;
		philo[i].start_time = get_time_in_ms();
		philo[i].last_meal_time = get_time_in_ms();
		philo[i].print_lock = &program->print_lock;
		philo[i].dead_lock = &program->dead_lock;
		philo[i].meal_time_lock = &program->meal_lock;
		philo[i].dead = &program->dead_flag;
		philo[i].left_fork = &forks[i];
		input_init(&philo[i], argv);
		if (i == 0)
			philo[i].right_fork = &forks[ft_atoi(argv[1]) - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_program(t_program *program, t_philo *philos)
{
	program->dead_flag = 0;
	program->philos = philos;
	pthread_mutex_init(&program->print_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
