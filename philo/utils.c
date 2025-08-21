/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:21:02 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/21 18:08:45 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print(t_philo *philo, char *text, long long start)
{
	long long	current;

	current = get_time_in_ms();
	pthread_mutex_lock(&(philo->table->dead));
	if (philo->table->smbd_died == 1)
		return (pthread_mutex_unlock(&(philo->table->dead)), 0);
	pthread_mutex_unlock(&(philo->table->dead));
	pthread_mutex_lock(&(philo->table->print));
	pthread_mutex_lock(&(philo->table->dead));
	if (philo->table->smbd_died == 1)
		return (pthread_mutex_unlock(&(philo->table->dead)),
			pthread_mutex_unlock(&(philo->table->print)), 0);
	pthread_mutex_unlock(&(philo->table->dead));
	printf("%lld %d %s\n", current - start, philo->id, text);
	pthread_mutex_unlock(&(philo->table->print));
	return (1);
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	start;

	start = get_time_in_ms();
	while (1)
	{
		pthread_mutex_lock(&philo->table->dead);
		if (philo->table->smbd_died == 1)
		{
			pthread_mutex_unlock(&philo->table->dead);
			return ;
		}
		pthread_mutex_unlock(&philo->table->dead);
		if (get_time_in_ms() - start >= time)
			return ;
		usleep(75);
	}
}
