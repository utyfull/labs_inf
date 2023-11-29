#include <stdio.h>

int power(int base, int exponent) {
    int result = 1;

    while (exponent > 0) {
        result *= base;
        --exponent;
    }

    return result;
}

int main() {
    int numSize, firstDigit, num, numCopy, repeatSize;
    scanf("%d", &num);
    scanf("%d", &repeatSize);
    numCopy = num;
    while (numCopy >= 1) {
        numSize++;
        numCopy = (int)(numCopy / 10);
    }
    for (int i = 0; i < repeatSize; i++) {
        firstDigit = (int)(num / power(10, (numSize - 1)));
        num = (num % (int)power(10, numSize - 1)) * 10 + firstDigit;
    }
    printf("%d", num);
    return 0;
}