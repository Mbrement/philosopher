/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:45:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/05 17:37:23 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <pthread.h>
#include <stddef.h>

void	ft_unlock(t_philo *philo);

inline int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->data->lock);
	if (i == 0)
		philo->data->alive = 0;
	if (philo->data->alive == 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (get_time() > philo->last_eat + philo->data->time_to_die \
		|| philo->data->alive == 0)
	{
		if (philo->data->alive == 1)
			ft_print(10, philo);
		philo->data->alive = 0;
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (1);
}

void	ft_unlock(t_philo *philo)
{
	int	i;

	i = philo->index;
	if (philo->index == philo->data->nb_philo)
		i = 0;
	philo->data->fork[philo->index - 1] = AVAILABLE;
	pthread_mutex_unlock(&philo->data->fork_m[philo->index - 1]);
	philo->data->fork[i] = AVAILABLE;
	pthread_mutex_unlock(&philo->data->fork_m[i]);
}

inline int	ft_musteat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->nb_of_eat++;
	pthread_mutex_unlock(&philo->lock);
	if (philo->nb_of_eat == philo->data->must_eat)
	{
		return (1);
	}
	return (0);
}

void	is_eating(t_philo *philo)
{
	if (dead(philo) == 0)
		return ;
	philo_fork(philo);
	if (dead(philo) == 0)
		return (ft_unlock(philo));
	ft_print(2, philo);
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->lock);
	wft_usleep(philo, philo->data->time_eat);
	ft_unlock(philo);
	if (dead(philo) == 0)
		return ;
	if (ft_musteat(philo) == 1)
		return ;
	if (dead(philo) == 0)
		return ;
	ft_print(4, philo);
	wft_usleep(philo, philo->data->time_sleep);
	if (dead(philo) == 0)
		return ;
	ft_print(3, philo);
}
