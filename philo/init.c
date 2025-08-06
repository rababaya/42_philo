/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:48:22 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/06 16:34:05 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	helper(t_table **table, t_philo **philo_data)
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
		i++;
	}
}

void	init(t_table *table)
{
	int		i;
	t_philo	*philo_data;

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
	i = 0;
	while (i < table->n)
		pthread_join(philo_data[i++].thread, NULL);
	return ;
}
