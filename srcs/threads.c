/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/03/13 12:02:14 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *nb)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)nb;
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		
		printf("Philo %d is eating\n", philo->id);
		usleep(philo->data->time_to_eat * 1000);

		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		
		printf("Philo %d is sleeping\n", philo->id);
		usleep(philo->data->time_to_sleep * 1000);

		printf("Philo %d is thinking\n", philo->id);
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

void	create_threads(t_data *data)
{
	long		i;

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
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
