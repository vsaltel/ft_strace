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

typedef struct user_regs_struct64
{
  unsigned long r15;
  unsigned long r14;
  unsigned long r13;
  unsigned long r12;
  unsigned long rbp;
  unsigned long rbx;
  unsigned long r11;
  unsigned long r10;
  unsigned long r9;
  unsigned long r8;
  unsigned long rax;
  unsigned long rcx;
  unsigned long rdx;
  unsigned long rsi;
  unsigned long rdi;
  unsigned long orig_rax;
  unsigned long rip;
  unsigned long cs;
  unsigned long eflags;
  unsigned long rsp;
  unsigned long ss;
  unsigned long fs_base;
  unsigned long gs_base;
  unsigned long ds;
  unsigned long es;
  unsigned long fs;
  unsigned long gs;
}				t_regs_64;

typedef struct user_regs_struct32
{
  long int ebx;
  long int ecx;
  long int edx;
  long int esi;
  long int edi;
  long int ebp;
  long int eax;
  long int xds;
  long int xes;
  long int xfs;
  long int xgs;
  long int orig_eax;
  long int eip;
  long int xcs;
  long int eflags;
  long int esp;
  long int xss;
}				t_regs_32;

typedef struct s_trace
{
	int						c;
	char					*name;
	char					**args;
	char					**env;
	int						pid;
	int						ppid;
	struct iovec			iov;
	t_regs_64				regs64;
	t_regs_32				regs32;
	int						detach;
	int						arch;
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
t_syscall get_syscall(t_trace *trace);
void	free_trace(t_trace *trace);
int		get_architecture(t_trace *trace);

/*	program.c */
int		launch_prog(t_trace *trace);

/*	trace.c */
int		tracing(t_trace *trace);

/*	display.c */
int		display_args(enum e_type type, uint64_t reg, int space);
void	display_ret_syscall(enum e_type type, uint64_t reg);
void	display_syscall(t_trace *trace, int cont);
void	display_str_reg(t_trace *trace, uint64_t reg);

/*	get_path.c */
char	*get_path(t_trace *trace);

/*	signal.c */
int		check_child_state(t_trace *trace, int action);
void	catch_sigint(int signal);
int		wait_child(t_trace *trace, int action);
void	init_block_sig(t_trace *trace);
void	detach_prog(t_trace *trace);

/*	summary.c */
void	display_summary(t_trace *trace);
void	update_summary_count(t_trace *trace, long reg);
void	update_summary_time(t_trace *trace);
void	free_sum(t_sum **sum);
t_sum	*new_sum(t_sum **deb, long long unsigned int code, char *name);
t_sum	*search_sum(t_sum *deb, long long unsigned int code);

#endif
