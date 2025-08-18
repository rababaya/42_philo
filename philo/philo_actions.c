/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/18 17:17:06 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *data)
{
	int			i;
	t_table		*table;
	long long	current;

	table = data;
	while (1)
	{
		i = -1;
		while (++i < table->n)
		{
			current = get_time_in_ms();
			pthread_mutex_lock(&(table->philos[i].last_eat));
			if (current - table->philos[i].last_eat_time >= table->time_to_die)
			{
				print(&(table->philos[i]), "is died", table->start_time);
				pthread_mutex_lock(&(table->dead));
				table->smbd_died = 1;
				pthread_mutex_unlock(&(table->dead));
				pthread_mutex_unlock(&(table->philos[i].last_eat));
				return (NULL);
			}
			pthread_mutex_unlock(&(table->philos[i].last_eat));
		}
		usleep(1000);
	}
	return (NULL);
}

void	check_count(t_table *table)
{
	int	i;
	int	all;
	int	*all_eaten;

	all_eaten = malloc(sizeof(int) * table->n);
	all = 0;
	i = -1;
	while (++i < table->n)
		all_eaten[i] = -1;
	while (all < table->n)
	{
		i = -1;
		while (++i < table->n)
		{
			pthread_mutex_lock(&(table->philos[i].count));
			if (table->philos[i].count_now == table->eat_count)
				if (all_eaten[i] != i)
				{
					all_eaten[i] = i;
					all++;
				}
			pthread_mutex_unlock(&(table->philos[i].count));
		}
		usleep(1000);
	}
	pthread_mutex_lock(&(table->dead));
	table->smbd_died = 1;
	pthread_mutex_unlock(&(table->dead));
	free(all_eaten);
}

static int	philo_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (!print(philo, "has taken a fork", philo->start_time))
		return (pthread_mutex_unlock(philo->left), 0);
	pthread_mutex_lock(philo->right);
	if (!print(philo, "has taken a fork", philo->start_time))
		return (pthread_mutex_unlock(philo->left),
			pthread_mutex_unlock(philo->right), 0);
	if (!print(philo, "is eating", philo->start_time))
		return (pthread_mutex_unlock(philo->left),
			pthread_mutex_unlock(philo->right), 0);
	pthread_mutex_lock(&(philo->last_eat));
	philo->last_eat_time = get_time_in_ms();
	pthread_mutex_unlock(&(philo->last_eat));
	usleep(philo->time_to_eat);
	pthread_mutex_lock(&(philo->count));
	if (philo->count_of_eat != 0)
		if (++philo->count_now >= philo->count_of_eat)
			return (pthread_mutex_unlock(&(philo->count)),
				pthread_mutex_unlock(philo->left),
				pthread_mutex_unlock(philo->right), 0);
	pthread_mutex_unlock(&(philo->count));
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

static int	philo_even(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	if (!print(philo, "has taken a fork", philo->start_time))
		return (pthread_mutex_unlock(philo->right), 0);
	pthread_mutex_lock(philo->left);
	if (!print(philo, "has taken a fork", philo->start_time))
		return (pthread_mutex_unlock(philo->right),
			pthread_mutex_unlock(philo->left), 0);
	if (!print(philo, "is eating", philo->start_time))
		return (pthread_mutex_unlock(philo->right),
			pthread_mutex_unlock(philo->left), 0);
	pthread_mutex_lock(&(philo->last_eat));
	philo->last_eat_time = get_time_in_ms();
	pthread_mutex_unlock(&(philo->last_eat));
	usleep(philo->time_to_eat);
	pthread_mutex_lock(&(philo->count));
	if (philo->count_of_eat != 0)
		if (++philo->count_now >= philo->count_of_eat)
			return (pthread_mutex_unlock(&(philo->count)),
				pthread_mutex_unlock(philo->left),
				pthread_mutex_unlock(philo->right), 0);
	pthread_mutex_unlock(&(philo->count));
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (1);
}

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 1)
		usleep(500);
	while (1)
	{
		if (philo->id % 2 == 1)
		{
			if (!philo_odd(philo))
				return (NULL);
		}
		else
			if (!philo_even(philo))
				return (NULL);
		if (!print(philo, "is sleeping", philo->start_time))
			return (NULL);
		usleep(philo->time_to_sleep);
		if (!print(philo, "is thinking", philo->start_time))
			return (NULL);
	}
	return (NULL);
}
