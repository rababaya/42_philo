/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/06 16:18:22 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	while (1)
	{
		pthread_mutex_lock(philo->left);
		printf("%d left fork taken\n", philo->id);
		pthread_mutex_lock(philo->right);
		printf("%d right fork taken\n", philo->id);
		printf("%d eating\n", philo->id);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%d sleeping\n", philo->id);
		usleep(philo->time_to_sleep);
	}
	return (0);
}
