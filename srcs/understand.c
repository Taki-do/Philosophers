/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   understand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:30:09 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/24 14:42:47 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	pthread_mutex_lock(&mutex);
	printf("Thread %ld ici !\n", (long)arg);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main(void)
{
	pthread_t	th1;
	pthread_t	th2;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&th1, NULL, routine, (void *)1);
	pthread_create(&th2, NULL, routine, (void *)2);
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_mutex_destroy(&mutex);
}
