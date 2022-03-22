#ifndef STRACE_H
# define STRACE_H

# include <sys/wait.h>
# include <sys/ptrace.h>
# include <sys/uio.h>
# include <sys/user.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <elf.h>
# include <signal.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

# include "syscall.h"
# include "summary.h"

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
	int						c;
	char					*name;
	char					**args;
	char					**env;
	int						pid;
	int						ppid;
	struct iovec			iov;
	struct user_regs_struct	regs;
	int						ret;
	int						delivery_sig;
	char					*stack_file;
	t_sum					*summary;
	t_syscall				sys;
	struct timeval			bef;
	struct timeval			aft;
	sigset_t				new;
	sigset_t				old;
}				t_trace;

extern t_trace trace;

/*	strace_utils.c */
void	init_trace(t_trace *trace, int argc, char **argv, char **env);
char	*get_stack_file(t_trace *trace);
t_syscall get_syscall(t_trace *trace);
void	free_trace(t_trace *trace);

/*	program.c */
int		launch_prog(t_trace *trace);

/*	trace.c */
int		tracing(t_trace *trace);

/*	display.c */
int		display_args(enum e_type type, uint64_t reg, int space);
void	display_ret_syscall(enum e_type type, uint64_t reg);
void	display_syscall(t_trace *trace);
void	display_str_reg(t_trace *trace, uint64_t reg);

/*	get_path.c */
char	*get_path(t_trace *trace);

/*	signal.c */
int		check_child_state(t_trace *trace, int action);
void	catch_sigint(int signal);
int		wait_child(t_trace *trace, int action);
void	init_block_sig(t_trace *trace);

/*	summary.c */
void	display_summary(t_trace *trace);
void	update_summary_count(t_trace *trace, long reg);
void	update_summary_time(t_trace *trace);
void	free_sum(t_sum **sum);
t_sum	*new_sum(t_sum **deb, long long unsigned int code, char *name);
t_sum	*search_sum(t_sum *deb, long long unsigned int code);

#endif
