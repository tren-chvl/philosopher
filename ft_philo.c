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

int	parse_philo(int argc, char **argv, t_phi *philo)
{
	if (argc < 5 || argc > 6)
	{
		printf("error of argument \n");
		return (1);
	}
	philo->n = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->nb_din = ft_atoi(argv[5]);
	else
		philo->nb_din = -1;
	if (philo->n <= 0 || philo->t_die <= 0
		|| philo->t_eat <= 0 || philo->t_sleep <= 0)
	{
		printf("Error of argument\n");
		return (1);
	}
	return (0);
}

int	start_threads(t_phi *ph)
{
	int	i;

	i = 0;
	while (i < ph->n)
	{
		if (pthread_create(&ph->philo[i].thread, NULL,
				ft_routine, &ph->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&ph->monitor, NULL, ft_monitor, ph) != 0)
		return (1);
	return (0);
}

void	cleanup(t_phi *ph)
{
	int	i;

	pthread_join(ph->monitor, NULL);
	i = 0;
	while (i < ph->n)
	{
		pthread_join(ph->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < ph->n)
	{
		pthread_mutex_destroy(&ph->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&ph->print);
	pthread_mutex_destroy(&ph->state);
	free(ph->forks);
	free(ph->philo);
}

int	main(int argc, char **argv)
{
	t_phi	ph;

	if (parse_philo(argc, argv, &ph))
		return (1);
	if (init_fork(&ph))
		return (1);
	ph.start = now_ms();
	if (init_philo(&ph))
		return (1);
	if (start_threads(&ph))
		return (1);
	cleanup(&ph);
	return (0);
}
