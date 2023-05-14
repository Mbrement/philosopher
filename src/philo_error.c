/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:29:11 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/14 17:05:50 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_error(int i)
{
	if (i == 129)
	{
		printf("Wrong usage : use ./philo number_of_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
	}	
	else if (i == 130)
		printf("Wrong usage : use ./philo with only positive numbers\n");
	else if (i == 131)
		printf("Memorie allocation fail\n");
	exit(i);
}
