/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:35:30 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/05 15:13:38 by loup             ###   ########.fr       */
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

int check_philo(t_table *table, int i, int *all_full)
{
    pthread_mutex_lock(&table->philos[i].last_mutex);
    if (get_ms_time() - table->philos[i].last_meal > table->time_to_die)
    {
        change_stop_values(table);
        pthread_mutex_lock(&table->write_mutex);
        printf("%ldms : philo %d is dead\n",
               get_ms_time() - table->start,
               table->philos[i].id);
        pthread_mutex_unlock(&table->write_mutex);
        pthread_mutex_unlock(&table->philos[i].last_mutex);
        return (1);
    }
    if (table->number_of_meal > 0 &&
        table->philos[i].eaten_meals < table->number_of_meal)
        *all_full = 0;

    pthread_mutex_unlock(&table->philos[i].last_mutex);
    return (0);
}

void check_all_full(t_table *table, int all_full)
{
    if (table->number_of_meal > 0 && all_full)
    {
        change_stop_values(table);
        pthread_mutex_lock(&table->write_mutex);
        printf("All philosophers have eaten enough\n");
        pthread_mutex_unlock(&table->write_mutex);
    }
}

int check_philo_is_full(t_table *table, int i)
{	
	if (table->number_of_meal > 0 
		&& table->philos[i].eaten_meals < table->number_of_meal)
		return (0);
	return (1); 
}

