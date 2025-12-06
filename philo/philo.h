/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:38:10 by jiyawang          #+#    #+#             */
/*   Updated: 2025/12/06 19:38:09 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread_id;
	int				ph_id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				number_of_philosophers;
	int				*dead;
	int				num_times_to_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_time_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	t_philo			*philos;
}					t_program;

void				print_action(t_philo *philo, const char *action);
void				sleep_action(t_philo *philo);
void				think_action(t_philo *philo);
void				eat_action(t_philo *philo);
void				die_action(t_philo *philo);
void				input_init(t_philo *philo, char **argv);
void				init_philo(t_philo *philo, t_program *program,
						pthread_mutex_t *forks, char **argv);
void				init_forks(pthread_mutex_t *forks, int num_philosophers);
void				init_program(t_program *program, t_philo *philos);
int					arg_num_check(char *arg);
int					check_input(char **argv);
int					main(int argc, char **argv);
void				printf_status(t_philo *philo, char *status);
int					philosophers_dead(t_philo *philo, size_t time_to_die);
int					if_philosophers_dead(t_philo *philo);
int					if_all_ate(t_philo *philo);
void				*monitor(void *arg);
int					dead_check(t_philo *philo);
void				*philo_thread(void *arg);
int					thread_create(t_program *program, pthread_mutex_t *forks);
size_t				get_time_in_ms(void);
void				ft_usleep(size_t ms);
int					ft_atoi(const char *str);
void				dstroy_all(char *philo, t_program *program,
						pthread_mutex_t *forks);

#endif