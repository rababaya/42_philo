/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:31:15 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/02 15:05:47 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_table
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		number_of_philosophers;
}	t_table;

typedef struct s_philo
{
	t_mutex	*left;
	t_mutex	*right;
	int		number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		count_of_eat; //tmp
}	t_philo;


int	ft_atoi(const char *str);
int	validation(int argcount, char **argvector, t_table *table);
void	*philo(void * data);

#endif
