/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_alt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:48:08 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 12:16:45 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death(t_philosopher *philo, int left, int right)
{
	pthread_mutex_lock(&philo->data->meal_check);
	if (philo->data->is_dead)
	{
		if (left)
			pthread_mutex_unlock(philo->left_fork);
		if (right)
			pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->data->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_check);
	return (0);
}

void	taken_fork(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->printf_check);
	printf("%lld %d has taken a fork\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->data->printf_check);
}

void	sleeping(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->printf_check);
	printf("%lld %d is sleeping\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->data->printf_check);
}

void	eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->printf_check);
	printf("%lld %d is eating\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->data->printf_check);
}

void	thinking(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->printf_check);
	printf("%lld %d is thinking\n", (get_time_in_ms() - philo->data->start_time), philo->id + 1);
	pthread_mutex_unlock(&philo->data->printf_check);
}
