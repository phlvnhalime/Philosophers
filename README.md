#  Dining Philosophers
# 🧠 Project Overview
This project is an implementation of the classic Dining Philosophers Problem, a concurrency exercise that demonstrates how to handle threads and mutexes in C.
It simulates philosophers sitting around a table, eating, sleeping, and thinking, without falling into deadlocks or data races.

# ⚙️ Technologies
Language: C

Concepts: Threads, Mutexes, Synchronization, Race Conditions

Tools: pthread library

# 🔧 How to Compile

```
make
```

This will compile the project and generate the philo executable.

# 🚀 How to Run

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Arguments:

- number_of_philosophers – how many philosophers are sitting at the table
- time_to_die – time (in ms) after which a philosopher dies if they don't start eating
- time_to_eat – time (in ms) it takes for a philosopher to eat
- time_to_sleep – time (in ms) a philosopher spends sleeping
- number_of_times_each_philosopher_must_eat (optional) – if specified, the simulation ends when all philosophers have eaten this many times

Example:
```
./philo 5 800 200 200 3
```

This runs the simulation with 5 philosophers.

# 🔄 Behavior

You can see the behavior of your code with this link in below.

https://nafuka11.github.io/philosophers-visualizer/

For ./philo 5 800 200 200 3 user input, my result is:

![image](https://github.com/user-attachments/assets/0fc2da99-5e5f-4b45-bda1-df4257e3af2a)


Each philosopher performs the following cycle:

- Think

- Take two forks (mutexes)

- Eat

- Release forks

- Sleep

The program ensures:

- No deadlocks

- No philosopher dies unexpectedly

- Output is clear and timestamped

# 🧵 Thread Management
Each philosopher is a thread. Forks are protected using mutexes to avoid concurrent access. The simulation ends either when a philosopher dies or when all have eaten the specified number of times.

# ✅ Mandatory Rules Met
Avoided deadlocks using order of picking forks

Accurate timing using gettimeofday or clock_gettime

Used mutexes for printing and fork access

Created monitoring threads for death check

# 📌 Known Limitations or To-Do
 Add error handling for wrong input

 Add bonus version (one thread per philosopher + monitor thread)


