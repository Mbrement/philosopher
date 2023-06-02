/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:42:49 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/01 20:24:02 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

inline void	ft_usleep(size_t time)
{
	size_t	curr_time;
	size_t	end_time;
	size_t	wait_time;

	curr_time = get_time();
	end_time = curr_time + time - 1;
	while (curr_time < end_time)
	{
		curr_time = get_time();
		wait_time = (end_time - curr_time) / 2;
		if (wait_time > time)
			break ;
		usleep((unsigned int)wait_time);
	}
}

void	wft_usleep(t_philo *philo, size_t t)
{
	size_t	i;

	i = philo->last_eat + philo->data->time_to_die;
	if (philo->last_eat + t > i)
	{
		ft_usleep(i - philo->last_eat + t);
		pthread_mutex_lock(&philo->data->lock);
		printf("%zu %zu died", since_start(philo), philo->index);
		philo->data->alive = 0;
		pthread_mutex_unlock(&philo->data->lock);
	}
	else
		ft_usleep(t);
}
