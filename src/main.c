/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:21:04 by mbrement          #+#    #+#             */
/*   Updated: 2023/05/16 11:41:11 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	alone(t_data *data);

int	main(int arg_c, char **arg_v)
{
	int		i;
	t_data	*data;

	if (arg_c < 5 || arg_c > 6)
		philo_error(129);
	i = 1;
	while (i < arg_c)
	{
		if (ft_isdigit_str(arg_v[i]) <= 0)
			philo_error(130);
		i++;
	}
	data = malloc(sizeof(t_data));
	if (!data)
		philo_error(131);
	*data = data_init(arg_c, arg_v, *data);
	if (data->nb_philo <= 1)
		alone(data);
	else
		philo_init(data);
	free(data->fork);
	free(data->all_philo);
	free(data);
	return (0);
}

void	alone(t_data *data)
{
	if (data->nb_philo == 1)
	{
		printf("0 0 has taken a fork\n");
		ft_usleep(data->time_to_die);
		printf("%zu 0 died\n", data->time_to_die / 1000);
	}
}
