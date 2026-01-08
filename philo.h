/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:57:05 by marcheva          #+#    #+#             */
/*   Updated: 2025/12/10 15:56:15 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_per
{
	int				id;
	int				left;
	int				right;
	int				meal;
	long			last_meal;
	pthread_t		thread;
	struct s_phi	*phi;
}	t_per;

typedef struct s_phi
{
	int					n;
	int					t_eat;
	int					t_sleep;
	int					t_die;
	int					nb_din;
	int					stop;
	long				start;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		state;
	pthread_t			monitor;
	t_per				*philo;
}	t_phi;

int		ft_atoi(const char *str);
long	now_ms(void);
void	log_state(t_phi *ph, int id, char *msg);
void	*ft_routine(void *arg);
void	*ft_monitor(void *arg);
int		init_philo(t_phi *philo);
int		init_fork(t_phi *philo);
int		get_stop(t_phi *ph);
void	set_stop(t_phi *ph, int value);
void	take_forks(t_per *per, t_phi *phi);
int		ft_strcmp(const char *s1, const char *s2);

#endif