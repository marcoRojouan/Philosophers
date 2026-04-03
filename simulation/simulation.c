/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:17:31 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/03 13:23:11 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void *check_death(void *arg)
{
	t_table	*table;
	int		i;
	int		are_full;
	
	table = (t_table *)arg;
	while (1)
	{
		are_full = 1;
		i = 0;
		while (i < table->number_of_philo)
		{
			pthread_mutex_lock(&table->philos[i].last_mutex);
			if (check_if_dead(table, i))
				return (NULL);
			if (check_philo_is_full(table, i) == 0)
				are_full = 0;
			pthread_mutex_unlock(&table->philos[i].last_mutex);
			i++;	
		}
		if (check_if_all_full(table, are_full))
			return (NULL);
		usleep(500);
	}
}

static void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{	
		if (check_if_stop(philo))
			break;
		if (one_philo_routine(philo))
			return (NULL);
		pthread_mutex_lock(&philo->last_mutex);
		if (philo->table->number_of_meal > 0
    		&& philo->eaten_meals >= philo->table->number_of_meal)
    		break;
		pthread_mutex_unlock(&philo->last_mutex);
		eating_routine(philo);
		print_msg(philo, "is sweeping");
		smart_sleep(philo->table->time_to_sleep, philo);
		print_msg(philo, "is swinking");
	}
	return (NULL);
}

int start_simulation(t_table *table)
{
	pthread_t monitor;
	int i;

	table->start = get_ms_time();
	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].last_meal = table->start;
		pthread_create(
			&table->philos[i].philo, NULL, philo_routine, &table->philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, check_death, table);
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philos[i].philo, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}