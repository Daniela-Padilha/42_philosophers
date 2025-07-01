# 42_philosophers

A 42 school project that simulates the famous **Dining Philosophers Problem**, illustrating problems of concurrency, synchronization, and resource sharing using **threads**, **processes**, and **semaphores**.

## 🧠 Project Overview

The goal is to write a program where multiple philosophers sit at a table, alternating between **thinking**, **eating**, and **sleeping**, while competing for limited resources (**forks**). The main challenge is to prevent **deadlocks**, **race conditions**, and **starvation**.

- ✅ **Mandatory part:** Uses **threads** and **mutexes** for synchronization.
- 🔥 **Bonus part:** Uses **processes**, **semaphores**, and internal **threads** for monitoring.

---

## 📜 Rules of the Simulation

- Each philosopher must:
  - Take two forks (mutex or semaphore).
  - Eat for `time_to_eat` milliseconds.
  - Release the forks.
  - Sleep for `time_to_sleep` milliseconds.
  - Think.

- If a philosopher doesn’t eat within `time_to_die` milliseconds, they **die**, and the simulation ends.

- Optional: If a number of `must_eat_count` is provided, the simulation stops when all philosophers have eaten that number of times.

---

## 🚀 How to Compile

### Mandatory (threads + mutexes):
```bash
make
```

## 🔍 Examples:

./philo 1 800 200 200 - philo shouldn't eat and should die.

./philo 5 800 200 200 - philos shouldn't die.

./philo 5 800 200 200 7 - philos should eat 7 times and program should stop on its own.

./philo 4 410 200 200 - philos shouldn't die.

./philo 4 310 200 100 - philos should die at 310ms.
