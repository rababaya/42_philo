/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/21 16:13:58 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (!print(philo, "has taken a fork", philo->start_time))
		return (pthread_mutex_unlock(philo->left), 0);
	if (philo->table->n == 1)
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
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&(philo->count));
	if (philo->table->eat_count != 0)
		philo->count_now++;
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
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&(philo->count));
	if (philo->table->eat_count != 0)
		philo->count_now++;
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
		ft_usleep(philo->time_to_sleep, philo);
		if (!print(philo, "is thinking", philo->start_time))
			return (NULL);
	}
	return (NULL);
}
