#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

typedef unsigned int	u32;
struct	s_philomain;

typedef struct s_philosophers
{
	u32	id;
	u32	left_fork_id;
	u32	right_fork_id;
	u32	end_time_to_eat;
	int	eat;
	struct s_philomain	*pm;
}	t_philosophers;

typedef struct s_philomain
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	philo_nb;
	int	must_eat;
	bool	is_dead;
	pthread_mutex_t	printing;
	u32	time;
	pthread_mutex_t	*mutexes;
	pthread_t	*threads;
	t_philosophers	*philos;
}	t_philomain;

int		ft_atoi(const char *str);
bool	init_arguments(int ac, char **av, t_philomain *philomain);
bool	init_philo(t_philomain *pm, int i);
u32		gettime(void);
void	print(t_philosophers *philo, char *str);
void	my_sleep(u32 time);
#endif