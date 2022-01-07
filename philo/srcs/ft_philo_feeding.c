/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_feeding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:29:30 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 21:35:25 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_feed_philo(t_philosopher *philosophers, int *arr)
{
	pthread_mutex_lock(&(philosophers[arr[0]].starving_mutex));
	arr[2] += philosophers[arr[0]].meals;
	pthread_mutex_unlock(&(philosophers[arr[0]].starving_mutex));
	pthread_mutex_lock(&(philosophers->table->eat_mutex));
	arr[1] = (int)(get_current_timestamp() \
	- (philosophers[arr[0]].eat_timestamp));
	pthread_mutex_unlock(&(philosophers->table->eat_mutex));
}

void	ft_philo_dying(t_philosopher *philosophers, int *arr)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&(philosophers->table->print_mutex));
	pthread_mutex_lock(&(philosophers->table->time_mutex));
	printf("%07i Philosopher %d died.\n", \
	calculate_timedifference (philosophers), philosophers[arr[0]].id);
	pthread_mutex_unlock(&(philosophers->table->time_mutex));
	while (j < philosophers->table->num_philos)
	{
		if ((philosophers[j].thread) != 0)
		{
			pthread_mutex_lock(&(philosophers[j].ded_mutex));
			philosophers[j].ded = 1;
			pthread_mutex_unlock(&(philosophers[j].ded_mutex));
		}
		j++;
	}
	pthread_mutex_unlock(&(philosophers->table->print_mutex));
}
