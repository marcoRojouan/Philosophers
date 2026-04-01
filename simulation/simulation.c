/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:17:31 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/01 16:58:55 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void *check_death(void *arg)
{
	t_table	*table;
	int		i;
	
	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->number_of_philo)
		{
			pthread_mutex_lock(&table->philos[i].last_mutex);
			if (get_ms_time() - table->philos[i].last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&table->stop_mutex);
				table->stop = 1;
				pthread_mutex_unlock(&table->stop_mutex);
				pthread_mutex_lock(&table->write_mutex);
				printf("%ldms : philo %d died\n",
					get_ms_time() - table->start, table->philos[i].id);
				pthread_mutex_unlock(&table->write_mutex);
				pthread_mutex_unlock(&table->philos[i].last_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->philos[i].last_mutex);
			i++;	
		}
		usleep(500);
	}
}

static void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{	
		if (check_if_stop(philo))
			break;
		if (philo->table->number_of_philo == 1)
		{
			pthread_mutex_lock(philo->forks[0]);
			print_msg(philo, "has taken a fork");
			smart_sleep(philo->table->time_to_die, philo);
			pthread_mutex_unlock(philo->forks[0]);
			return (NULL);
		}
		eating_routine(philo);
		print_msg(philo, "is sleeping");
		smart_sleep(philo->table->time_to_sleep, philo);
		print_msg(philo, "is thinking");
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