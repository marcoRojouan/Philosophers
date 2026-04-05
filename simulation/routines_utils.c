/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:58:42 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/05 17:57:00 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	one_philo_routine(t_philo *philo)
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

void	thinking_routine(t_philo *philo)
{
	long	think_time;

	print_msg(philo, "is thinking");
	think_time = philo->table->time_to_die
		- philo->table->time_to_eat
		- philo->table->time_to_sleep;
	think_time /= 2;
	if (think_time < 0)
		think_time = 0;
	if (think_time > 600)
		think_time = 600;
	if (think_time > 0)
		smart_sleep(think_time, philo);
}

static void	after_eating(t_philo *philo,
					pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(&philo->last_mutex);
	philo->last_meal = get_ms_time();
	philo->eaten_meals++;
	pthread_mutex_unlock(&philo->last_mutex);
	print_msg(philo, "is eating");
	smart_sleep(philo->table->time_to_eat, philo);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	eating_routine(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->forks[0] < philo->forks[1])
	{
		first_fork = philo->forks[0];
		second_fork = philo->forks[1];
	}
	else
	{
		first_fork = philo->forks[1];
		second_fork = philo->forks[0];
	}
	pthread_mutex_lock(first_fork);
	print_msg(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print_msg(philo, "has taken a fork");
	after_eating(philo, first_fork, second_fork);
}
