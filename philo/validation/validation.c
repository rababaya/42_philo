/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <rababaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:30:25 by rababaya          #+#    #+#             */
/*   Updated: 2025/08/21 14:49:59 by rababaya         ###   ########.fr       */
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

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static int	is_in_int(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	if ((len == 10 && ft_strncmp(str, "2147483647", 10) > 0) || len > 10)
		return (0);
	return (1);
}

static int	check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '0')
			return (printf("Argument is negative, or 0\n"), 0);
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j++]))
				return (printf("Arguments must be digits\n"), 0);
		}
		if (!is_in_int(argv[i]))
			return (printf("Outside of int borders\n"), 0);
	}
	return (1);
}

int	validation(int argcount, char **argvector, t_table *table)
{
	if (!check(argcount, argvector))
		return (0);
	table->n = ft_atoi(argvector[1]);
	table->time_to_die = ft_atoi(argvector[2]);
	table->time_to_eat = ft_atoi(argvector[3]);
	table->time_to_sleep = ft_atoi(argvector[4]);
	table->eat_count = 0;
	if (argcount == 6)
		table->eat_count = ft_atoi(argvector[5]);
	table->smbd_died = 0;
	return (1);
}
