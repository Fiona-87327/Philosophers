/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:52:08 by jiyawang          #+#    #+#             */
/*   Updated: 2025/11/30 18:42:35 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	tv;
	size_t			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_in_ms);
}

void	ft_usleep(size_t duration_in_ms)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < duration_in_ms)
		usleep(100);
}

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;
	int			i;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	dstroy_all(char *philo, t_program *program, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (philo)
	{
		write(2, philo, ft_strlen(philo));
		write(2, "\n", 1);
	}
	pthread_mutex_destroy(&program->print_lock);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	while (i < program->philos->number_of_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
