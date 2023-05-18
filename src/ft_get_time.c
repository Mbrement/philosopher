/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:39:45 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/18 04:28:08 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

inline size_t	get_time(void)
{
	struct timeval	time;
	size_t			res;

	gettimeofday(&time, NULL);
	res = time.tv_sec;
	res *= 1000000;
	res += time.tv_usec;
	return (res);
}

size_t	since_start(t_philo *philo)
{
	return ((get_time() - philo->data->start_time) / 1000);
}
