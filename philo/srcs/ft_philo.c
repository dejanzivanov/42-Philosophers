/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 22:17:18 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 23:21:45 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_philo_life(t_philosopher *philosopher, int *ded_read, int *arr)
{
	pthread_mutex_lock(&(philosopher->table-> \
	chopsticks[arr[0]].chopstick_mutex));
	pthread_mutex_lock(&(philosopher->table-> \
	chopsticks[arr[1]].chopstick_mutex));
	pthread_mutex_lock(&(philosopher->table->print_mutex));
	printf("%07i Philosopher %i has taken a fork.\n", \
	calculate_timedifference (philosopher), philosopher->id);
	pthread_mutex_unlock(&(philosopher->table->print_mutex));
	eat(philosopher);
	philosopher->table->chopsticks[arr[0]].last_philo = philosopher->id;
	philosopher->table->chopsticks[arr[1]].last_philo = philosopher->id;
	ft_philo_life_helper(philosopher, ded_read, arr);
}

void	ft_philo_life_helper(t_philosopher *philosopher, \
int *ded_read, int *arr)
{
	pthread_mutex_unlock(&(philosopher->table-> \
	chopsticks[arr[1]].chopstick_mutex));
	pthread_mutex_unlock(&(philosopher->table-> \
	chopsticks[arr[0]].chopstick_mutex));
	sleepy(philosopher);
	pthread_mutex_lock(&(philosopher->ded_mutex));
	*ded_read = philosopher->ded;
	pthread_mutex_unlock(&(philosopher->ded_mutex));
	if (ded_read == 0)
	{
		pthread_mutex_lock(&(philosopher->table->print_mutex));
		printf("%07i Philosopher %d is thinking.\n", \
		calculate_timedifference (philosopher), philosopher->id);
		pthread_mutex_unlock(&(philosopher->table->print_mutex));
	}
}

void	ft_philo_forks(t_philosopher *philosopher, int *ded_read, int *arr)
{
	pthread_mutex_lock(&(philosopher->table-> \
	chopsticks[arr[0]].chopstick_mutex));
	arr[2] = philosopher->table->chopsticks[arr[0]].last_philo;
	pthread_mutex_unlock(&(philosopher->table-> \
	chopsticks[arr[0]].chopstick_mutex));
	pthread_mutex_lock(&(philosopher->table-> \
	chopsticks[arr[1]].chopstick_mutex));
	arr[3] = philosopher->table->chopsticks[arr[1]].last_philo;
	pthread_mutex_unlock(&(philosopher->table-> \
	chopsticks[arr[1]].chopstick_mutex));
	pthread_mutex_lock(&(philosopher->ded_mutex));
	*ded_read = philosopher->ded;
	pthread_mutex_unlock(&(philosopher->ded_mutex));
}

void	ft_last_philo_fork(t_philosopher *philosopher, int *arr)
{
	if ((philosopher->id - 1) < \
	((int)((philosopher->id) % (philosopher->table->num_philos))))
	{
		arr[0] = philosopher->id - 1;
		arr[1] = (int)((philosopher->id) % (philosopher->table->num_philos));
	}
	else
	{
		arr[0] = (int)((philosopher->id) % (philosopher->table->num_philos));
		arr[1] = philosopher->id - 1;
	}
}
