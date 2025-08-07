/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/07 15:53:51 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 1)
		usleep(20);
	while (1)
	{
		pthread_mutex_lock(philo->left);
		print(philo, "has taken a fork", philo->start_time);
		pthread_mutex_lock(philo->right);
		print(philo, "has taken a fork", philo->start_time);
		print(philo, "is eating", philo->start_time);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		print(philo, "is sleeping", philo->start_time);
		usleep(philo->time_to_sleep);
		print(philo, "is thinking", philo->start_time);
	}
	return (0);
}
