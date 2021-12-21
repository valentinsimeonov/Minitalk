/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:40:15 by vsimeono          #+#    #+#             */
/*   Updated: 2021/12/20 14:11:17 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	receive(int signal, siginfo_t *siginfo, void *context)
{
	static char		c;
	static int		i;

	if (signal == SIGUSR1)
		c += 0 << i;
	if (signal == SIGUSR2)
		c += 1 << i;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	kill(siginfo->si_pid, SIGUSR1);
	(void) context;
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

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = &receive;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	write(1, "PID: ", 5);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	while (1)
		pause();
}
