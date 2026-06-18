/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 16:54:38 by loup              #+#    #+#             */
/*   Updated: 2026/04/05 17:56:48 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	philos_clean_loop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_destroy(&table->philos[i].last_mutex);
		i++;
	}
	free(table->philos);
}

static void	table_clean_loop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
}

void	clean_all(t_table *table)
{
	if (!table)
		return ;
	if (table->philos)
		philos_clean_loop(table);
	if (table->forks)
		table_clean_loop(table);
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->write_mutex);
	free(table);
}
