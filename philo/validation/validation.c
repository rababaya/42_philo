/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:30:25 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/06 16:19:21 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s1[i] == s2[i]) && i < n)
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

static size_t	ft_strlen(const char	*s)
{
	size_t	n;

	n = 0;
	while (s[n])
		++n;
	return (n);
}

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static int	is_in_int(const char *str)
{
	if ((ft_strlen(str) == 10 && ft_strncmp(str, "2147483647", 10) > 0)
		|| ft_strlen(str) > 10)
		return (0);
	return (1);
}

int	validation(int argcount, char **argvector, t_table *table)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argcount)
	{
		j = 0;
		if (argvector[i][j] == '-' || argvector[i][j] == '0')
			return (printf("Argument is negative, or 0\n"), 0);
		if (argvector[i][j] == '+')
			j++;
		while (argvector[i][j])
		{
			if (!ft_isdigit(argvector[i][j++]))
				return (printf("Arguments must be digits\n"), 0);
		}
		if (!is_in_int(argvector[i]))
			return (printf("Outside of int borders\n"), 0);
	}
	table->n = ft_atoi(argvector[1]);
	table->time_to_die = ft_atoi(argvector[2]) * 1000;
	table->time_to_eat = ft_atoi(argvector[3]) * 1000;
	table->time_to_sleep = ft_atoi(argvector[4]) * 1000;
	return (1);
}
