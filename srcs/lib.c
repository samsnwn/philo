#include "../includes/philo.h"

static long	convert_number(const char *str)
{
	long	result;

	result = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			break ;
		if (result > (LONG_MAX - (*str - '0')) / 10)
      error_exit("Value too big");
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

long	ft_atol(const char *str)
{
  int len;
  const char *start;

  len = 0;
  start = str;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
    error_exit("Only positive numbers");
  if (*str < 48 || *str > 57)
    error_exit("Not a digit");
  while (*str >= 48 && *str <= 57)
  {
    ++len;
    str++;
  }
  if (len > 10)
    error_exit("Value too big");
	return (convert_number(start));
}
