/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:02:25 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/14 17:36:02 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	data_init(int argc, char **argv, t_data	data)
{
	int	i;

	i = ft_atoi(argv[1]);
	data.nb_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]) * 1000;
	data.time_eat = ft_atoi(argv[3]) * 1000;
	data.time_sleep = ft_atoi(argv[4]) * 1000;
	data.start_time = get_time();
	data.alive = 1;
	pthread_mutex_init(&data.lock, NULL);
	data.fork = malloc(sizeof(int) * (data.nb_philo));
	if (!data.fork)
		return (philo_error(131), data);
	while (--i >= 0)
		data.fork[i] = AVAILABLE;
	if (argc == 6)
		data.must_eat = ft_atoi(argv[5]);
	else
		data.must_eat = -1;
	return (data);
}
