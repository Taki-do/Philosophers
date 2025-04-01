/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:54:58 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 13:14:00 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	even_odd(t_philosopher *philo, int num)
{
	if (num % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		if (check_death_routine(philo, 0, 1))
			return (1);
		taken_fork(philo);
		pthread_mutex_lock(philo->left_fork);
		if (check_death_routine(philo, 1, 1))
			return (1);
		taken_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (check_death_routine(philo, 1, 0))
			return (1);
		taken_fork(philo);
		pthread_mutex_lock(philo->right_fork);
		if (check_death_routine(philo, 1, 1))
			return (1);
		taken_fork(philo);
	}
	return (0);
}

int	check_philo_full(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->meal_check);
	philo->nb_eat++;
	if (philo->nb_eat == philo->data->nb_meals)
	{
		philo->data->philo_full_eat++;
		pthread_mutex_unlock(&philo->data->meal_check);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_check);
	return (0);
}

void	better_usleep(t_philosopher *philo, int eat_or_sleep)
{
	long long		start;

	start = get_time_in_ms();
	if (!eat_or_sleep)
	{
		while (get_time_in_ms() - start < philo->data->time_to_eat)
			usleep(500);
	}
	else
	{
		while (get_time_in_ms() - start < philo->data->time_to_sleep)
			usleep(500);
	}
}

int	philo_living(t_philosopher *philo)
{
	if (check_philo_full(philo))
		return (1);
	better_usleep(philo, 0);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (check_death_routine(philo, 0, 0))
		return (1);
	sleeping(philo);
	better_usleep(philo, 1);
	if (check_death_routine(philo, 0, 0))
		return (1);
	thinking(philo);
	return (0);
}
