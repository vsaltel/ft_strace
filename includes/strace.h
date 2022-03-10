#ifndef STRACE_H
# define STRACE_H

# include <sys/wait.h>
# include <sys/ptrace.h>
# include <sys/uio.h>
# include <sys/user.h>
# include <sys/types.h>
# include <elf.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_reg32
{
	uint32_t		ebx, ecx, edx, esi, edi, ebp, eax;
	unsigned short	ds, __ds, es, __es;
	unsigned short	fs, __fs, gs, __gs;
	uint32_t		orig_eax, eip;
	unsigned short	cs, __cs;
	uint32_t		eflags, esp;
	unsigned short	ss, __ss;
}				t_regs32;

typedef struct s_trace
{
	char	*name;
	char	**args;
	char	**env;
	int		pid;
	int		ppid;
	struct iovec	iov;
	struct user_regs_struct regs;
	int		ret;
	char	*stack_file;
}				t_trace;

extern t_trace trace;

/*	strace_utils.c */
void	init_trace(t_trace *trace, int argc, char **argv, char **env);
void	catch_sigint(int signal);
char	*get_stack_file(t_trace *trace);

/*	program.c */
int		launch_prog(t_trace *trace);

/*	trace.c */
int		tracing(t_trace *trace);

#endif
