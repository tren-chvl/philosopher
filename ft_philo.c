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

int main(int argc, char *argv[])
{
	t_phi *philo;

	if (parse_philo(argc, argv, philo))
		return (1);
	printf("philosopher %d\nnb eat = %d\nnb to sleep\nnb to die\nnb dinner %d\n",philo->n,philo->t_eat,philo->t_sleep,philo->t_die,philo->nb_din);
	return (0);
}