/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 12:46:06 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 13:10:52 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_full_eat(t_data *data)
{
	int	i;

	data->is_dead = 1;
	if (data->philo_full_eat == data->nb_philo)
	{
		pthread_mutex_unlock(&data->meal_check);
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_join(data->philos[i].thread, NULL);
			i++;
		}
	}
	else
		pthread_mutex_unlock(&data->meal_check);
}

void	philo_time_die(t_data *data, int i)
{
	int	nb_philo;

	data->is_dead = 1;
	nb_philo = i;
	i = 0;
	pthread_mutex_unlock(&data->meal_check);
	pthread_mutex_lock(&data->printf_check);
	printf("%lld %d died\n", get_time_in_ms() - data->start_time, nb_philo + 1);
	pthread_mutex_unlock(&data->printf_check);
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].nb_eat = 0;
		data->philos[i].left_fork = &data->fork[i];
		data->philos[i].right_fork = &data->fork[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		i++;
	}
}

void	launch_threads(t_data *data, pthread_t *check_death)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].time_meal = get_time_in_ms();
		i++;
	}
	pthread_create(check_death, NULL, check_meal, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
}
