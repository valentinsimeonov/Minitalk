/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:52:18 by vsimeono          #+#    #+#             */
/*   Updated: 2021/12/22 00:43:13 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_flag;

void	send(int pid, char *str, size_t len)
{
	int		shift;
	size_t	i;

	i = 0;
	while (i <= len)
	{
		shift = 0;
		while (shift <= 7)
		{
			g_flag = 0;
			if ((str[i] >> shift) & 1)
			{
				kill(pid, SIGUSR2);
				usleep(100000);
			}
			else
			{
				kill(pid, SIGUSR1);
				usleep(100000);
			}
			shift++;
			while (g_flag == 0)
				pause();
		}
		i++;
	}
}

void	get_ack(int sig, siginfo_t *info, void *ucontext)
{	
	g_flag = 1;
	(void) ucontext;
	(void) info;
	(void) sig;
}

int	ft_atoi(const char *str)
{
	int		i;
	int		num;
	int		sign;

	i = 0;
	sign = 1;
	num = 0;
	while ((*(str + i) >= 9 && *(str + i) <= 13) || (*(str + i) == ' '))
	{
		i++;
	}
	if (*(str + i) == '-' || *(str + i) == '+')
	{
		if (*(str + i) == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((*(str + i) >= 48 && *(str + i) <= 57))
	{
		num = (num * 10) + (*(str + i) - '0');
		i++;
	}
	return (num * sign);
}

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	temp;

	temp = n;
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (temp < 0)
	{
		ft_putchar_fd('-', fd);
		temp *= -1;
	}
	if (temp < 10)
	{
		ft_putchar_fd(temp + '0', fd);
	}
	else
	{
		ft_putnbr_fd(temp / 10, fd);
		ft_putnbr_fd(temp % 10, fd);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, s++, 1);
		}
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					pid;

	sig.sa_sigaction = &get_ack;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		send(pid, argv[2], ft_strlen(argv[2]));
	}
	
	if (argc != 3)
		write(1, "Try again, please\n", 18);
	return (0);
}
