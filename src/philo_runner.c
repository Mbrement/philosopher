/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:45:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/16 14:14:45 by mbrement         ###   ########lyon.fr   */
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

int	ded(t_philo *philo)
{
	if (philo->nb_of_eat == philo->data->must_eat)
		return (2);
	if (get_time() > philo->last_eat + philo->data->time_to_die \
		|| philo->alive == 0)
	{
		pthread_mutex_lock(&philo->lock);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
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

int	ft_musteat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->nb_of_eat++;
	if (philo->nb_of_eat == philo->data->must_eat)
		return (pthread_mutex_unlock(&philo->lock), 1);
	pthread_mutex_unlock(&philo->lock);
	return (0);
}

void	is_eating(t_philo *philo)
{
	if (ded(philo) == 0)
		return ;
	first_fork(philo);
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	printf("%zu %zu is eating\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	philo->last_eat = get_time();
	ft_usleep(philo->data->time_eat);
	philo->last_eat = get_time();
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	ft_unlock(philo);
	if (ft_musteat(philo) == 1)
		return ;
	if (ded(philo) == 0)
		return ;
	printf("%zu %zu is sleeping\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	ft_usleep(philo->data->time_sleep);
	if (ded(philo) == 0)
		return ;
	printf("%zu %zu is thinking\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
}
