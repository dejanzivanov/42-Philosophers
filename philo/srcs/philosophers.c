/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 21:06:13 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 21:06:13 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	main(int argc, char **argv)
{
	int				i;
	t_philosopher	*philosophers;
	pthread_t		thread_killer;

	if (initial_checker(argc, argv) == -1 || argc < 2)
		return (-1);
	philosophers = NULL;
	ft_init(&philosophers, argc, argv, ft_atoi(argv[1]));
	philosophers->table->start_time = get_current_timestamp();
	pthread_create(&thread_killer, NULL, &destroyer, philosophers);
	if (ft_atoi(argv[1]) == 1)
		ft_lonely_philo(philosophers, argv, &(thread_killer));
	else
	{
		i = ft_odd_or_even(ft_atoi(argv[1]));
		ft_create_threads(i, ft_atoi(argv[1]), philosophers);
		i = !i;
		ft_create_threads(i, ft_atoi(argv[1]), philosophers);
		if (pthread_join(thread_killer, NULL) != 0)
			printf("Failed to close thread\n");
		ft_free_resources(philosophers, ft_atoi(argv[1]));
	}
	return (0);
}
