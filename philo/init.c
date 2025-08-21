/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:48:22 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/21 14:58:25 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	helper(t_table **table, t_philo **philo_data, int i)
{
	while (++i < (*table)->n)
	{
		pthread_mutex_init(&((*table)->forks[i]), NULL);
		(*philo_data)[i].id = i + 1;
		(*philo_data)[i].time_to_eat = (*table)->time_to_eat;
		(*philo_data)[i].time_to_sleep = (*table)->time_to_sleep;
		(*philo_data)[i].left = &((*table)->forks[i]);
		(*philo_data)[i].right = &((*table)->forks[(i + 1) % (*table)->n]);
		(*philo_data)[i].start_time = (*table)->start_time;
		(*philo_data)[i].last_eat_time = (*table)->start_time;
		(*philo_data)[i].table = (*table);
		pthread_mutex_init(&((*philo_data)[i]).last_eat, NULL);
		pthread_mutex_init(&((*philo_data)[i]).count, NULL);
	}
}

void	init(t_table *table)
{
	int		i;
	t_philo	*philo_data;

	pthread_mutex_init(&(table->print), NULL);
	pthread_mutex_init(&(table->dead), NULL);
	table->forks = (t_mutex *)malloc(table->n * sizeof(t_mutex));
	if (!table->forks)
		return ;
	i = -1;
	philo_data = (t_philo *)malloc(table->n * sizeof(t_philo));
	if (!philo_data)
		return ;
	i = -1;
	helper(&table, &philo_data, i);
	table->philos = philo_data;
	while (++i < table->n)
		pthread_create(&philo_data[i].thread, NULL, philo, &philo_data[i]);
	pthread_create(&(table->dead_check), NULL, is_dead, table);
	return ;
}
