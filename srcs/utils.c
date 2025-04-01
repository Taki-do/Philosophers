/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:54:58 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 12:21:25 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(char *str)
{
	int i;
	int res;
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
		if (check_death(philo, 0, 1))
			return (1);
		taken_fork(philo);
		pthread_mutex_lock(philo->left_fork);
		if (check_death(philo, 1, 1))
			return (1);
		taken_fork(philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (check_death(philo, 1, 0))
			return (1);
		taken_fork(philo);
		pthread_mutex_lock(philo->right_fork);
		if (check_death(philo, 1, 1))
			return (1);
		taken_fork(philo);
	}
	return (0);
}
