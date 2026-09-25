# Philosophers

This repository contains a C implementation of the classic Dining Philosophers problem using POSIX threads (`pthread`) and mutexes.

## Project Structure

- `philo/`: source code and `Makefile`

## Build

```bash
cd philo
make
```

This generates the executable:

- `./philo`

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

- `number_of_philosophers`: total philosophers (and forks)
- `time_to_die`: max time (ms) without eating before a philosopher dies
- `time_to_eat`: eating duration (ms)
- `time_to_sleep`: sleeping duration (ms)
- `number_of_times_each_philosopher_must_eat` (optional): simulation ends when all philosophers eat at least this many times

## Output

The program prints timestamped actions in the format:

```text
<timestamp_in_ms> <philosopher_id> <action>
```

Actions include:

- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

## Notes

- Input arguments must be positive integers.
- The simulation also supports the single philosopher edge case.
