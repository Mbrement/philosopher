/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:32:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/16 17:25:32 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static inline int	first_fork2(t_philo *philo, int i)
{
	philo->data->fork[philo->index - 1] = TAKEN;
	pthread_mutex_unlock(&philo->data->lock);
	printf("%zu %zu has taken a fork\n", (get_time() - \
	philo->data->start_time) / 1000, philo->index);
	i += 2;
	if (philo->index % 2 == 1)
		i += second_fork(philo);
	return (i);
}

void	first_fork(t_philo *philo)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo->index % 2 == 0)
			i = second_fork(philo);
		if (ded(philo) == 0)
			break ;
		pthread_mutex_lock(&philo->data->lock);
		if (ded(philo) == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return ;
		}
		if (philo->data->fork[philo->index - 1] == AVAILABLE)
		{
			i = first_fork2(philo, i);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->data->lock);
			ft_usleep(10);
		}
	}
	if (i != 3)
	{
		pthread_mutex_lock(&philo->lock);
		philo->alive = 0;
		pthread_mutex_unlock(&philo->lock);
	}
}

int	second_fork(t_philo *philo)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (philo->index != philo->data->nb_philo)
		i = philo->index;
	while (1)
	{
		if (ded(philo) == 0)
		{
			pthread_mutex_unlock(&philo->data->lock);
			return (j);
		}
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->fork[i] == AVAILABLE)
		{
			philo->data->fork[i] = TAKEN;
			pthread_mutex_unlock(&philo->data->lock);
			printf("%zu %zu has taken a fork\n", (get_time() - \
					philo->data->start_time) / 1000, philo->index);
			j++;
			break ;
		}
		else
			pthread_mutex_unlock(&philo->data->lock);
	}
	return (j);
}
