#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

std::vector<int> sieve_of_eratosthenes(int n) {
    // Create a boolean array "isPrime[0..n]" and initialize all entries as true.
    std::vector<bool> isPrime(n + 1, true);
    
    // 0 and 1 are not prime numbers
    isPrime[0] = isPrime[1] = false;
    
    // Iterate through numbers from 2 to sqrt(n)
    for (int i = 2; i <= std::sqrt(n); i++) {
        // If isPrime[i] is not changed, then it's a prime
        if (isPrime[i]) {
            // Use OpenMP to parallelize the marking of multiples
            #pragma omp parallel for
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    // Create a vector to store the prime numbers
    std::vector<int> primes;
    
    // Collect all prime numbers
    #pragma omp parallel
    {
        std::vector<int> local_primes;
        
        #pragma omp for nowait
        for (int i = 2; i <= n; i++) {
            if (isPrime[i]) {
                local_primes.push_back(i);
            }
        }
        
        #pragma omp critical
        {
            primes.insert(primes.end(), local_primes.begin(), local_primes.end());
        }
    }
    
    // Sort the results since multiple threads might add in different orders
    std::sort(primes.begin(), primes.end());
    
    return primes;
}

int main(int argc, char* argv[]) {
    int n = 1000000;
    
    if (argc > 1) {
        n = std::stoi(argv[1]);
    }
    
    double start_time = omp_get_wtime();
    
    std::vector<int> primes = sieve_of_eratosthenes(n);
    
    double end_time = omp_get_wtime();
    
    std::cout << "Found " << primes.size() << " primes up to " << n << std::endl;
    std::cout << "Time taken: " << end_time - start_time << " seconds" << std::endl;
    
    // Uncomment to print the first few primes
    /*
    std::cout << "First few primes: ";
    for (size_t i = 0; i < std::min(primes.size(), size_t(10)); i++) {
        std::cout << primes[i] << " ";
    }
    std::cout << std::endl;
    */
    
    return 0;
}
