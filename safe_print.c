#include "philosophers.h"

static char		*lltoa(long long c);
static void		putnbr_str(long long n, size_t i, size_t len, char *str);
static size_t	ilen(long long number);

void	safe_print(char *message, long int time, short int id, t_mutex *print)
{
	char	*str_time;
	char	*str_id;

	str_time = lltoa(time);
	str_id = lltoa(id);
	pthread_mutex_lock(&print->mutex);
	write(1, str_time, ilen(time));
	write(1, " ", 1);
	write(1, str_id, ilen(id));
	write(1, message, strlen(message));
	pthread_mutex_unlock(&print->mutex);
	free(str_time);
	free(str_id);
}

static char	*lltoa(long long c)
{
	char			*string;
	size_t			length;
	long long int	number;

	number = c;
	length = ilen(number);
	string = calloc(length + 1, sizeof(char));
	if (!string)
		return (NULL);
	if (number < 0)
	{
		number *= -1;
		*string = '-';
		putnbr_str(number, 1, length, string);
	}
	else
		putnbr_str(number, 0, length, string);
	return (string);
}

static void	putnbr_str(long long n, size_t i, size_t len, char *str)
{
	while (i < len)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
}

static size_t	ilen(long long number)
{
	size_t	counter;

	counter = 0;
	if (number <= 0)
	{
		number *= -1;
		counter++;
	}
	while (number)
	{
		number /= 10;
		counter++;
	}
	return (counter);
}
