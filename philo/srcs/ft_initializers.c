/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 23:23:53 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 23:34:20 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

void	ft_philosophers_init(int argc, char **argv, \
t_philosopher **philosophers, t_table **table)
{
	int	num_philosophers;
	int	i;

	num_philosophers = ft_atoi(argv[1]);
	*philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
	i = 0;
	while (i < num_philosophers)
	{
		(*philosophers + i)->id = i + 1;
		(*philosophers + i)->ded = 0;
		if (argc == 6)
			(*philosophers + i)->meals = ft_atoi(argv[5]);
		else
			(*philosophers + i)->meals = 999999999;
		(*philosophers + i)->table = *table;
		(*philosophers + i)->eat_timestamp = get_current_timestamp();
		pthread_mutex_init(&((*philosophers + i)->ded_mutex), NULL);
		pthread_mutex_init(&((*philosophers + i)->starving_mutex), NULL);
		i++;
	}
}

t_chopstick	*ft_chopstick_init(int num_philosophers)
{
	int			i;
	t_chopstick	*chopsticks;

	chopsticks = malloc(sizeof(t_chopstick) * num_philosophers);
	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_init(&(chopsticks[i].chopstick_mutex), NULL);
		pthread_mutex_lock(&(chopsticks[i].chopstick_mutex));
		chopsticks[i].last_philo = 0;
		pthread_mutex_unlock(&(chopsticks[i].chopstick_mutex));
		i++;
	}
	return (chopsticks);
}

t_table	*ft_table_init(t_table **table, t_chopstick *chopstick, \
char **argv, int num_philosophers)
{
	(*table) = malloc(sizeof(t_table) * 1);
	(*table)->num_philos = num_philosophers;
	(*table)->chopsticks = chopstick;
	(*table)->time_to_die = ft_atoi(argv[2]);
	(*table)->time_to_eat = ft_atoi(argv[3]);
	(*table)->time_to_sleep = ft_atoi(argv[4]);
	(*table)->start_time = 0;
	pthread_mutex_init(&((*table)->eat_mutex), NULL);
	pthread_mutex_init(&((*table)->time_mutex), NULL);
	pthread_mutex_init(&((*table)->print_mutex), NULL);
	return (*table);
}

void	ft_init(t_philosopher **philosophers, \
int argc, char **argv, int num_philosophers)
{
	t_table		*table;
	t_chopstick	*chopsticks;

	table = NULL;
	chopsticks = ft_chopstick_init(num_philosophers);
	table = ft_table_init(&table, chopsticks, argv, num_philosophers);
	ft_philosophers_init(argc, argv, philosophers, &table);
}
