/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:21:34 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/21 18:07:10 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead_check(t_table *table)
{
	int			i;
	long long	current = 0;

	i = -1;
	while (++i < table->n)
	{
		current = get_time_in_ms();
		pthread_mutex_lock(&(table->philos[i].last_eat));
		if (current - table->philos[i].last_eat_time > table->time_to_die)
		{
			print(&(table->philos[i]), "died", table->start_time);
			pthread_mutex_lock(&(table->dead));
			table->smbd_died = 1;
			pthread_mutex_unlock(&(table->dead));
			pthread_mutex_unlock(&(table->philos[i].last_eat));
			return (0);
		}
		pthread_mutex_unlock(&(table->philos[i].last_eat));
	}
	return (1);
}

static int	check_count(t_table *table)
{
	int	i;
	int	all;

	all = 0;
	i = -1;
	while (++i < table->n)
	{
		pthread_mutex_lock(&(table->philos[i].count));
		if (table->philos[i].count_now >= table->eat_count)
			all++;
		pthread_mutex_unlock(&(table->philos[i].count));
	}
	if (all == table->n)
	{
		pthread_mutex_lock(&(table->print));
		printf("Everyone ate required times!\n");
		return (1);
	}
	else
		return (0);
}

void	*is_dead(void *data)
{
	int			i;
	t_table		*table;

	table = data;
	while (1)
	{
		if (table->eat_count && check_count(table))
		{
			pthread_mutex_lock(&(table->dead));
			table->smbd_died = 1;
			pthread_mutex_unlock(&(table->dead));
			return (pthread_mutex_unlock(&(table->print)), NULL);
		}
		i = -1;
		if (!dead_check(table))
			return (NULL);
		usleep(75);
	}
	return (NULL);
}
