/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 14:09:35 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/30 04:35:22 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	destroy_mutex(int i, t_sim *sim)
{
	while (i < sim->philos_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
	exit(EXIT_FAILURE);
}

void	accurate_sleep(long time_in_ms)
{
	long	start_time;
	long	current;

	start_time = get_current_time();
	while (1)
	{
		current = get_current_time();
		if ((current - start_time) >= time_in_ms)
			break ;
		usleep(500);
	}
}

void	log_state(t_philo *philo, char *state)
{
	int	all_alive_flag;

	pthread_mutex_lock(&philo->sim->alive_mutex);
	all_alive_flag = philo->sim->all_alive;
	pthread_mutex_unlock(&philo->sim->alive_mutex);
	pthread_mutex_lock(&philo->sim->log_mutex);
	if (all_alive_flag)
	{
		printf("%d %d %s\n", (int)(get_current_time() - philo->sim->start_time),
			philo->id, state);
	}
	pthread_mutex_unlock(&philo->sim->log_mutex);
}

void	clean(t_philo *philos, t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->philos_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&philos[i].state_mutex);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_mutex_destroy(&sim->alive_mutex);
	free(sim->forks);
	free(philos);
}
