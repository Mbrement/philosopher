/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:45:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/28 04:13:25 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_unlock(t_philo *philo);

inline int	is_dead(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->lock);
	if (i == 0)
		philo->alive = 0;
	if (philo->alive == 1)
	{
		pthread_mutex_unlock(&philo->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->nb_of_eat == philo->data->must_eat)
		return (pthread_mutex_unlock(&philo->lock), 2);
	if (get_time() > philo->last_eat + philo->data->time_to_die \
		|| philo->alive == 0)
	{
		philo->alive = 0;
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}

void	ft_unlock(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->index != philo->data->nb_philo)
		i = philo->index;
	pthread_mutex_lock(&philo->data->lock);
	philo->data->fork[i] = AVAILABLE;
	philo->data->fork[philo->index - 1] = AVAILABLE;
	pthread_mutex_unlock(&philo->data->lock);
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
		return ;
	ft_print(2, philo);
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->time_eat);
	ft_unlock(philo);
	if (dead(philo) == 0)
		return ;
	if (ft_musteat(philo) == 1)
		return ;
	if (dead(philo) == 0)
		return ;
	ft_print(4, philo);
	ft_usleep(philo->data->time_sleep);
	if (dead(philo) == 0)
		return ;
	ft_print(3, philo);
}
