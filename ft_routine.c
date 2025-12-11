#include "philo.h"

void    *ft_routine(void *arg)
{
	t_per   *per;
	t_phi   *phi;

	per = (t_per *)arg;
	phi = per->phi;
	while (1)
	{
		pthread_mutex_lock(&phi->forks[per->left]);
		log_state(phi, per->id, "take fork");
		pthread_mutex_lock(&phi->forks[per->right]);
		log_state(phi, per->id, "take fork");
		log_state(phi , per->id, "miam mian :)");
		per->last_meal = now_ms();
		usleep(phi->t_eat * 1000);
		pthread_mutex_unlock(&phi->forks[per->left]);
		pthread_mutex_unlock(&phi->forks[per->right]);
		log_state(phi, per->id, "il roupiiie");
		usleep(phi->t_sleep * 1000);
		log_state(phi, per->id, "hi cook !");
	}
	return (NULL);
	
}

void    *ft_monitor(void *arg)
{
	t_phi   *ph;
	int     i;

	ph = (t_phi *)arg;
	while (1)
	{
		i = 0;
		while (i < ph->n)
		{
			if (now_ms() - ph->philo[i].last_meal > ph->t_die)
			{
				log_state(ph, ph->philo[i].id, "died");
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
