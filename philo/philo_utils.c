#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
    size_t	i;
    size_t	c;
    size_t	sign;

    c = 0;
    i = 0;
    sign = 1;
    while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i] == '-')
            sign *= -1;
        i++;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
    {
        c = c * 10 + nptr[i] - '0';
        i++;
    }
    return (sign * c);
}

void handle_exit(char *str, int status)
{
    printf("%s", str);
    exit(status);
}

long int get_time_stamp(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return(time.tv_sec * 1000 + time.tv_usec / 1000);
}