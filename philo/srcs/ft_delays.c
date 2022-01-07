/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 23:54:42 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 23:55:08 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

long long unsigned int	get_current_timestamp(void)
{
	struct timeval			current_time;
	long long unsigned int	timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	return (timestamp);
}

void	delay(int miliseconds)
{
	long long unsigned int	starting_value;

	starting_value = get_current_timestamp();
	while (get_current_timestamp() < miliseconds + starting_value)
		;
}

int	calculate_timedifference(t_philosopher *philosopher)
{
	int	time_diff;

	time_diff = get_current_timestamp() - philosopher->table->start_time;
	return (time_diff);
}

void	eat(t_philosopher *philosopher)
{
	int	ded_read;

	pthread_mutex_lock(&(philosopher->ded_mutex));
	ded_read = philosopher->ded;
	pthread_mutex_unlock(&(philosopher->ded_mutex));
	if (ded_read == 0)
	{
		pthread_mutex_lock(&(philosopher->table->eat_mutex));
		pthread_mutex_lock(&(philosopher->table->print_mutex));
		philosopher->eat_timestamp = get_current_timestamp();
		printf("%07i Philosopher %d is eating.\n", \
		calculate_timedifference (philosopher), philosopher->id);
		pthread_mutex_unlock(&(philosopher->table->print_mutex));
		pthread_mutex_unlock(&(philosopher->table->eat_mutex));
		if (philosopher->meals > 0)
		{
			pthread_mutex_lock(&(philosopher->starving_mutex));
			philosopher->meals--;
			pthread_mutex_unlock(&(philosopher->starving_mutex));
		}
		delay(philosopher->table->time_to_eat);
	}
}

void	sleepy(t_philosopher *philosopher)
{
	int	ded_read;

	pthread_mutex_lock(&(philosopher->ded_mutex));
	ded_read = philosopher->ded;
	pthread_mutex_unlock(&(philosopher->ded_mutex));
	if (ded_read == 0)
	{
		pthread_mutex_lock(&(philosopher->table->print_mutex));
		printf("%07i Philosopher %d is sleeping.\n", \
		calculate_timedifference (philosopher), philosopher->id);
		pthread_mutex_unlock(&(philosopher->table->print_mutex));
		delay(philosopher->table->time_to_sleep);
	}
}
