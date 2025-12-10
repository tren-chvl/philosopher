/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:10:54 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/10 16:44:31 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	init_philo(t_phi *philo)
{
	int	i;

	i = 0;
	philo->philo = malloc(sizeof(t_per) * philo->n);
	if (!philo->philo)
		return (1);
	while (i < philo->n)
	{
		i++;
	}
	return (0);
}

int	init_fork(t_phi *philo)
{
	int	i;

	i = 0;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->n);
	if (!philo->forks)
		return (1);
	while (i < philo->n)
	{
		if (pthread_mutex_init(&philo->philo[i], NULL) != 0);
			return (1);
		i++;
	}
	return (0);
}

