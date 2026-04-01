/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:16:34 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/01 16:42:31 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static int init_forks(t_table *table)
{
	int i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_of_philo);
	if (!table->forks)
		return (0);
	while (i < table->number_of_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	return (1);
}

static t_philo *philos_init(t_table *table)
{
	int i;
	long nb;
	t_philo *philos;

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
		pthread_mutex_init(&philos[i].last_mutex, NULL);
		i++;
	}
	return (philos);
}

t_table *table_init(int ac, char **av)
{
	t_table *table;
	
	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->number_of_philo = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	table->start = 0;
	table->stop = 0;
	table->number_of_meal = -1;
	if (ac == 6)
		table->number_of_meal = ft_atol(av[5]);
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->write_mutex, NULL);
	if (!verif_data(table, ac))
		return (NULL);
	if (!init_forks(table))
		return (NULL);
	table->philos = philos_init(table);
	if (!table->philos)
		return (NULL);	
	return (table);
} 