/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:05:43 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/12 12:06:04 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_num_check(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			printf("All arguments must be positive integers.\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_input(char **argv)
{
	if (ft_atoi(argv[1]) > 2147483647 || ft_atoi(argv[1]) <= 0
		|| arg_num_check(argv[1]) == 1)
	{
		return (printf("Error: Invalid philosophers number\n"), 1);
	}
	if (ft_atoi(argv[2]) <= 0 || arg_num_check(argv[2]) == 1)
	{
		return (printf("Error: Invalid time to die\n"), 1);
	}
	if (ft_atoi(argv[3]) <= 0 || arg_num_check(argv[3]) == 1)
	{
		return (printf("Error: Invalid time to eat\n"), 1);
	}
	if (ft_atoi(argv[4]) <= 0 || arg_num_check(argv[4]) == 1)
	{
		return (printf("Error: Invalid time to sleep\n"), 1);
	}
	if (argv[5] && (ft_atoi(argv[5]) <= 0 || arg_num_check(argv[5]) == 1))
	{
		return (printf("Error: Invalid number of times must eat\n"),
			1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int 			ph_num;
	
	ph_num = ft_atoi(argv[1]);
	if (ph_num > 200)
	{
		printf("Error: Too many philosophers (max 200).\n");
		return (1);
	}

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (check_input(argv) == 1)
		return (1);
	init_program(&program, philos);
	init_forks(forks, ft_atoi(argv[1]));
	init_philo(philos, &program, forks, argv);
	if (thread_create(&program, forks) != 0)
		return (1);
	dstroy_all(NULL, &program, forks);
	return (0);
}
