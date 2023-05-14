/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_runner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:45:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/14 17:33:15 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	if (get_time() > philo->last_eat + philo->data->time_to_die)
		return (0);
	return (1);
}

void	first_fork(t_philo *philo)
{
	printf("start first fork %zu\n", philo->index);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->fork[philo->index - 1] == AVAILABLE)
		{
			if (ded(philo) == 0)
			{
				pthread_mutex_unlock(&philo->data->lock);
				return ;
			}
			philo->data->fork[philo->index - 1] = TAKEN;
			printf("%zu : %zu has taken a fork\n", (get_time() - \
					philo->data->start_time) / 1000, philo->index);
			break ;
		}
		else
			ft_usleep(10);
		pthread_mutex_unlock(&philo->data->lock);
		printf("end first fork %zu\n", philo->index);
	}
}

void	second_fork(t_philo *philo)
{
	printf("start second fork %zu\n", philo->index);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->fork[philo->index - 1] == AVAILABLE)
		{
			if (ded(philo) == 0)
			{
				pthread_mutex_unlock(&philo->data->lock);
				return ;
			}
			if (philo->index == philo->data->nb_philo)
				philo->data->fork[0] = TAKEN;
			else
			 	philo->data->fork[philo->index] = TAKEN;
			printf("%zu : %zu has taken a fork\n", (get_time() - \
					philo->data->start_time) / 1000, philo->index);
			break ;
		}
		else
			ft_usleep(10);
		pthread_mutex_unlock(&philo->data->lock);
	}
	printf("end second fork %zu\n", philo->index);
}

void	is_eating(t_philo *philo)
{
	size_t	time;

	time = get_time() - philo->data->start_time;
	if (ded(philo) == 0)
		return ;
	first_fork(philo);
	if (ded(philo) == 0)
		return ;
	second_fork(philo);
	if (ded(philo) == 0)
		return ;
	printf("%zu : %zu is eating\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	philo->last_eat = get_time() + philo->data->time_eat;
	ft_usleep(philo->data->time_eat);
	if (ded(philo) == 0)
		return ;
	printf("%zu : %zu is sleeping\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	ft_usleep(philo->data->time_sleep);
	if (ded(philo) == 0)
		return ;
	printf("%zu : %zu is thinking\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
}

