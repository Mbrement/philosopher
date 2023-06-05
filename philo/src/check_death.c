/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:34:02 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/05 15:40:28 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check(t_data *data);

static void	ft_kill(t_data *data, size_t i);

void	check_death(t_data *data)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->all_philo[i].lock);
			if (get_time() > data->time_to_die + data->all_philo[i].last_eat \
				&& data->all_philo[i].nb_of_eat != data->must_eat)
			{
				pthread_mutex_lock(&data->lock);
				if (data->alive == 1)
				{
					pthread_mutex_unlock(&data->lock);
					ft_print(5, &data->all_philo[i]);
					pthread_mutex_lock(&data->lock);
				}
				return (ft_kill(data, i));
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

static void	ft_kill(t_data *data, size_t i)
{
	data->alive = 0;
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_unlock(&data->all_philo[i].lock);
}
