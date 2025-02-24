/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:36:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/24 16:14:59 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	mutex;

void	*routine(void *nb)
{
	pthread_mutex_lock(&mutex);
	printf("Thread %ld\n", (long)nb);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

void	create_threads(t_philo *philo)
{
	long		i;
	pthread_t	philos[200];

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (i < philo->nb_philo)
	{
		pthread_create(&philos[i], NULL, routine, (void *)i + 1);
		usleep(philo->time_to_eat * 1000);
		pthread_join(philos[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&mutex);
}
