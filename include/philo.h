/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:30:24 by taomalbe          #+#    #+#             */
/*   Updated: 2025/03/18 11:39:26 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_philosopher
{
	int				id;
	int				nb_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
	long long int	time_meal;
}	t_philosopher;

typedef struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				is_dead;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	fork_check;
	pthread_mutex_t	eat_check;
	pthread_mutex_t	sleep_check;
	pthread_mutex_t	printf_check;
	long long int	start_time;
	pthread_mutex_t	*fork; //tableau de fork
	t_philosopher	*philos; //tout les philosophes
}	t_data;

// utils.c
int     		ft_atoi(char *str);

void			create_threads(t_data *data);

long long int	get_time_in_ms();
#endif