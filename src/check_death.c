/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:34:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/14 16:27:19 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void static	apocalypse(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->all_philo[i].alive = 0;
	}
}

void	check_death(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			// pthread_mutex_lock(&data->all_philo[i].lock);
			// printf("%zu : %zu didn't eat since %zu\n", (get_time() - \
			// 		data->start_time) / 1000, data->all_philo[i].index, (get_time() - data->all_philo[i].last_eat)/1000);
			if (get_time() > data->time_to_die + data->all_philo[i].last_eat)
			{
				printf("%zu : %zu died\n", (get_time() - \
					data->start_time) / 1000, data->all_philo[i].index);
				data->all_philo[i].alive = 0;
			}
			if (data->all_philo[i].alive == 1)
				i++;
			else
				return (apocalypse(data));
			// pthread_mutex_unlock(&data->all_philo[i].lock);
		}
	}
}
