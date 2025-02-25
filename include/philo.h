/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:30:24 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/25 15:34:20 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct	s_philo
{
	int nb_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int nb_meals;
	pthread_mutex_t	*fork; //tableau de fork
}   t_philo;

typedef struct	s_philosopher
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo			*philo;
}	t_philosopher;

// utils.c
int     ft_atoi(char *str);

void	create_threads(t_philo *philo);

#endif