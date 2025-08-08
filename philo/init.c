/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:48:22 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/08 16:40:58 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	helper(t_table **table, t_philo **philo_data)
{
	int	i;

	i = 0;
	while (i < (*table)->n)
	{
		(*table)->forks[i] = (t_mutex *)malloc(sizeof(t_mutex));
		if (!(*table)->forks[i])
			return ;
		i++;
	}
	i = 0;
	while (i < (*table)->n)
	{
		pthread_mutex_init((*table)->forks[i], NULL);
		(*philo_data)[i].id = i + 1;
		(*philo_data)[i].time_to_eat = (*table)->time_to_eat;
		(*philo_data)[i].time_to_sleep = (*table)->time_to_sleep;
		//(*philo_data)[i].count_of_eat = i;
		(*philo_data)[i].left = (*table)->forks[i];
		(*philo_data)[i].right = (*table)->forks[(i + 1) % (*table)->n];
		(*philo_data)[i].start_time = (*table)->start_time;
		(*philo_data)[i].last_eat_time = (*table)->start_time;
		(*philo_data)[i].table = (*table);
		(*philo_data)[i].last_eat = (t_mutex *)malloc(sizeof(t_mutex));
		if (!(*philo_data)[i].last_eat)
			return ;
		pthread_mutex_init((*philo_data)[i].last_eat, NULL);
		i++;
	}
}

void	init(t_table *table)
{
	int		i;
	t_philo	*philo_data;

	table->print = (t_mutex *)malloc(sizeof(t_mutex ));
	if (!table->print)
		return ;
	pthread_mutex_init(table->print, NULL);
	table->dead = (t_mutex *)malloc(sizeof(t_mutex ));
	if (!table->dead)
		return ;
	pthread_mutex_init(table->dead, NULL);
	table->forks = (t_mutex **)malloc(table->n * sizeof(t_mutex *));
	if (!table->forks)
		return ;
	philo_data = (t_philo *)malloc(table->n * sizeof(t_philo));
	if (!philo_data)
		return ;
	helper(&table, &philo_data);
	table->philos = philo_data;
	i = -1;
	while (++i < table->n)
		pthread_create(&philo_data[i].thread, NULL, philo, &philo_data[i]);
	pthread_create(&(table->dead_check), NULL, is_dead, table);
	i = 0;
	while (i < table->n)
		pthread_join(philo_data[i++].thread, NULL);
	pthread_join(table->dead_check, NULL);
	free(philo_data);
	free(table->print);
	free(table->dead);
	return ;
}
