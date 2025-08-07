/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:31:15 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/07 18:40:15 by rababaya         ###   ########.fr       */
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
typedef struct s_table t_table;

typedef struct s_philo
{
	long long	last_eat_time;
	long long	start_time;
	t_mutex		*left;
	t_mutex		*right;
	pthread_t	thread;
	int			id;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			count_of_eat; //tmp
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			smbd_died;
	long long	start_time;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			n;
	t_mutex		**forks;
	pthread_t	dead_check;
	t_philo		*philos;
}	t_table;

int			ft_atoi(const char *str);
int			validation(int argcount, char **argvector, t_table *table);
void		*philo(void *data);
void		init(t_table *table);
long long	get_time_in_ms(void);
void		print(t_philo *philo, char *text, long long start);
void		*is_dead(void *data);

#endif
