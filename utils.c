#include "philo.h"

int ft_atoi(const char *str)
{
    int i;
    int res;
    int pn;

	pn = 1;
	res = 0;
	i = 0;

	while(str[i] <= 32 && str[i])
		i++;
    if(str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			pn = -1;
		i++;
		if(str[i] == '+' || str[i] == '-')
			return(-1);
	}
	while(str[i])
	{
		if(str[i] >= '0' && str[i] <= '9')
			res = res * 10 + str[i++] - 48;
		else
			return(-1);
	}
	return(res * pn);
}

u32 gettime()
{
    struct timeval t;

    gettimeofday(&t, NULL);

    return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void print(t_philosophers *philo, char *str)
{
	pthread_mutex_lock(&philo->pm->printing);
	if (philo->pm->is_dead == false)
    	printf("%d %d %s\n", gettime()-philo->pm->time, philo->id, str);
	pthread_mutex_unlock(&philo->pm->printing);
}
