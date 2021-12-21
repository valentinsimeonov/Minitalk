/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 14:09:36 by vsimeono          #+#    #+#             */
/*   Updated: 2021/12/20 14:09:37 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>

void	receive(int signal, siginfo_t *siginfo, void *context);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	send(int pid, char *str, size_t len);
void	get_ack(int sig, siginfo_t *info, void *ucontext);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

#endif 