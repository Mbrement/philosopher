/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:34:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/15 17:53:24 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	apocalypse(t_data *data)
{
	size_t	i;

	i = -1;
		pthread_mutex_lock(&data->all_philo[i].lock);
	while (++i < data->nb_philo)
	{
		// printf("KILL THEM ALL\n");
		data->all_philo[i].alive = 0;
	}
		pthread_mutex_unlock(&data->all_philo[i].lock);
}

void	check_death(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			// printf("____\n%zu\n____\n", i);
			pthread_mutex_lock(&data->all_philo[i].lock);
			if (get_time() > data->time_to_die + data->all_philo[i].last_eat \
					|| data->all_philo[i].alive == 0)
			{
				printf("%zu : %zu died\n", (get_time() - \
					data->start_time) / 1000, data->all_philo[i].index);
				data->all_philo[i].alive = 0;
				pthread_mutex_unlock(&data->all_philo[i].lock);
				return (apocalypse(data));
			}
			pthread_mutex_unlock(&data->all_philo[i].lock);
		}
	}
}
