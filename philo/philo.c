/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:07:08 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/21 14:58:43 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;
	int		i;

	table.start_time = get_time_in_ms();
	if (argc != 5 && argc != 6)
		return (printf("wrong argument number\n"), 1);
	if (!validation(argc, argv, &table))
		return (1);
	init(&table);
	i = 0;
	while (i < table.n)
		pthread_join(table.philos[i++].thread, NULL);
	pthread_join(table.dead_check, NULL);
	pthread_mutex_destroy(&table.dead);
	pthread_mutex_destroy(&table.print);
	i = 0;
	while (i < table.n)
	{
		pthread_mutex_destroy(&table.philos[i].last_eat);
		pthread_mutex_destroy(&table.philos[i].count);
		pthread_mutex_destroy(&table.forks[i++]);
	}
	free(table.philos);
	free(table.forks);
	return (0);
}
