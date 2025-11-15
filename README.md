# philosophers [![wakatime](https://wakatime.com/badge/user/b5c6762d-cdfb-4336-9c84-87845f0e1976/project/7721e100-b973-45d3-9427-35e9d831e5ec.svg)](https://wakatime.com/badge/user/b5c6762d-cdfb-4336-9c84-87845f0e1976/project/7721e100-b973-45d3-9427-35e9d831e5ec)

*philosophers is a 42 project: In this project, you will learn the basics of threading a process. You will learn how to create threads and explore the use of mutexes.*

- **100/100** ✅

![Illustration](/images/illustration.png)

## Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die` (in milliseconds): If a philosopher has not started eating within
time_to_die milliseconds since the start of their last meal or the start of the
simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

![42](https://img.shields.io/badge/-42-black?style=for-the-badge&logo=42&logoColor=white)