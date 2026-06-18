/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:47:32 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/05 17:56:40 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	main(int ac, char **av)
{
	t_table	*table;

	if (!(ac == 5 || ac == 6))
		return (1);
	if (!verif_args(av))
		return (1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!init_data(table, ac, av))
	{
		clean_all(table);
		return (1);
	}
	if (!start_simulation(table))
	{
		clean_all(table);
		return (1);
	}
	clean_all(table);
	return (0);
}
