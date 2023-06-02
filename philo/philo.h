/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 09:16:55 by mbrement          #+#    #+#             */
/*   Updated: 2023/06/01 20:41:24 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

# define TAKEN 1

# define  AVAILABLE 0

typedef struct s_data {
	size_t			nb_philo;
	size_t			time_to_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			must_eat;
	size_t			start_time;
	struct s_philo	*all_philo;
	int				*fork;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_mutex_t	start;
	int				alive;
}		t_data;

typedef struct s_philo {
	size_t			index;
	size_t			last_eat;
	size_t			nb_of_eat;
	pthread_t		thread;
	pthread_mutex_t	lock;
	struct s_data	*data;
}		t_philo;

//CORE
void	philo_error(int i);
t_data	*data_init(int argc, char **argv, t_data *data);
void	philo_init(t_data	*data);
int		is_dead(t_philo *philo, int i);
void	is_eating(t_philo *philo);
void	check_death(t_data *data);
void	philo_fork(t_philo *philo);
int		dead(t_philo *philo);
void	first_fork(t_philo *philo);
void	second_fork(t_philo *philo);
int		ft_musteat(t_philo *philo);

//TOOLS
int		ft_isdigit(int c);
int		ft_isdigit_str(char *str);
int		ft_atoi(const char *str);
size_t	get_time(void);
void	ft_usleep(size_t time);
size_t	since_start(t_philo *philo);
void	ft_print(int i, t_philo *philo);
void	wft_usleep(t_philo *philo, size_t t);

#endif