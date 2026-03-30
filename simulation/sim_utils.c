/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:51:52 by mrojouan          #+#    #+#             */
/*   Updated: 2026/03/30 16:23:07 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long get_ms_time(void)
{
	struct timeval time_val;

	gettimeofday(&time_val, NULL);
	return ((time_val.tv_sec * 1000) + (time_val.tv_usec / 1000));
}