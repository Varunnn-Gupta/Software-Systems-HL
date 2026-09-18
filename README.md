# CSE 513A - Software Systems

## Hands-On Practicals

A collection of hands-on practical experiments completed as a course requirement for **CSE 513A - Software Systems**.

The practicals focus on Linux/UNIX system programming and system-level mechanisms, covering file and process management, system calls, inter-process communication, timers, resource limits, multithreading, and signals.

## Environment

* **Course:** CSE 513A - Software Systems
* **OS:** Ubuntu on WSL 2
* **Editor:** Visual Studio Code
* **Compiler:** GCC
* **Shell:** Bash

## Topics Covered

The complete set of 60 hands-on questions covers the following areas:

* **File Management**
* **Process Management**
* **System and IPC Mechanisms**
* **Timers**
* **Resource Limits**
* **Multithreading**
* **Signals**

## Repository Structure

```text
hands-on-list/
│
├── 1-file-mgmt/
│   ├── Ques-01-file-links/
│   ├── Ques-02-infinite-process/
│   ├── Ques-03-file-desc-using-creat/
│   └── ...
│
├── 2-process-mgmt/
│   ├── ...
│
├── 3-system-ipc-mechanisms/
│   ├── ...
│
├── 4-timer-resource-limits-multithreading/
│   ├── ...
│
└── README.md
```

The practicals are organized according to their respective system-level topics. Individual questions are maintained within the relevant topic directory.

## Working Environment

The experiments are performed in an **Ubuntu WSL 2** environment through **Visual Studio Code**. Programs are compiled using GCC and executed within the Linux environment.

Typical compilation:

```bash
gcc program.c -o program
```

Execution:

```bash
./program
```

System-level information and behavior are examined using standard Linux interfaces, system calls, commands, and the `/proc` filesystem where applicable.

## Purpose

This repository serves as a record of the implementation and experimentation performed as part of **CSE 513A — Software Systems**, containing the source code, compiled programs, and associated files for the hands-on practical experiments.
