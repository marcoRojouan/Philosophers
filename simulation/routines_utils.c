/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:58:42 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/03 13:30:44 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int one_philo_routine(t_philo *philo)
{
	if (philo->table->number_of_philo == 1)
	{
		pthread_mutex_lock(philo->forks[0]);
		print_msg(philo, "has twaken a fwork");
		smart_sleep(philo->table->time_to_die, philo);
		pthread_mutex_unlock(philo->forks[0]);
		return (1);
	}
	return (0);
}

void eating_routine(t_philo *philo)
{		
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->forks[1]);
		print_msg(philo, "has twaken a fwork");
		pthread_mutex_lock(philo->forks[0]);
		print_msg(philo, "has twaken a fwork");
	}
	else
	{
		pthread_mutex_lock(philo->forks[0]);
		print_msg(philo, "has twaken a fwork");
		pthread_mutex_lock(philo->forks[1]);
		print_msg(philo, "has twaken a fwork");
	}
	print_msg(philo, "is eating");
	pthread_mutex_lock(&philo->last_mutex);
	philo->last_meal = get_ms_time();
	pthread_mutex_unlock(&philo->last_mutex);
	smart_sleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(&philo->last_mutex);
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->last_mutex);
	pthread_mutex_unlock(philo->forks[0]);
	pthread_mutex_unlock(philo->forks[1]);
}
