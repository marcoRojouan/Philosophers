/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:16:34 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/05 17:56:51 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (!table->forks)
		return (0);
	while (i < table->number_of_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static t_philo	*philos_init(t_table *table)
{
	int		i;
	long	nb;
	t_philo	*philos;

	nb = table->number_of_philo;
	philos = malloc(sizeof(t_philo) * nb);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].eaten_meals = 0;
		philos[i].last_meal = 0;
		philos[i].forks[0] = &table->forks[i];
		philos[i].forks[1] = &table->forks[(i + 1) % nb];
		if (pthread_mutex_init(&philos[i].last_mutex, NULL) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}

static int	table_init(t_table *table, int ac, char **av)
{
	table->number_of_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->start = 0;
	table->stop = 0;
	table->number_of_meal = -1;
	if (ac == 6)
		table->number_of_meal = ft_atol(av[5]);
	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->write_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_data(t_table *table, int ac, char **av)
{
	if (!table_init(table, ac, av))
		return (0);
	if (!verif_data(table, ac))
		return (0);
	if (!init_forks(table))
		return (0);
	table->philos = philos_init(table);
	if (!table->philos)
		return (0);
	return (1);
}
