# Linux C Process Programming Tasks

This repository contains six C programs demonstrating process creation, inter-process communication, file handling, and system calls in a Linux environment.

## Tasks Overview

1. **Process Hierarchy**  
   Creates a multi-level process tree using `fork()` and displays process/parent IDs.

2. **File Concatenation with Child Processes**  
   Uses three child processes to read separate files. The parent concatenates results, ensuring proper punctuation, and writes to an output file.

3. **Nested Fork & execvp()**  
   Child process forks another child to execute `ls -l ..` using `execvp()`. The parent checks execution status.

4. **execve() with Environment Variables**  
   Passes environment variables to a script using `execve()` and compares before/after states.

5. **Multi-Process File Encryption/Decryption**  
   Lists files in a directory and allows selection for encryption/decryption using a substitution cipher, with each file handled in a separate process.

6. **Process-Based Merge Sort**  
   Implements merge sort where each subarray is sorted by a separate process, then merged by the parent.

## How to Run
Compile any program with:
```bash
gcc filename.c -o program
./program
