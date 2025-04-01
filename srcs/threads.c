/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 12:06:49 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *arg)
{
	long long		start;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (1)
	{
		if (check_death(philo, 0, 0))
			break ;
		if (philo->id % 2)
		{
			pthread_mutex_lock(philo->right_fork);

			if (check_death(philo, 0, 1))
				break ;
			
			pthread_mutex_lock(&philo->data->printf_check);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
			pthread_mutex_unlock(&philo->data->printf_check);
			pthread_mutex_lock(philo->left_fork);
			
			if (check_death(philo, 1, 1))
				break ;
			
			pthread_mutex_lock(&philo->data->printf_check);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
			pthread_mutex_unlock(&philo->data->printf_check);
		}
		else //pair
		{
			pthread_mutex_lock(philo->left_fork);
			
			if (check_death(philo, 1, 0))
				break ;
			
			pthread_mutex_lock(&philo->data->printf_check);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
			pthread_mutex_unlock(&philo->data->printf_check);
			pthread_mutex_lock(philo->right_fork);
			
			if (check_death(philo, 1, 1))
				break ;
			
			pthread_mutex_lock(&philo->data->printf_check);
			printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
			pthread_mutex_unlock(&philo->data->printf_check);
		}

		if (check_death(philo, 1, 1))
			break ;
		
		pthread_mutex_lock(&philo->data->printf_check);
		printf("%lld %d is eating\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->data->printf_check);
		
		pthread_mutex_lock(&philo->data->meal_check);
		philo->time_meal = get_time_in_ms();
		pthread_mutex_unlock(&philo->data->meal_check);
		//partie a clear
		pthread_mutex_lock(&philo->data->meal_check);
		philo->nb_eat++;
		if (philo->nb_eat == philo->data->nb_meals)
		{
			philo->data->philo_full_eat++;
			pthread_mutex_unlock(&philo->data->meal_check);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		if (philo->data->nb_meals != -1 && philo->nb_eat >= philo->data->nb_meals)
		{
			pthread_mutex_unlock(&philo->data->meal_check);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meal_check);
		
		start = get_time_in_ms();
		while (get_time_in_ms() - start < philo->data->time_to_eat)
			usleep(500);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (check_death(philo, 0, 0))
			break ;
		pthread_mutex_lock(&philo->data->printf_check);
		printf("%lld %d is sleeping\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->data->printf_check);
		
		start = get_time_in_ms();
		while (get_time_in_ms() - start < philo->data->time_to_sleep)
			usleep(500);
		if (check_death(philo, 0, 0))
			break ;

		pthread_mutex_lock(&philo->data->printf_check);
		printf("%lld %d is thinking\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
		pthread_mutex_unlock(&philo->data->printf_check);
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
	int			j;
	int			nb_philo;
	t_data		*data;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->meal_check);
			if (data->nb_meals != -1 && data->philo_full_eat == data->nb_philo)
			{
				data->is_dead = 1;
				if (data->philo_full_eat == data->nb_philo)
				{
					pthread_mutex_unlock(&data->meal_check);
					j = 0;
					while (j < data->nb_philo)
					{
						pthread_join(data->philos[j].thread, NULL);
						j++;
					}
				}
				else
				pthread_mutex_unlock(&data->meal_check);
				return (NULL);
			}
			else if (get_time_in_ms() - data->philos[i].time_meal > data->time_to_die)
			{
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
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_check);
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
		data->philos[i].nb_eat = 0;
		data->philos[i].left_fork = &data->fork[i];
		data->philos[i].right_fork = &data->fork[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		i++;
	}
	i = 0;
	data->start_time = get_time_in_ms();
	while (i < data->nb_philo)
	{
		data->philos[i].time_meal = get_time_in_ms();
		i++;
	}
	pthread_create(&check_death, NULL, check_meal, data);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
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
