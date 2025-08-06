/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:07:08 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/02 16:10:00 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table table;
	t_philo	philo_data[2];
	pthread_t id[2];
	t_mutex *mutex[2];

	if (argc != 5 && argc != 6)
		return (printf("wrong argument number\n"), 1);
	if (!validation(argc, argv, &table))
		return (1);
	mutex[0] = (t_mutex *)malloc(sizeof(t_mutex));
	mutex[1] = (t_mutex *)malloc(sizeof(t_mutex));
	pthread_mutex_init(mutex[0], NULL);
	pthread_mutex_init(mutex[1], NULL);
	philo_data[0].number = 0;
	philo_data[0].time_to_eat = table.time_to_eat;
	philo_data[0].time_to_sleep = table.time_to_sleep;
	philo_data[0].count_of_eat = 0;
	philo_data[0].left = mutex[0];
	philo_data[0].right = mutex[1];
	philo_data[1].number = 1;
	philo_data[1].time_to_eat = table.time_to_eat;
	philo_data[1].time_to_sleep = table.time_to_sleep;
	philo_data[1].count_of_eat = 0;
	philo_data[1].left = mutex[0];
	philo_data[1].right = mutex[1];
	pthread_create(&id[0], NULL, philo, &philo_data[0]);
	pthread_create(&id[1], NULL, philo, &philo_data[1]);
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	return (0);
}
