/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:17:31 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/05 17:57:10 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	*check_death(void *arg)
{
	t_table	*table;
	int		i;
	int		all_full;

	table = (t_table *)arg;
	while (1)
	{
		all_full = 1;
		i = 0;
		while (i < table->number_of_philo)
		{
			if (check_philo(table, i, &all_full))
				return (NULL);
			i++;
		}
		check_all_full(table, all_full);
		if (check_if_stop(&table->philos[0]))
			return (NULL);
		usleep(500);
	}
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep((philo->table->time_to_eat * 1000) / 2
			+ (philo->id / 2) * 1000);
	if (one_philo_routine(philo) == 1)
		return (NULL);
	while (!check_if_stop(philo))
	{
		eating_routine(philo);
		pthread_mutex_lock(&philo->last_mutex);
		if (philo->table->number_of_meal > 0
			&& philo->eaten_meals >= philo->table->number_of_meal)
		{
			pthread_mutex_unlock(&philo->last_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->last_mutex);
		print_msg(philo, "is sleeping");
		smart_sleep(philo->table->time_to_sleep, philo);
		thinking_routine(philo);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	pthread_t	monitor;
	int			i;

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
