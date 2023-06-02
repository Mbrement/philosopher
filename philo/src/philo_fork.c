/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:32:35 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/01 19:01:40 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_fork(t_philo *philo)
{
	if (philo->index % 2)
	{
		first_fork(philo);
		second_fork(philo);
	}
	else
	{
		second_fork(philo);
		first_fork(philo);
	}
}

void	first_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->data->fork_m[philo->index - 1]);
		if (dead(philo) == 0)
			return ;
		if (philo->data->fork[philo->index - 1] == AVAILABLE)
		{
			if (dead(philo) != 0)
			{
				philo->data->fork[philo->index - 1] = TAKEN;
				ft_print(1, philo);
			}
			return ;
		}
	}
}

void	second_fork(t_philo *philo)
{
	size_t	i;

	i = philo->index;
	if (philo->index == philo->data->nb_philo)
		i = 0;
	pthread_mutex_lock(&philo->data->fork_m[i]);
	if (dead(philo) == 0)
		return ;
	if (philo->data->fork[i] == AVAILABLE)
	{
		if (dead(philo) != 0)
		{
			philo->data->fork[i] = philo->index;
			ft_print(1, philo);
		}
		return ;
	}
}
