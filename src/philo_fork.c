/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:32:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/18 05:30:13 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_fork(t_philo *philo)
{
	if (philo->index % 2 == 1)
	{
		second_fork(philo);
		first_fork(philo);
	}
	else
	{
		first_fork(philo);
		second_fork(philo);
	}
}

void	first_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (dead(philo) == 0)
			return ((void)pthread_mutex_unlock(&philo->data->lock));
		if (philo->data->fork[philo->index - 1] == AVAILABLE)
		{
			if (dead(philo) != 0)
			{
				philo->data->fork[philo->index - 1] = philo->index;
				printf("%zu %zu has taken a fork\n", (get_time() - \
				philo->data->start_time) / 1000, philo->index);
			}
			pthread_mutex_unlock(&philo->data->lock);
			return ;
		}
		else
			pthread_mutex_unlock(&philo->data->lock);
	}
}

void	second_fork(t_philo *philo)
{
	size_t	i;

	i = philo->index;
	if (philo->index == philo->data->nb_philo)
		i = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (dead(philo) == 0)
			return ((void)pthread_mutex_unlock(&philo->data->lock));
		if (philo->data->fork[i] == AVAILABLE)
		{
			if (dead(philo) != 0)
			{
				philo->data->fork[i] = philo->index;
				printf("%zu %zu has taken a fork\n", (get_time() - \
					philo->data->start_time) / 1000, philo->index);
			}
			return ((void)pthread_mutex_unlock(&philo->data->lock));
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
}
