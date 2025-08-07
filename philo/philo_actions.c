/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/07 18:44:30 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *data)
{
	int	i;
	t_table		*table;
	long long	current_time;

	table = data;
	i= 0;
	while (1)
	{
		while (i < table->n)
		{
			current_time = get_time_in_ms();
			if (current_time - table->philos->last_eat_time >= table->time_to_die)
			{
				table->smbd_died = 1;
				print(&(table->philos[i]), "is died", table->start_time);
				return (NULL);
			}
		}
	}
	return (NULL);
}

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 1)
		usleep(20);
	while (1)
	{
		if(philo->table->smbd_died == 1)
			break ;
		pthread_mutex_lock(philo->left);
		print(philo, "has taken a fork", philo->start_time);
		pthread_mutex_lock(philo->right);
		print(philo, "has taken a fork", philo->start_time);
		print(philo, "is eating", philo->start_time);
		usleep(philo->time_to_eat);
		philo->last_eat_time = get_time_in_ms();
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		print(philo, "is sleeping", philo->start_time);
		usleep(philo->time_to_sleep);
		print(philo, "is thinking", philo->start_time);
	}
	return (0);
}
