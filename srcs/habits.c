/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:25:44 by taomalbe          #+#    #+#             */
/*   Updated: 2025/03/17 10:42:22 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long int	get_time_in_ms()
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
