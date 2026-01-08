#include "philo.h"

int	get_stop(t_phi *ph)
{
	int	stop;

	pthread_mutex_lock(&ph->state);
	stop = ph->stop;
	pthread_mutex_unlock(&ph->state);
	return (stop);
}

void	set_stop(t_phi *ph, int value)
{
	pthread_mutex_lock(&ph->state);
	ph->stop = value;
	pthread_mutex_unlock(&ph->state);
}

void	take_forks(t_per *per, t_phi *phi)
{
	if (per->id % 2 == 0)
	{
		pthread_mutex_lock(&phi->forks[per->right]);
		log_state(phi, per->id, "has taken a fork");
		pthread_mutex_lock(&phi->forks[per->left]);
		log_state(phi, per->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&phi->forks[per->left]);
		log_state(phi, per->id, "has taken a fork");
		pthread_mutex_lock(&phi->forks[per->right]);
		log_state(phi, per->id, "has taken a fork");
	}
}
