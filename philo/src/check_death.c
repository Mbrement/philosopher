/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:34:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/28 02:08:32 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <unistd.h>

static int	check(t_data *data);

static void	apocalypse(t_data *data)
{
	size_t	i;

	i = -1;
	pthread_mutex_lock(&data->print);
	data->alive = 0;
	pthread_mutex_unlock(&data->print);
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->all_philo[i].lock);
		data->all_philo[i].alive = 0;
		pthread_mutex_unlock(&data->all_philo[i].lock);
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
			pthread_mutex_lock(&data->all_philo[i].lock);
			if ((get_time() > data->time_to_die + data->all_philo[i].last_eat \
					|| data->all_philo[i].alive == 0) && \
					data->all_philo[i].nb_of_eat != data->must_eat)
			{
				ft_print(5, &data->all_philo[i]);
				data->all_philo[i].alive = 0;
				pthread_mutex_unlock(&data->all_philo[i].lock);
				apocalypse(data);
				return ;
			}
			pthread_mutex_unlock(&data->all_philo[i].lock);
		}
		if (check(data) == 1)
			return ;
	}
}

static int	check(t_data *data)
{
	size_t	i;
	size_t	check;

	i = -1;
	check = 0;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->all_philo[i].lock);
		if (data->all_philo[i].nb_of_eat == data->must_eat)
			check ++;
		else
		{
			pthread_mutex_unlock(&data->all_philo[i].lock);
			return (0);
		}
		pthread_mutex_unlock(&data->all_philo[i].lock);
	}
	if (check == data->nb_philo)
	{
		return (1);
	}
	else
		return (0);
}
