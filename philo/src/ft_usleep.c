/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:42:49 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/12 15:29:34 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

inline void	ft_usleep(size_t time)
{
	size_t	curr_time;
	size_t	end_time;
	size_t	wait_time;

	curr_time = get_time();
	end_time = curr_time + time - 1;
	while (curr_time < end_time)
	{
		curr_time = get_time();
		wait_time = (end_time - curr_time) / 2;
		if (wait_time > time)
			break ;
		usleep((unsigned int)wait_time);
	}
}
