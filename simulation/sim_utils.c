/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:51:52 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/06 13:42:56 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	get_ms_time(void)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return ((time_val.tv_sec * 1000) + (time_val.tv_usec / 1000));
}

void	smart_sleep(long time_in_ms, t_philo *philo)
{
	long	start;

	start = get_ms_time();
	while (get_ms_time() - start < time_in_ms)
	{
		if (check_if_stop(philo))
			break ;
		usleep(500);
	}
}

void	change_stop_values(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	print_msg(t_philo *philo, char *message)
{
	long	timestamp;

	if (check_if_stop(philo))
		return ;
	timestamp = get_ms_time() - philo->table->start;
	pthread_mutex_lock(&philo->table->write_mutex);
	printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->write_mutex);
}
