/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:31:15 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/20 17:23:22 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			count_of_eat;
	int			count_now;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long long	last_eat_time;
	long long	start_time;
	t_mutex		*left;
	t_mutex		*right;
	t_mutex		last_eat;
	t_mutex		count;
	pthread_t	thread;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			smbd_died;
	int			n;
	int			eat_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long long	start_time;
	t_mutex		print;
	t_mutex		dead;
	t_mutex		*forks;
	pthread_t	dead_check;
	t_philo		*philos;
}	t_table;

int			ft_atoi(const char *str);
int			validation(int argcount, char **argvector, t_table *table);
void		init(t_table *table);
void		*philo(void *data);
void		*is_dead(void *data);
int			print(t_philo *philo, char *text, long long start);
long long	get_time_in_ms(void);
void		ft_usleep(long long time, t_philo *philo);

#endif
