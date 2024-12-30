/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmuhaise <mmuhaise@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:17:47 by mmuhaise          #+#    #+#             */
/*   Updated: 2024/12/30 04:34:01 by mmuhaise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		state_mutex;
	pthread_t			thread;
	struct s_sim		*sim;
}					t_philo;

typedef struct s_sim
{
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	alive_mutex;
	int				all_alive;
	t_philo			*philos;
}					t_sim;

int		validate_args(int ac, char **av);
int		ft_atoi(const char *str);
long	get_current_time(void);
void	init_all_data(char **argv);
void	destroy_mutex(int i, t_sim *sim);
void	log_state(t_philo *philo, char *state);
void	accurate_sleep(long time_in_ms);
void	clean(t_philo *philos, t_sim *sim);

#endif