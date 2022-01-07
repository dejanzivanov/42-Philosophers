/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:44:58 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 20:44:58 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_chopstick
{
	pthread_mutex_t	chopstick_mutex;
	int				last_philo;
}	t_chopstick;

typedef struct s_table
{
	long long unsigned int	start_time;
	long					time_to_eat;
	long					time_to_sleep;
	long					time_to_die;
	long					num_philos;
	t_chopstick				*chopsticks;
	pthread_mutex_t			eat_mutex;
	pthread_mutex_t			time_mutex;
	pthread_mutex_t			print_mutex;

}	t_table;

typedef struct s_philosopher
{
	pthread_t				thread;
	int						id;
	long					meals;
	long long unsigned int	eat_timestamp;
	t_table					*table;
	int						ded;
	pthread_mutex_t			ded_mutex;
	pthread_mutex_t			starving_mutex;
}	t_philosopher;

long					ft_atoi(const char *str);
long long unsigned int	get_current_timestamp(void);
void					delay(int miliseconds);
int						calculate_timedifference(t_philosopher *philosopher);
void					eat(t_philosopher *philosopher);
void					sleepy(t_philosopher *philosopher);
int						argc_checker(int argc);
int						argv_checker(char **argv);
int						initial_checker(int argc, char **argv);
void					ft_feed_philo(t_philosopher *philosophers, int *arr);
void					ft_philo_dying(t_philosopher *philosophers, int *arr);
void					ft_thread_helper(t_philosopher *philosophers);
void					ft_print_mutex(t_philosopher *philosophers, char *str);
void					ft_philo_life(t_philosopher *philosopher, \
int *ded_read, int *arr);
void					ft_philo_life_helper(t_philosopher *philosopher, \
int *ded_read, int *arr);
void					ft_philo_forks(t_philosopher *philosopher, \
int *ded_read, int *arr);
void					ft_last_philo_fork(t_philosopher *philosopher, \
int *arr);
void					ft_philosophers_init(int argc, char **argv, \
t_philosopher **philosophers, t_table **table);
t_chopstick				*ft_chopstick_init(int num_philosophers);
t_table					*ft_table_init(t_table **table, t_chopstick *chopstick, \
char **argv, int num_philosophers);
void					ft_init(t_philosopher **philosophers, int argc, \
char **argv, int num_philosophers);
void					*destroyer(void *arg);
void					*routine(void *philo_args);
void					*ft_lonely(void *philo_args);
void					ft_lonely_philo(t_philosopher *philosophers, \
char **argv, pthread_t *thread_killer);
void					ft_create_threads(int i, int num_philo, \
t_philosopher *philosophers);
int						ft_odd_or_even(int num_philosophers);
void					ft_free_resources(t_philosopher *philosophers, \
int num_philosophers);

#endif