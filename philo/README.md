*This project has been created as part of the 42 curriculum by mrojouan.*

# Philosophers

I never thought philosophy would be so deadly

## Description

Philosophers is a concurrency simulation project based on the classic Dining Philosophers problem. One or more philosophers are seated around a round table with a large bowl of spaghetti in the middle. Each philosopher alternates between three states: eating, thinking, and sleeping — never doing more than one at a time.

To eat, a philosopher must pick up both the fork to their left and the fork to their right. Since there are as many forks as philosophers, access to forks is a shared and limited resource. Once a philosopher finishes eating, they put both forks back on the table and go to sleep, before waking up and thinking again.

The simulation ends if any philosopher dies of starvation. The goal is to ensure that every philosopher gets to eat and that no one starves — all while philosophers have no knowledge of each other's state and cannot communicate with one another.

## Instructions

Each philosopher is represented as an independent thread, running concurrently alongside all the others. The forks shared between philosophers are protected by mutexes to prevent race conditions and ensure no two philosophers can grab the same fork at the same time. In the special case where there is only one philosopher, they will only have access to a single fork and will therefore be unable to eat, leading to their inevitable death by starvation.

### Compilation

The project uses a Makefile with the following available targets:

| Command | Description |
|---|---|
| `make` | Compile the project |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and the binary |
| `make re` | Full recompile from scratch |
| `make debug` | Compile with debug flags (`-g3 -O0`) |

The binary will be compiled with `-Wall -Wextra -Werror -pthread`.

### Execution

```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
**Examples:**
```bash
./philosophers 5 800 200 200
./philosophers 5 800 200 200 7
```
## Resources

### Documentation & References

**POSIX Threads (pthreads)**
- [pthreads(7) — Linux man page](https://man7.org/linux/man-pages/man7/pthreads.7.html) — General overview of the POSIX threads API
- [pthread_create(3) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_create.3.html) — Creating and joining threads
- [pthread_mutex_init(3) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_init.3.html) — Initializing, locking and destroying mutexes

**Time Management**
- [gettimeofday(2) — Linux man page](https://man7.org/linux/man-pages/man2/gettimeofday.2.html) — Getting current time in microseconds
- [usleep(3) — Linux man page](https://man7.org/linux/man-pages/man3/usleep.3.html) — Sleeping for a given number of microseconds

**The Dining Philosophers Problem**
- [Dining Philosophers Problem — GeeksforGeeks](https://www.geeksforgeeks.org/dining-philosophers-problem/) — Classic explanation of the problem with deadlock and starvation analysis
- [Philosophers 42 Guide — Medium (Dean Ruina)](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2) — Step-by-step guide tailored to the 42 project, covering threads, mutexes, and time management
- [Dining Philosophers — Medium (Dina ELgammal)](https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e) — Another 42-focused walkthrough with detailed mutex and deadlock explanations

### AI Usage

AI was used at two stages of this project. First, for **debugging** — when facing race conditions or unexpected simulation behavior, AI helped identify the root cause of issues and understand why certain thread interactions led to inconsistent results. Second, for **understanding time-related concepts** — in particular the mathematical reasoning behind precise sleep functions, timestamp comparisons, and how to accurately measure elapsed time in milliseconds using `gettimeofday` to avoid timing drift across the simulation.