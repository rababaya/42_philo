/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/10 17:09:43 by rababaya         ###   ########.fr       */
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
	}
	return (NULL);
}

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 1)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(philo->left);
		if (!print(philo, "has taken a fork", philo->start_time))
			return (pthread_mutex_unlock(philo->left), NULL);
		pthread_mutex_lock(philo->right);
		if (!print(philo, "has taken a fork", philo->start_time))
			return (pthread_mutex_unlock(philo->left),
				pthread_mutex_unlock(philo->right), NULL);
		if (!print(philo, "is eating", philo->start_time))
			return (pthread_mutex_unlock(philo->left),
				pthread_mutex_unlock(philo->right), NULL);
		pthread_mutex_lock(&(philo->last_eat));
		philo->last_eat_time = get_time_in_ms();
		pthread_mutex_unlock(&(philo->last_eat));
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		if (!print(philo, "is sleeping", philo->start_time))
			return (NULL);
		usleep(philo->time_to_sleep);
		if (!print(philo, "is thinking", philo->start_time))
			return (NULL);
	}
	return (NULL);
}
