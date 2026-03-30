/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 13:47:32 by mrojouan          #+#    #+#             */
/*   Updated: 2026/03/30 15:18:38 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int main(int ac, char **av)
{
	t_table *table;
	
	if (!(ac == 5 || ac == 6))
		return (1);
	if (!verif_args(av))
		return (1);
	table = table_init(ac, av);
	if (!table)
		return (1);
	if (!start_simulation(table))
		return (1);
	return (0);
}
