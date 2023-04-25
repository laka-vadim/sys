#include <stdio.h>
#include <stdlib.h>

int generalizedFibonacciNumber(int p, int k) {
    if (1 <= k && k <= p + 1) return 1;
    else if (k > p + 1) {
        int sum = 0;
        for (int i = k - p - 1; i <= k - 1; ++i) sum += generalizedFibonacciNumber(p, i);
        return sum;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int p = atoi(argv[1]);
    int k = atoi(argv[2]);
    return generalizedFibonacciNumber(p, k);
}
