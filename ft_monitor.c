#include "philo.h"

int	check_death(t_phi *ph)
{
	int		i;
	long	last;

	i = 0;
	while (i < ph->n)
	{
		pthread_mutex_lock(&ph->state);
		last = ph->philo[i].last_meal;
		pthread_mutex_unlock(&ph->state);
		if (now_ms() - last > ph->t_die)
		{
			log_state(ph, ph->philo[i].id, "died");
			set_stop(ph, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_ate(t_phi *ph)
{
	int	i;

	if (ph->nb_din == -1)
		return (0);
	i = 0;
	while (i < ph->n)
	{
		pthread_mutex_lock(&ph->state);
		if (ph->philo[i].meal < ph->nb_din)
		{
			pthread_mutex_unlock(&ph->state);
			return (0);
		}
		pthread_mutex_unlock(&ph->state);
		i++;
	}
	set_stop(ph, 1);
	return (1);
}

void	*ft_monitor(void *arg)
{
	t_phi	*ph;

	ph = (t_phi *)arg;
	while (!get_stop(ph))
	{
		if (check_death(ph))
			return (NULL);
		if (check_all_ate(ph))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
