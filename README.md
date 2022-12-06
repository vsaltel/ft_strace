# ft_strace

My version of the standard strace program in C.

This is a syscall calls and signal tracer.

42 Paris school system project.

## Build
Compilation :

```
make
```

Clean objects files :
```
make clean
```

Clean entire project :
```
make fclean
```
## Usage

```
ft_strace [-ch] PROG [ARGS]

	-c count time, calls, and errors for each syscall and report summary
	-h this help
```
