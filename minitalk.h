#ifndef MINITALK_H
#define MINITALK_H

#include <unistd.h>
#include <signal.h>

void	receive(int signal, siginfo_t *siginfo, void *context);

void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

void	send(int pid, char *str, size_t len);
void	get_ack(int sig, siginfo_t *info, void *ucontext);

int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

#endif