/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 10:57:20 by marcheva          #+#    #+#             */
/*   Updated: 2026/01/12 16:21:25 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	rt_one_philo(t_per *per, t_phi *phi)
{
	pthread_mutex_lock(&phi->forks[per->left]);
	log_state(phi, per->id, "has taken a fork");
	usleep(phi->t_die * 1000);
	pthread_mutex_unlock(&phi->forks[per->left]);
}

void	rt_eat(t_per *per, t_phi *phi)
{
	log_state(phi, per->id, "is eating");
	pthread_mutex_lock(&phi->state);
	per->last_meal = now_ms();
	pthread_mutex_unlock(&phi->state);
	usleep(phi->t_eat * 1000);
	pthread_mutex_lock(&phi->state);
	per->meal++;
	pthread_mutex_unlock(&phi->state);
	pthread_mutex_unlock(&phi->forks[per->left]);
	pthread_mutex_unlock(&phi->forks[per->right]);
}

void	rt_sleep_think(t_per *per, t_phi *phi)
{
	log_state(phi, per->id, "is sleeping");
	usleep(phi->t_sleep * 1000);
	log_state(phi, per->id, "is thinking");
	if (per->id % 2 == 1)
		usleep(500);
}

void	ft_script(t_per *per, t_phi *phi)
{
	while (!get_stop(phi))
	{
		if (per->id % 2 == 1)
			usleep(500);
		take_forks(per, phi);
		if (get_stop(phi))
		{
			pthread_mutex_unlock(&phi->forks[per->left]);
			pthread_mutex_unlock(&phi->forks[per->right]);
			break ;
		}
		rt_eat(per, phi);
		rt_sleep_think(per, phi);
	}
}

void	*ft_routine(void *arg)
{
	t_per	*per;
	t_phi	*phi;

	per = (t_per *)arg;
	phi = per->phi;
	if (phi->n == 1)
	{
		rt_one_philo(per, phi);
		return (NULL);
	}
	if (per->id % 2 == 0)
		usleep(10000);
	ft_script(per, phi);
	return (NULL);
}
