/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:40:56 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/31 18:22:53 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_thread_helper(t_philosopher *philosophers)
{
	int	j;

	j = 0;
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
}

/*
**	arr[0] - i - done
**	arr[1] - t_since_last_meal - done
**	arr[2] - meals_all - done
**	arr[3] - number_of_total_elements
**
*/

void	*destroyer(void *arg)
{
	t_philosopher	*philosophers;
	int				arr[3];

	arr[0] = 0;
	arr[2] = 99999999;
	philosophers = (t_philosopher *)arg;
	while (1 && arr[2] != 0)
	{
		arr[0] = 0;
		arr[2] = 0;
		while (arr[0] < philosophers->table->num_philos)
		{
			ft_feed_philo(philosophers, arr);
			if (arr[1] >= philosophers->table->time_to_die)
			{
				ft_philo_dying(philosophers, arr);
				return ((void *) 1);
			}
		arr[0]++;
		}
	}
	ft_print_mutex(philosophers, "All philosphers had all of their meals\n");
	ft_thread_helper(philosophers);
	return ((void *)(2));
}

/*
** arr[0] - left
** arr[1] - right
** arr[2] - last_left
** arr[3] - last_right
** arr[4] - total_number_of_elements
*/

void	*routine(void *philo_args)
{
	t_philosopher	*philosopher;
	int				arr[4];
	int				ded_read;

	philosopher = (t_philosopher *)philo_args;
	arr[0] = 0;
	ded_read = 0;
	ft_last_philo_fork(philosopher, arr);
	pthread_mutex_lock(&(philosopher->ded_mutex));
	ded_read = philosopher->ded;
	pthread_mutex_unlock(&(philosopher->ded_mutex));
	while (1 && ded_read == 0)
	{
		ft_philo_forks(philosopher, &ded_read, arr);
		if (arr[2] != philosopher->id && \
						arr[3] != philosopher->id && ded_read == 0)
			ft_philo_life(philosopher, &ded_read, arr);
	}
	return ((void *)(NULL));
}

void	*ft_lonely(void *philo_args)
{
	t_philosopher	*philosopher;
	int				ded_read;

	ded_read = 0;
	philosopher = (t_philosopher *)philo_args;
	pthread_mutex_lock(&(philosopher->ded_mutex));
	ded_read = philosopher->ded;
	pthread_mutex_unlock(&(philosopher->ded_mutex));
	while (1 && ded_read == 0)
	{
		pthread_mutex_lock(&(philosopher->table->print_mutex));
		printf("%07i Philosopher 1 picked a fork.\n", \
		calculate_timedifference(philosopher));
		pthread_mutex_unlock(&(philosopher->table->print_mutex));
		pthread_mutex_lock(&(philosopher->ded_mutex));
		ded_read = 1;
		pthread_mutex_unlock(&(philosopher->ded_mutex));
	}
	return (NULL);
}

void	ft_lonely_philo(t_philosopher *philosophers, \
char **argv, pthread_t *thread_killer)
{
	int	*ret;
	int	k;

	k = 0;
	ret = NULL;
	if (pthread_create(&(philosophers[0].thread), \
	NULL, &ft_lonely, &(philosophers[0])) != 0)
		printf("Failed to create thread\n");
	delay(ft_atoi(argv[2]) + 1);
	if (pthread_join(philosophers[0].thread, NULL) != 0)
		printf("Failed to close thread2\n");
	if (pthread_join(*thread_killer, (void *)ret) != 0)
		printf("Failed to close thread1\n");
	while (k < ft_atoi(argv[1]))
	{
		pthread_mutex_destroy(&(philosophers->table-> \
		chopsticks[k].chopstick_mutex));
		pthread_mutex_destroy(&(philosophers[k].ded_mutex));
		k++;
	}
	free(ret);
	free(philosophers->table->chopsticks);
	free(philosophers->table);
	free(philosophers);
}
