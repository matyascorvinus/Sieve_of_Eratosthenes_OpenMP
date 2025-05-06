# Sieve of Eratosthenes - OpenMP Parallel Implementation

## Overview
This project implements a parallel version of the Sieve of Eratosthenes algorithm using OpenMP. The Sieve of Eratosthenes is an ancient algorithm for finding all prime numbers up to a specified integer limit, and this implementation leverages parallel processing to improve performance on multi-core systems.

## The Sieve of Eratosthenes Algorithm

The Sieve of Eratosthenes is a simple and efficient algorithm for finding all prime numbers up to a given limit. The algorithm works as follows:

1. Create a list of consecutive integers from 2 through n: (2, 3, 4, ..., n).
2. Initially, let p = 2, the smallest prime number.
3. Enumerate the multiples of p by counting in increments of p from 2p to n, and mark them in the list (these are 2p, 3p, 4p, ...; the p itself should not be marked).
4. Find the first number greater than p in the list that is not marked. If there was no such number, stop. Otherwise, let p now equal this new number (which is the next prime), and repeat from step 3.
5. When the algorithm terminates, the numbers remaining not marked in the list are all the prime numbers below n.

## Pseudocode

```
function sieve(n)
    if n < 2 then return []
    primes = []
    is_prime = [true] * (n + 1)
    is_prime[1] = false
    for p = 2 to sqrt(n) do
        if is_prime[p] then
            for i = p^2 to n step p do
                is_prime[i] = false
    for p = 2 to n do
        if is_prime[p] then
            primes.append(p)
    return primes
```
    

## OpenMP Parallel Implementation

This implementation uses OpenMP to parallelize the Sieve of Eratosthenes algorithm in two key ways:

1. **Marking multiples**: For each prime number found, the task of marking its multiples as non-prime is performed in parallel.

2. **Collecting results**: The final collection of prime numbers is done in parallel, where each thread maintains its own local list to avoid contention.

## Compilation and Execution

### Prerequisites
- A C++ compiler with OpenMP support (GCC, Clang, etc.)
- OpenMP library installed on your system

### Compiling the Code
```bash
g++ -fopenmp eratosthenes_openmp.cpp -o eratosthenes_openmp
```

### Running the Program

```bash
./eratosthenes_openmp [upper_limit]
```

Where `[upper_limit]` is an optional parameter specifying the maximum number to check for primality. The default is 1,000,000.

## Performance Considerations

- The parallel performance scales with the number of available CPU cores.
- For small values of n, the overhead of creating and managing threads might outweigh the benefits of parallelization.
- The program includes timing measurements to help evaluate performance.
- You can control the number of threads used by setting the `OMP_NUM_THREADS` environment variable:
  ```bash
  export OMP_NUM_THREADS=4  # Use 4 threads
  ./eratosthenes_openmp
  ```

## References

### Sieve of Eratosthenes
- Pritchard, P. (1987). "Linear prime-number sieves: a family tree". Science of Computer Programming. 9 (1): 17–35.
- Sorenson, J. (1990). "An Introduction to Prime Number Sieves". Computer Science Technical Reports.
- "The Sieve of Eratosthenes", Prime Number Sieves. Available at: https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

### OpenMP
- Chapman, B., Jost, G., & Van Der Pas, R. (2008). "Using OpenMP: portable shared memory parallel programming". MIT Press.
- OpenMP Architecture Review Board. "OpenMP Application Programming Interface". Available at: https://www.openmp.org/specifications/
- Chandra, R. (2001). "Parallel programming in OpenMP". Morgan Kaufmann.
- OpenMP API Reference Guide: https://www.openmp.org/resources/refguides/
- OMP Specifications: https://www.openmp.org/specifications/
- "OpenMP Introduction with Installation Guide". Available at: https://www.geeksforgeeks.org/openmp-introduction-with-installation-guide/
- "OpenMP on Ubuntu". Available at: https://medium.com/swlh/openmp-on-ubuntu-1145355eeb2
- "Install OpenMP on Windows using MinGW". Available at: https://www.toolify.ai/ai-news/install-openmp-on-windows-using-mingw-a-stepbystep-guide-659927