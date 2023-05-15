/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:45:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/15 17:28:23 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	second_fork(t_philo *philo);

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
	// printf ("time %zu | %zu\n", (get_time() - philo->data->start_time), philo->data->time_to_die);
	if (get_time() > philo->last_eat + philo->data->time_to_die || philo->alive == 0)
	{
		pthread_mutex_lock(&philo->lock);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	return (1);
}

void	first_fork(t_philo *philo)
{
	while (1)
	{
		if (philo->index % 2 == 0)
			second_fork(philo);
		pthread_mutex_lock(&philo->data->lock);
		if (ded(philo) == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return ;
		}
		if (philo->data->fork[philo->index - 1] == AVAILABLE)
		{
			philo->data->fork[philo->index - 1] = TAKEN;
			pthread_mutex_unlock(&philo->data->lock);
			printf("%zu : %zu has taken a fork\n", (get_time() - \
					philo->data->start_time) / 1000, philo->index);
			if (philo->index % 2 == 1)
				second_fork(philo);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->data->lock);
			ft_usleep(10);
		}
	}
}

void	second_fork(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (philo->index != philo->data->nb_philo)
			i = philo->index;
		if (ded(philo) == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return ;
		}
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->fork[i] == AVAILABLE)
		{
			philo->data->fork[i] = TAKEN;
			pthread_mutex_unlock(&philo->data->lock);
			printf("%zu : %zu has taken a fork\n", (get_time() - \
					philo->data->start_time) / 1000, philo->index);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
	}
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

void	is_eating(t_philo *philo)
{
	// size_t	time;

	// time = get_time() - philo->data->start_time;
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	first_fork(philo);
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	printf("%zu : %zu is eating\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	philo->last_eat = get_time();
	ft_usleep(philo->data->time_eat);
	philo->last_eat = get_time();
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	ft_unlock(philo);
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	printf("%zu : %zu is sleeping\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	ft_usleep(philo->data->time_sleep);
	if (ded(philo) == 0)
		return (ft_unlock(philo));
	printf("%zu : %zu is thinking\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
}

