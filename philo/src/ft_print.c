/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:43:21 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/28 02:08:11 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

inline void	ft_print(int i, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->alive == 0)
		return ((void)pthread_mutex_unlock(&philo->data->print));
	if (i == 1)
	{
		printf("%zu %zu has taken a fork\n", (get_time() - \
				philo->data->start_time) / 1000, philo->index);
	}
	else if (i == 2)
	{
		printf("%zu %zu is eating\n", since_start(philo), philo->index);
	}
	else if (i == 3)
		printf("%zu %zu is thinking\n", since_start(philo), philo->index);
	else if (i == 4)
		printf("%zu %zu is sleeping\n", since_start(philo), philo->index);
	else
		printf("%zu %zu died\n", (get_time() - \
			philo->data->start_time) / 1000, philo->index);
	pthread_mutex_unlock(&philo->data->print);
}
