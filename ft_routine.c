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
	pthread_mutex_lock(&phi->state);
	per->last_meal = now_ms();
	per->meal++;
	pthread_mutex_unlock(&phi->state);
	log_state(phi, per->id, "is eating");
	usleep(phi->t_eat * 1000);
	pthread_mutex_unlock(&phi->forks[per->left]);
	pthread_mutex_unlock(&phi->forks[per->right]);
}

void	rt_sleep_think(t_per *per, t_phi *phi)
{
	log_state(phi, per->id, "is sleeping");
	usleep(phi->t_sleep * 1000);
	log_state(phi, per->id, "is thinking");
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
	while (!get_stop(phi))
	{
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
	return (NULL);
}
