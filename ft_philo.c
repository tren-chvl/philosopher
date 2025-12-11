/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:56:50 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/10 15:09:08 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_philo(int argc, char **argv, t_phi *philo)
{
	if (argc < 5 || argc > 6)
	{
		printf("error of argument \n");
		return (1);
	}
	philo->n = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat =ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_din = ft_atoi(argv[5]);
	else
		philo->nb_din = -1;
	if (philo->n <= 0 || philo->t_die <= 0 || philo->t_eat <= 0 || philo->t_sleep <= 0)
	{
		printf("Error of argument\n");
		return (1);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_phi   philo;
	int     i;

	if (parse_philo(argc, argv, &philo))
		return (1);
	if (init_fork(&philo))
		return (1);
	if (init_philo(&philo))
		return (1);
	philo.start = now_ms();
	i = 0;
	while (i < philo.n)
	{
		if (pthread_create(&philo.philo[i].thread, NULL,
				ft_routine, &philo.philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&philo.monitor, NULL, ft_monitor, &philo))
		return (1);
	pthread_join(philo.monitor, NULL);
	i = 0;
	while (i < philo.n)
	{
		pthread_join(philo.philo[i].thread, NULL);
		i++;
	}
	return (0);
}

