/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taomalbe <taomalbe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:53:00 by taomalbe          #+#    #+#             */
/*   Updated: 2025/02/24 16:01:54 by taomalbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	one_philo(void)
{
	printf("0 1 died\n");
}

int	check_philo(t_philo *philo, int ac)
{
	if (philo->nb_philo < 1)
		return (write(2, "Error: [number_of_philosophers] is a negative value\n"
				, 52), -1);
	if (philo->nb_philo == 1)
		return (one_philo(), -1);
	if (philo->nb_philo > 200)
		return (write(2, "Error: [number_of_philosophers] is above 200\n"
				, 45), -1);
	if (philo->time_to_die < 0)
		return (write(2, "Error: [time_to_die] is a negative value\n", 41), -1);
	if (philo->time_to_eat < 0)
		return (write(2, "Error: [time_to_eat] is a negative value\n", 41), -1);
	if (philo->time_to_sleep < 0)
		return (write(2, "Error: [time_to_sleep] is a negative value\n", 43)
				, -1);
	if (ac == 6)
	{
		if (philo->nb_meals < 0)
			return (write(2, "Error: [number_of_times_each_philosophers", 41),
			write(2, "_must_eat] is a negative value\n", 31), -1);
	}
	return (0);
}

void	init_philo(int ac, char *av[], t_philo *philo)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->nb_meals = ft_atoi(av[5]);
}

int	main(int ac, char *av[])
{
	t_philo	philo;

	if (ac == 5 || ac == 6)
	{
		init_philo(ac, av, &philo);
		if (check_philo(&philo, ac) == -1)
			return (1);
		create_threads(&philo);
		//if odd or even
	}
}
