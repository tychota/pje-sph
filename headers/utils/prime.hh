#pragma once

#include <stdint.h>
#include <math.h>

class prime {
public:
    /*
     * Accuracy parameter `k´ of the Miller-Rabin algorithm.
     *
     */
    static const int DEFAULT_ACCURACY = 10;

    /*
     * The Miller-Rabin probabilistic primality test.
     *
     * Returns true if ``n´´ is PROBABLY prime, false if it's composite.
     * The parameter ``k´´ is the accuracy.
     *
     * The running time should be somewhere around O(k log_3 n).
     *
     */
    bool isprime(int64_t n, int accuracy = DEFAULT_ACCURACY);

    /*
     * Set which rand function to use and its maximum value.
     *
     * If passed a NULL parameter, it will revert back to the default libc
     * rand().
     */
    void setrand(int (*rand_function)(void), const int rand_max);

    int64_t next(int64_t n);
};

