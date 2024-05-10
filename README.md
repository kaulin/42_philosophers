## TODO
Change printer to printer mutex, add a data mutex an individual mutex to each philo

> [!WARNING]
> To anyone in general, but fellow 42 students in particular: when faced with a problem, it is always better to attempt solving it first alone without consulting the previous works of others. Your precursors were no smarter than and just as fallible as you; Blindly following their footsteps will only lead you on the same detours they took and prevent you from seeing new, faster routes along the way.

# philosophers
Exploring process threading and mutex in the context of a classical computer science problem.

> [!NOTE]  
> 42 Cursus C projects need to follow specific rules and formatting dictated by the [42 Norm](https://github.com/42School/norminette/tree/master/pdf).

## Introduction
This was a 42 cursus project focusing on process threading and mutex.

## Installation
Git clone the repository, move into it and run `make` to compile the program.

## Usage
TODO

## Problems encountered
- Initializing struct values in the wrong. I was initially setting the start_time right before creating the threads, but setting the last_meal for each philosopher to start_time already when initializing philosopher structs.
- The accuracy of library functions is not always guaranteed. Using usleep for extended suspension of threads can cause suprising issues.

## Acknowledgements
- Peer evaluators: XXX

## Resources
Combeau, M. (2022, November 2). Threads, mutexes and concurrent programming in C. https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/