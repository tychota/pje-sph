#pragma once

#include <stdint.h>
#include <math.h>

class Prime {
public:
    /**
     * Accuracy parameter `k´ of the Miller-Rabin algorithm.
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

    int64_t next(int64_t n);
};

