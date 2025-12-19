# lsh – A Minimal POSIX-Style Unix Shell in C

`lsh` is a lightweight, educational Unix shell implemented in C.  
It demonstrates core operating system concepts such as process creation, signal handling, file descriptor manipulation, I/O redirection, and pipelines using low-level POSIX system calls.

This project is intended as a **learning-focused yet practical shell**, not a full replacement for Bash.

---

## Features

- Interactive shell loop with prompt
- Execution of external commands via `fork()` and `execvp()`
- Built-in commands:
  - `cd`, `pwd`, `exit`
  - `mkdir`, `rmdir`, `touch`, `rm`
- Signal handling
  - Ctrl+C terminates foreground processes without killing the shell
  - Ctrl+Z is safely ignored by the shell
- Input and output redirection
  - `<`, `>`, `>>`
- Multi-stage pipelines
  - e.g. `ls | grep c | wc -l`
- Modular multi-file C architecture
- Makefile-based build system

---

## Requirements

- Linux or WSL (Windows Subsystem for Linux)
- GCC (POSIX-compliant)
- Make

---

## Build and Run

Clone the repository and build using `make`:


