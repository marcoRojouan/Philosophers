/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 14:33:28 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/05 17:56:56 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	is_number(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-' || av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	verif_max(char *arg)
{
	long long	nbr;
	int			i;

	i = 0;
	nbr = 0;
	while (arg[i])
	{
		nbr = nbr * 10 + (arg[i] - '0');
		if (nbr > LONG_MAX)
			return (1);
		i++;
	}
	return (0);
}

static int	is_number_max(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (verif_max(av[i]))
			return (0);
		i++;
	}
	return (1);
}

int	verif_args(char **av)
{
	if (!is_number(av))
		return (0);
	if (!is_number_max(av))
		return (0);
	return (1);
}

int	verif_data(t_table *table, int ac)
{
	if (table->number_of_philo <= 0
		|| table->time_to_die <= 0
		|| table->time_to_eat <= 0
		|| table->time_to_sleep <= 0
		|| (ac == 6 && table->number_of_meal <= 0))
		return (0);
	return (1);
}
