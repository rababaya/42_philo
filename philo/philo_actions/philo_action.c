/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:06:04 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/02 15:07:52 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void * data)
{
	t_philo *philo;

	philo = data;
	while (philo->count_of_eat < 4)
	{
		pthread_mutex_lock(philo->left);
		printf("%d left fork taken\n", philo->number);
		pthread_mutex_lock(philo->right);
		printf("%d right fork taken\n", philo->number);
		printf("%d eating\n", philo->number);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		printf("%d sleeping\n", philo->number);
		usleep(philo->time_to_sleep);
		philo->count_of_eat++;
	}
	return (0);
}
