/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:53:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/04/01 13:11:44 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	one_philo(t_data *data)
{
	printf("%d 1 has taken a fork\n", 0);
	usleep(data->time_to_die * 1000);
	printf("%d 1 died\n", data->time_to_die);
}

int	check_philo(t_data *data, int ac)
{
	if (data->nb_philo < 1)
		return (write(2, "Error: [number_of_philosophers] is a negative value\n"
				, 52), -1);
	if (data->nb_philo == 1)
		return (one_philo(data), -1);
	if (data->nb_philo > 200)
		return (write(2, "Error: [number_of_philosophers] is above 200\n"
				, 45), -1);
	if (data->time_to_die < 0)
		return (write(2, "Error: [time_to_die] is a negative value\n", 41), -1);
	if (data->time_to_eat < 0)
		return (write(2, "Error: [time_to_eat] is a negative value\n", 41), -1);
	if (data->time_to_sleep < 0)
		return (write(2, "Error: [time_to_sleep] is a negative value\n", 43)
			, -1);
	if (ac == 6)
	{
		if (data->nb_meals < 0)
			return (write(2, "Error: [number_of_times_each_philosophers", 41),
				write(2, "_must_eat] is a negative value\n", 31), -1);
	}
	return (0);
}

void	init_philo(int ac, char *av[], t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		data.is_dead = 0;
		if (ac != 6)
			data.nb_meals = -1;
		data.philo_full_eat = 0;
		pthread_mutex_init(&data.meal_check, NULL);
		pthread_mutex_init(&data.printf_check, NULL);
		init_philo(ac, av, &data);
		if (check_philo(&data, ac) == -1)
			return (1);
		create_threads(&data);
	}
}
