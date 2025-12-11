#include "philo.h"

long	now_ms(void)
{
	struct timeval	tv;
	long			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

void	log_state(t_phi *ph, int id, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&ph->print);
	timestamp = now_ms() - ph->start;
	printf("%ld %d %s\n", timestamp, id, msg);
	pthread_mutex_unlock(&ph->print);
}
