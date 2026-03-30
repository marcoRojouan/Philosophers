/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:17:31 by mrojouan          #+#    #+#             */
/*   Updated: 2026/03/30 16:30:12 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void smart_sleep(long time_in_ms)
{
    long start;

    start = get_ms_time();
    while (get_ms_time() - start < time_in_ms)
        usleep(500);
}

void print_msg(t_philo *philo, char *message)
{
	long timestamp;

	timestamp = get_ms_time() - philo->table->start;
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%ldms : philo %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->write_mutex);
}

static void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->forks[0]);
	pthread_mutex_lock(philo->forks[1]);
	print_msg(philo, "is eating");
	smart_sleep(10);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
	return (NULL);
}

int start_simulation(t_table *table)
{
	int i;

	table->start = get_ms_time();
	i = 0;
	while (i < table->number_of_philo)
	{
		table->philos[i].last_meal = table->start;
		pthread_create(
			&table->philos[i].thread, NULL, philo_routine, &table->philos[i]);
		i++;
	}
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (1);
}