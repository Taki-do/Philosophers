/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 13:12:50 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (check_death_routine(philo, 0, 0))
			break ;
		if (even_odd(philo, philo->id))
			break ;
		if (check_death_routine(philo, 1, 1))
			break ;
		eating(philo);
		pthread_mutex_lock(&philo->data->meal_check);
		philo->time_meal = get_time_in_ms();
		pthread_mutex_unlock(&philo->data->meal_check);
		if (philo_living(philo))
			break ;
	}
	return (NULL);
}

void	create_forks(t_data *data)
{
	int	i;

	i = 0;
	data->fork = (pthread_mutex_t *)malloc(data->nb_philo
			* sizeof(pthread_mutex_t));
	if (!data->fork)
		return ;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
}

void	*check_meal(void *arg)
{
	int			i;
	t_data		*data;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->meal_check);
			if (data->philo_full_eat == data->nb_philo)
				return (philo_full_eat(data), NULL);
			else if (get_time_in_ms() - data->philos[i].time_meal
				> data->time_to_die)
				return (philo_time_die(data, i), NULL);
			pthread_mutex_unlock(&data->meal_check);
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	int			i;
	pthread_t	check_death;

	data->philos = (t_philosopher *)malloc(data->nb_philo
			* sizeof(t_philosopher));
	if (!data->philos)
		return ;
	create_forks(data);
	init_philos(data);
	data->start_time = get_time_in_ms();
	launch_threads(data, &check_death);
	pthread_join(check_death, NULL);
	free(data->philos);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	pthread_mutex_destroy(&data->printf_check);
	pthread_mutex_destroy(&data->meal_check);
}
