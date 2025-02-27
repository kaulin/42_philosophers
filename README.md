> [!WARNING]
> To anyone in general, but fellow 42 students in particular: when faced with a problem, it is always better to attempt solving it first alone without consulting the previous works of others. Your precursors were no smarter than and just as fallible as you; Blindly following their footsteps will only lead you on the same detours they took and prevent you from seeing new, faster routes along the way.

# philosophers
Exploring process threading and mutex in the context of a classical computer science problem.

> [!NOTE]  
> 42 Cursus C projects need to follow specific rules and formatting dictated by the [42 Norm](https://github.com/42School/norminette/tree/master/pdf).

## Introduction
This was a 42 cursus project focusing on process threading and mutex. The program simulates a number of philosophers sitting down at a table, where they think, eat and sleep. The table has as many forks as there are philosophers and to eat a philosopher needs two forks. Thus the problem involves using mutexes to control access to a limited resource, forks. Depending on the number of philosophers and the time a philosopher takes to eat, sleep, or die, the simulation runs either indefinitely, until one philosopher dies or until all philosophers have finished eating a preset number of times.

## Installation
Git clone the repository, move into it and run `make` to compile the program.

## Usage
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`

## Problems encountered
- Initializing struct values in the wrong order. I was initially setting the start_time right before creating the threads, but setting the last_meal for each philosopher to start_time already when initializing philosopher structs.
- The accuracy of library functions is not always guaranteed. Using usleep for extended suspension of threads can cause suprising issues.

## Acknowledgements
- Peer evaluators: David Horvath, [Emmi Järvinen](https://github.com/ejarvinen), [Inka Niska](https://github.com/inkaonkala), Arttu Salo, [https://github.com/SpaMillie](https://github.com/SpaMillie), [Simos Tigkas](https://github.com/SimosTigkas), Ilmari Välimäki

## Resources
Combeau, M. (2022, November 2). Threads, mutexes and concurrent programming in C. https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/