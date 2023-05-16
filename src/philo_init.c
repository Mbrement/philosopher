/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/16 11:55:15 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_routine(void *org)
{
	t_philo	*philo;

	philo = org;
	usleep(philo->index * 10);
	while (is_dead(philo, 1) == 1)
	{
		is_eating(philo);
		if (ded(philo) == 2)
			return ;
	}
}

void	philo_init(t_data	*data)
{
	size_t	i;

	i = (size_t) -1;
	data->all_philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->all_philo)
		philo_error(131);
	while (++i < data->nb_philo)
	{
		data->all_philo[i].last_eat = get_time();
		data->all_philo[i].nb_of_eat = 0;
		data->all_philo[i].alive = 1;
		data->all_philo[i].data = data;
		data->all_philo[i].index = i + 1;
		pthread_mutex_init(&data->all_philo[i].lock, NULL);
		pthread_create(&data->all_philo[i].thread, NULL, (void *)philo_routine \
			, (void *)&data->all_philo[i]);
	}
	check_death(data);
	while (i > 0)
	{
		pthread_join(data->all_philo[i - 1].thread, NULL);
		i--;
	}
}
