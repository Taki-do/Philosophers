/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:30:24 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 13:15:16 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int				id;
	int				nb_eat;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
	long long int	time_meal;
}	t_philosopher;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				is_dead;
	int				philo_full_eat;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	printf_check;
	long long int	start_time;
	pthread_mutex_t	*fork; //tableau de fork
	t_philosopher	*philos; //tout les philosophes
}	t_data;

int				ft_atoi(char *str);
int				philo_living(t_philosopher *philo);
int				check_philo_full(t_philosopher *philo);
int				even_odd(t_philosopher *philo, int num);
int				check_death_routine(t_philosopher *philo, int left, int right);

void			*routine(void *arg);
void			*check_meal(void *arg);
void			init_philos(t_data *data);
void			create_threads(t_data *data);
void			eating(t_philosopher *philo);
void			sleeping(t_philosopher *philo);
void			thinking(t_philosopher *philo);
void			philo_full_eat(t_data *data);
void			taken_fork(t_philosopher *philo);
void			philo_time_die(t_data *data, int i);
void			launch_threads(t_data *data, pthread_t *check_death);
void			better_usleep(t_philosopher *philo, int eat_or_sleep);

long long int	get_time_in_ms(void);
#endif