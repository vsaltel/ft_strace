#ifndef SYSCALL_H
# define SYSCALL_H

# define NB_SYSCALL 328

enum					e_type
{
	TNONE = 0,
	TINT = 1,
	TUINT = 2,
	TSTR = 3,
	TLSTR = 4,
	TPTR = 5,
};

typedef struct			s_syscall
{
	long long unsigned int	code;
	char					*name;
	enum e_type				arg1;
	enum e_type				arg2;
	enum e_type				arg3;
	enum e_type				arg4;
	enum e_type				arg5;
	enum e_type				arg6;
	enum e_type				ret;
}						t_syscall;

static const t_syscall	g_syscall[] =
{
	{ 0, "read", TINT, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 1, "write", TINT, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 2, "open", TSTR, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 3, "close", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 4, "stat", TSTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 5, "fstat", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 6, "lstat", TSTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 7, "poll", TPTR, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 8, "lseek", TINT, TINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 9, "mmap", TPTR, TUINT, TUINT, TUINT, TUINT, TUINT, TPTR},
	{ 10, "mprotect", TPTR, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 11, "munmap", TPTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 12, "brk", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TPTR},
	{ 13, "rt_sigaction", TINT, TPTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 14, "rt_sigprocmask", TINT, TSTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 15, "rt_sigreturn", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 16, "ioctl", TUINT, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 17, "pread64", TUINT, TSTR, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 18, "pwrite64", TUINT, TSTR, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 19, "readv", TUINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 20, "writev", TUINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 21, "access", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 22, "pipe", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 23, "select", TINT, TPTR, TPTR, TPTR, TPTR, TNONE, TINT},
	{ 24, "sched_yield", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 25, "mremap", TUINT, TUINT, TUINT, TUINT, TUINT, TNONE, TINT},
	{ 26, "msync", TUINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 27, "mincore", TUINT, TUINT, TSTR, TNONE, TNONE, TNONE, TINT},
	{ 28, "madvise", TUINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 29, "shmget", TINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 30, "shmat", TINT, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 31, "shmctl", TINT, TINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 32, "dup", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 33, "dup2", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 34, "pause", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 35, "nanosleep", TPTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 36, "getitimer", TINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 37, "alarm", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 38, "setitimer", TINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 39, "getpid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 40, "sendfile", TINT, TINT, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 41, "socket", TINT, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 42, "connect", TINT, TPTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 43, "accept", TINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 44, "sendto", TINT, TPTR, TUINT, TUINT, TPTR, TPTR, TINT},
	{ 45, "recvfrom", TINT, TPTR, TUINT, TUINT, TPTR, TPTR, TINT},
	{ 46, "sendmsg", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 47, "recvmsg", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 48, "shutdown", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 49, "bind", TINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 50, "listen", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 51, "getsockname", TINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 52, "getpeername", TINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 53, "socketpair", TINT, TINT, TINT, TPTR, TNONE, TNONE, TINT},
	{ 54, "setsockopt", TINT, TINT, TINT, TSTR, TINT, TNONE, TINT},
	{ 55, "getsockopt", TINT, TINT, TINT, TSTR, TPTR, TNONE, TINT},
	{ 56, "clone", TUINT, TUINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 57, "fork", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 58, "vfork", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 59, "execve", TSTR, TLSTR, TLSTR, TNONE, TNONE, TNONE, TINT},
	{ 60, "exit", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 61, "wait4", TUINT, TPTR, TINT, TPTR, TNONE, TNONE, TINT},
	{ 62, "kill", TUINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 63, "uname", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 64, "semget", TUINT, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 65, "semop", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 66, "semctl", TINT, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 67, "shmdt", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 68, "msgget", TUINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 69, "msgsnd", TINT, TPTR, TUINT, TINT, TNONE, TNONE, TINT},
	{ 70, "msgrcv", TINT, TPTR, TUINT, TINT, TINT, TNONE, TINT},
	{ 71, "msgctl", TINT, TINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 72, "fcntl", TUINT, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 73, "flock", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 74, "fsync", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 75, "fdatasync", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 76, "truncate", TSTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 77, "ftruncate", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 78, "getdents", TUINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 79, "getcwd", TSTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 80, "chdir", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 81, "fchdir", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 82, "rename", TSTR, TSTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 83, "mkdir", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 84, "rmdir", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 85, "creat", TUINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 86, "link", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 87, "unlink", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 88, "symlink", TSTR, TSTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 89, "readlink", TSTR, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 90, "chmod", TSTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 91, "fchmod", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 92, "chown", TSTR, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 93, "fchown", TUINT, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 94, "lchown", TSTR, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 95, "umask", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 96, "gettimeofday", TPTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 97, "getrlimit", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 98, "getrusage", TINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 99, "sysinfo", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 100, "times", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 101, "ptrace", TINT, TINT, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 102, "getuid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 103, "syslog", TINT, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 104, "getgid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 105, "setuid", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 106, "setgid", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 107, "geteuid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 108, "getegid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 109, "setpgid", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 110, "getppid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 111, "getpgrp", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 112, "setsid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 113, "setreuid", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 114, "setregid", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 115, "getgroups", TINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 116, "setgroups", TINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 117, "setresuid", TPTR, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 118, "getresuid", TPTR, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 119, "setresgid", TUINT, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 120, "getresgid", TPTR, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 121, "getpgid", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 122, "setfsuid", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 123, "setfsgid", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 124, "getsid", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 125, "capget", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 126, "capset", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 127, "rt_sigpending", TPTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 128, "rt_sigtimedwait", TPTR, TPTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 129, "rt_sigqueueinfo", TUINT, TINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 130, "rt_sigsuspend", TPTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 131, "sigaltstack", TPTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 132, "utime", TSTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 133, "mknod", TSTR, TINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 134, "uselib", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 135, "personality", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 136, "ustat", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 137, "statfs", TSTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 138, "fstatfs", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 139, "sysfs", TINT, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 140, "getpriority", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 141, "setpriority", TINT, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 142, "sched_setparam", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 143, "sched_getparam", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 144, "sched_setscheduler", TUINT, TINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 145, "sched_getscheduler", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 146, "sched_get_priority_max", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 147, "sched_get_priority_min", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 148, "sched_rr_get_interval", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 149, "mlock", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 150, "munlock", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 151, "mlockall", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 152, "munlockall", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 153, "vhangup", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 154, "modify_ldt", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 155, "pivot_root", TSTR, TSTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 156, "_sysctl", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 157, "prctl", TINT, TUINT, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 158, "arch_prctl", TINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 159, "adjtimex", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 160, "setrlimit", TUINT, TINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 161, "chroot", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 162, "sync", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 163, "acct", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 164, "settimeofday", TPTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 165, "mount", TSTR, TSTR, TSTR, TUINT, TPTR, TNONE, TINT},
	{ 166, "umount2", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 167, "swapon", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 168, "swapoff", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 169, "reboot", TINT, TINT, TUINT, TPTR, TNONE, TNONE, TINT},
	{ 170, "sethostname", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 171, "setdomainname", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 172, "iopl", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 173, "ioperm", TUINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 174, "create_module", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 175, "init_module", TPTR, TUINT, TSTR, TNONE, TNONE, TNONE, TINT},
	{ 176, "delete_module", TSTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 177, "get_kernel_syms", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 178, "query_module", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 179, "quotactl", TUINT, TSTR, TUINT, TPTR, TNONE, TNONE, TINT},
	{ 180, "nfsservctl", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 181, "getpmsg", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 182, "putpmsg", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 183, "afs_syscall", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 184, "tuxcall", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 185, "security", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 186, "gettid", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 187, "readahead", TINT, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 188, "setxattr", TSTR, TSTR, TPTR, TUINT, TINT, TNONE, TINT},
	{ 189, "lsetxattr", TSTR, TSTR, TPTR, TUINT, TINT, TNONE, TINT},
	{ 190, "fsetxattr", TINT, TSTR, TPTR, TUINT, TINT, TNONE, TINT},
	{ 191, "getxattr", TSTR, TSTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 192, "lgetxattr", TSTR, TSTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 193, "fgetxattr", TINT, TSTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 194, "listxattr", TSTR, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 195, "llistxattr", TSTR, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 196, "flistxattr", TINT, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 197, "removexattr", TSTR, TSTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 198, "lremovexattr", TSTR, TSTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 199, "fremovexattr", TINT, TSTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 200, "tkill", TUINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 201, "time", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 202, "futex", TPTR, TINT, TUINT, TPTR, TPTR, TUINT, TINT},
	{ 203, "sched_setaffinity", TUINT, TUINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 204, "sched_getaffinity", TUINT, TUINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 205, "set_thread_area", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 206, "io_setup", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 207, "io_destroy", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 208, "io_getevents", TUINT, TUINT, TUINT, TPTR, TNONE, TNONE, TINT},
	{ 209, "io_submit", TUINT, TUINT, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 210, "io_cancel", TUINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 211, "get_thread_area", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 212, "lookup_dcookie", TUINT, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 213, "epoll_create", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 214, "epoll_ctl_old", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 215, "epoll_wait_old", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 216, "remap_file_pages", TUINT, TUINT, TUINT, TUINT, TUINT, TNONE, TINT},
	{ 217, "getdents64", TUINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 218, "set_tid_address", TPTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 219, "restart_syscall", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 220, "semtimedop", TINT, TPTR, TUINT, TPTR, TNONE, TNONE, TINT},
	{ 221, "fadvise64", TINT, TUINT, TUINT, TINT, TNONE, TNONE, TINT},
	{ 222, "timer_create", TUINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 223, "timer_settime", TUINT, TINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 224, "timer_gettime", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 225, "timer_getoverrun", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 226, "timer_delete", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 227, "clock_settime", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 228, "clock_gettime", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 229, "clock_getres", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 230, "clock_nanosleep", TUINT, TINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 231, "exit_group", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 232, "epoll_wait", TINT, TPTR, TINT, TINT, TNONE, TNONE, TINT},
	{ 233, "epoll_ctl", TINT, TINT, TINT, TPTR, TNONE, TNONE, TINT},
	{ 234, "tgkill", TUINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 235, "utimes", TSTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 236, "vserver", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 237, "mbind", TUINT, TUINT, TUINT, TPTR, TUINT, TUINT, TINT},
	{ 238, "set_mempolicy", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 239, "get_mempolicy", TPTR, TPTR, TUINT, TUINT, TUINT, TNONE, TINT},
	{ 240, "mq_open", TSTR, TINT, TUINT, TPTR, TNONE, TNONE, TINT},
	{ 241, "mq_unlink", TSTR, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 242, "mq_timedsend", TUINT, TSTR, TUINT, TUINT, TPTR, TNONE, TINT},
	{ 243, "mq_timedreceive", TSTR, TUINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 244, "mq_notify", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 245, "mq_getsetattr", TPTR, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 246, "kexec_load", TUINT, TUINT, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 247, "waitid", TINT, TUINT, TPTR, TINT, TPTR, TNONE, TINT},
	{ 248, "add_key", TSTR, TSTR, TPTR, TUINT, TNONE, TNONE, TINT},
	{ 249, "request_key", TSTR, TSTR, TSTR, TUINT, TNONE, TNONE, TINT},
	{ 250, "keyctl", TINT, TUINT, TUINT, TUINT, TUINT, TNONE, TINT},
	{ 251, "ioprio_set", TINT, TINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 252, "ioprio_get", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 253, "inotify_init", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 254, "inotify_add_watch", TINT, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 255, "inotify_rm_watch", TINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 256, "migrate_pages", TUINT, TUINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 257, "openat", TINT, TSTR, TINT, TINT, TNONE, TNONE, TINT},
	{ 258, "mkdirat", TINT, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 259, "mknodat", TINT, TSTR, TINT, TUINT, TNONE, TNONE, TINT},
	{ 260, "fchownat", TINT, TSTR, TUINT, TUINT, TINT, TNONE, TINT},
	{ 261, "futimesat", TINT, TSTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 262, "newfstatat", TINT, TSTR, TPTR, TINT, TNONE, TNONE, TINT},
	{ 263, "unlinkat", TINT, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 264, "renameat", TINT, TSTR, TINT, TSTR, TNONE, TNONE, TINT},
	{ 265, "linkat", TINT, TSTR, TINT, TSTR, TINT, TNONE, TINT},
	{ 266, "symlinkat", TSTR, TINT, TSTR, TNONE, TNONE, TNONE, TINT},
	{ 267, "readlinkat", TINT, TSTR, TSTR, TINT, TNONE, TNONE, TINT},
	{ 268, "fchmodat", TINT, TSTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 269, "faccessat", TINT, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 270, "pselect6", TINT, TSTR, TSTR, TSTR, TSTR, TSTR, TINT},
	{ 271, "ppoll", TPTR, TUINT, TPTR, TPTR, TUINT, TNONE, TINT},
	{ 272, "unshare", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 273, "set_robust_list", TPTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 274, "get_robust_list", TINT, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 275, "splice", TINT, TPTR, TINT, TPTR, TUINT, TUINT, TINT},
	{ 276, "tee", TINT, TINT, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 277, "sync_file_range", TUINT, TUINT, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 278, "vmsplice", TINT, TPTR, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 279, "move_pages", TUINT, TUINT, TPTR, TPTR, TPTR, TINT, TINT},
	{ 280, "utimensat", TINT, TPTR, TPTR, TINT, TNONE, TNONE, TINT},
	{ 281, "epoll_pwait", TINT, TPTR, TINT, TINT, TPTR, TUINT, TINT},
	{ 282, "signalfd", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 283, "timerfd_create", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 284, "eventfd", TUINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 285, "fallocate", TUINT, TUINT, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 286, "timerfd_settime", TINT, TINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 287, "timerfd_gettime", TINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 288, "accept4", TINT, TPTR, TPTR, TINT, TNONE, TNONE, TINT},
	{ 289, "signalfd4", TINT, TPTR, TUINT, TINT, TNONE, TNONE, TINT},
	{ 290, "eventfd2", TUINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 291, "epoll_create1", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 292, "dup3", TUINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 293, "pipe2", TPTR, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 294, "inotify_init1", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 295, "preadv", TUINT, TPTR, TUINT, TUINT, TUINT, TNONE, TINT},
	{ 296, "pwritev", TUINT, TPTR, TUINT, TUINT, TUINT, TNONE, TINT},
	{ 297, "rt_tgsigqueueinfo", TUINT, TUINT, TINT, TPTR, TNONE, TNONE, TINT},
	{ 298, "perf_event_open", TPTR, TUINT, TINT, TINT, TUINT, TNONE, TINT},
	{ 299, "recvmmsg", TINT, TPTR, TUINT, TUINT, TPTR, TNONE, TINT},
	{ 300, "fanotify_init", TUINT, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 301, "fanotify_mark", TINT, TINT, TUINT, TINT, TINT, TNONE, TINT},
	{ 302, "prlimit64", TUINT, TUINT, TPTR, TPTR, TNONE, TNONE, TINT},
	{ 303, "name_to_handle_at", TINT, TSTR, TPTR, TPTR, TINT, TNONE, TINT},
	{ 304, "open_by_handle_at", TINT, TSTR, TPTR, TPTR, TINT, TNONE, TINT},
	{ 305, "clock_adjtime", TUINT, TPTR, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 306, "syncfs", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 307, "sendmmsg", TINT, TPTR, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 308, "setns", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 309, "getcpu", TPTR, TPTR, TPTR, TNONE, TNONE, TNONE, TINT},
	{ 310, "process_vm_readv", TUINT, TPTR, TUINT, TPTR, TUINT, TUINT, TINT},
	{ 311, "process_vm_writev", TUINT, TPTR, TUINT, TPTR, TUINT, TUINT, TINT},
	{ 312, "kcmp", TUINT, TUINT, TINT, TUINT, TUINT, TNONE, TINT},
	{ 313, "finit_module", TINT, TSTR, TINT, TNONE, TNONE, TNONE, TINT},
	{ 314, "sched_setattr", TUINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 315, "sched_getattr", TUINT, TPTR, TUINT, TUINT, TNONE, TNONE, TINT},
	{ 316, "renameat2", TINT, TSTR, TINT, TSTR, TUINT, TNONE, TINT},
	{ 317, "seccomp", TUINT, TUINT, TSTR, TNONE, TNONE, TNONE, TINT},
	{ 318, "getrandom", TSTR, TUINT, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 319, "memfd", TSTR, TUINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 320, "kexec", TINT, TINT, TUINT, TSTR, TUINT, TNONE, TINT},
	{ 321, "bpf", TINT, TPTR, TUINT, TNONE, TNONE, TNONE, TINT},
	{ 322, "execveat", TINT, TSTR, TLSTR, TLSTR, TINT, TNONE, TINT},
	{ 323, "userfaultfd", TINT, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 324, "membarrier", TINT, TINT, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 325, "mlock2", TUINT, TUINT, TINT, TNONE, TNONE, TNONE, TINT},
	{ 326, "copy_file_range", TINT, TPTR, TINT, TPTR, TUINT, TUINT, TINT},
	{ 327, "preadv2", TUINT, TPTR, TUINT, TUINT, TUINT, TINT, TINT},
	{ 328, "pwritev2", TUINT, TPTR, TUINT, TUINT, TUINT, TINT, TINT},
	{ 329, "pkey_mprotect", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 330, "pkey_alloc", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 331, "pkey_free", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 332, "statx", TUINT, TSTR, TUINT, TUINT, TPTR, TNONE, TINT},
	{ 333, "io_pgetevents", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 334, "rseq", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 335, "pkey_mprotect", TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TINT},
	{ 336, NULL, TNONE, TNONE, TNONE, TNONE, TNONE, TNONE, TNONE}
};

#endif
