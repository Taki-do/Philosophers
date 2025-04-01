/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_alt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:48:08 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 12:07:03 by taomalbe         ###   ########.fr       */
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
