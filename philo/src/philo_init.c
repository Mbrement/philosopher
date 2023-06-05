/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:57:59 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/05 16:14:44 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_routine(void *org)
{
	t_philo	*philo;

	philo = org;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_lock(&philo->lock);
	philo->last_eat = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->start);
	pthread_mutex_unlock(&philo->lock);
	if (philo->index % 2 == 0)
		wft_usleep(philo, (philo->data->time_eat / 2));
	while (is_dead(philo, 1) == 1)
	{
		is_eating(philo);
		if (dead(philo) == 2 || philo->nb_of_eat == philo->data->must_eat)
			break ;
	}
}

void	philo_init(t_data	*data)
{
	size_t	i;

	i = (size_t) -1;
	pthread_mutex_lock(&data->start);
	data->all_philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->all_philo)
		return (free(data->fork), free(data), free(data->fork_m), \
			philo_error(131));
	while (++i < data->nb_philo)
	{
		data->fork[i] = AVAILABLE;
		data->all_philo[i].last_eat = get_time();
		data->all_philo[i].nb_of_eat = 0;
		data->all_philo[i].data = data;
		data->all_philo[i].index = i + 1;
		pthread_mutex_init(&data->all_philo[i].lock, NULL);
		pthread_create(&data->all_philo[i].thread, NULL, (void *)philo_routine \
			, (void *)&data->all_philo[i]);
	}
	data->start_time = get_time();
	pthread_mutex_unlock(&data->start);
	check_death(data);
	while (i > 0)
		pthread_join(data->all_philo[i-- - 1].thread, NULL);
}
