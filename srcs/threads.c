/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/03/15 15:27:47 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->meal_check);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->meal_check);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_check);
		if (philo->id % 2) //impair
		{
			pthread_mutex_lock(philo->left_fork);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id);
			pthread_mutex_lock(philo->right_fork);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id);
		}
		else //pair
		{
			pthread_mutex_lock(philo->right_fork);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id);
			pthread_mutex_lock(philo->left_fork);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id);
		}
		philo->time_meal = get_time_in_ms();
		printf("%lld %d is eating\n", (get_time_in_ms() - philo->data->start_time), philo->id);
		usleep(philo->data->time_to_eat * 1000);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		printf("%lld %d is sleeping\n", (get_time_in_ms() - philo->data->start_time), philo->id);
		usleep(philo->data->time_to_sleep * 1000);

		printf("%lld %d is thinking\n", (get_time_in_ms() - philo->data->start_time), philo->id);
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
	long long	current_time;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			current_time = get_time_in_ms();
			if (current_time - data->philos[i].time_meal > data->time_to_die)
			{
				printf("%lld %d died\n", current_time - data->start_time, i);
				pthread_mutex_lock(&data->meal_check);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->meal_check);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	create_threads(t_data *data)
{
	long		i;
	pthread_t	check_death;
	
	i = 0;
	data->philos = (t_philosopher *)malloc(data->nb_philo * sizeof(t_philosopher));
	if (!data->philos)
		return ;
	i = 0;
	create_forks(data);
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = &data->fork[i];
		data->philos[i].right_fork = &data->fork[(i + 1) % data->nb_philo]; //reverifier la logique
		data->philos[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].time_meal = get_time_in_ms();
		i++;
	}
	pthread_create(&check_death, NULL, check_meal, data);
	pthread_detach(check_death);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&data->meal_check);
}
