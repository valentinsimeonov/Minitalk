/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:39:50 by vsimeono          #+#    #+#             */
/*   Updated: 2021/12/22 00:51:10 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
