/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:47:36 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/03 12:03:10 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	long				last_meal;
	int					eaten_meals;
	pthread_t		 	philo;
	pthread_mutex_t		*forks[2];
	pthread_mutex_t		last_mutex;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	long	number_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	number_of_meal;
	long	start;
	long	stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	t_philo	*philos;
}	t_table;

int verif_args(char **av);
int check_if_stop(t_philo *philo);
int check_if_dead(t_table *table, int i);
int check_philo_is_full(t_table *table, int i);
int check_if_all_full(t_table *table, int are_full);
int verif_data(t_table *table, int ac);
int start_simulation(t_table *table);
int one_philo_routine(t_philo *philo);

void print_msg(t_philo *philo, char *message);
void change_stop_values(t_table *table);
void smart_sleep(long time_in_ms, t_philo *philo);
void eating_routine(t_philo *philo);

long ft_atol(const char *nptr);
long get_ms_time(void);

t_table *table_init(int ac, char **av);


#endif