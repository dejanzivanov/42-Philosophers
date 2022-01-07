/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzivanov <dzivanov@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 20:50:33 by dzivanov          #+#    #+#             */
/*   Updated: 2021/12/30 23:55:52 by dzivanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philosophers.h"

int	argc_checker(int argc)
{
	if ((argc != 5) && (argc != 6))
	{
		printf("Error: Incorrect number of arguments!\n");
		return (1);
	}
	return (0);
}

int	argv_checker(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0)
		{
			printf("Error: Incorrect arguments!\n");
			return (1);
		}
		i += 1;
	}
	return (0);
}

int	initial_checker(int argc, char **argv)
{
	if ((argv_checker(argv) == 1) || (argc_checker(argc) == 1))
		return (-1);
	else if (ft_atoi(argv[1]) < 1)
	{
		printf("Error: Incorrect number of philosophers!\n");
		return (-1);
	}
	return (0);
}

void	ft_print_mutex(t_philosopher *philosophers, char *str)
{
	pthread_mutex_lock(&(philosophers->table->print_mutex));
	printf("%s", str);
	pthread_mutex_unlock(&(philosophers->table->print_mutex));
}
