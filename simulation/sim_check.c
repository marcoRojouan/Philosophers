/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:35:30 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/02 14:36:47 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int check_if_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_mutex);
	if (philo->table->stop)
	{
		pthread_mutex_unlock(&philo->table->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->stop_mutex);
	return (0);
}

int check_if_dead(t_table *table, int i)
{
	if (get_ms_time() - table->philos[i].last_meal
				 > table->time_to_die)
	{
		change_stop_values(table);
		pthread_mutex_lock(&table->write_mutex);
		printf("%ldms : philo %d is ded\n",
			get_ms_time() - table->start, table->philos[i].id);
		pthread_mutex_unlock(&table->write_mutex);
		pthread_mutex_unlock(&table->philos[i].last_mutex);
		return (1);
	}
	return (0);
}

int check_if_all_full(t_table *table, int are_full)
{
	if (table->number_of_meal > 0 && are_full)
	{
		change_stop_values(table);
		pthread_mutex_lock(&table->write_mutex);
		printf("all philos are full\n");
		pthread_mutex_unlock(&table->write_mutex);
		return (1);
	}
	return (0);
}

int check_philo_is_full(t_table *table, int i)
{	
	if (table->number_of_meal > 0 
		&& table->philos[i].eaten_meals < table->number_of_meal)
		return (0);
	return (1); 
}

