/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread_gen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 00:08:57 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/31 18:22:11 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	ft_odd_or_even(int num_philosophers)
{
	if ((num_philosophers % 2) == 0)
		return (1);
	else
		return (0);
}

void	ft_create_threads(int i, int num_philo, t_philosopher *philosophers)
{
	while (i < num_philo)
	{
		if (pthread_create(&(philosophers[i].thread), NULL, \
		&routine, &(philosophers[i])) != 0)
			printf("Failed to create thread\n");
		i = i + 2;
	}
	delay(5);
}

void	ft_free_resources(t_philosopher *philosophers, int num_philosophers)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (j < num_philosophers)
	{
		if (pthread_join((philosophers[j].thread), NULL) != 0)
			printf("Failed to create thread\n");
		j++;
	}
	while (k < num_philosophers)
	{
		pthread_mutex_destroy(&(philosophers->table-> \
		chopsticks[k].chopstick_mutex));
		pthread_mutex_destroy(&(philosophers[k].ded_mutex));
		k++;
	}
	free(philosophers->table->chopsticks);
	free(philosophers->table);
	free(philosophers);
}
