#include <stdio.h>

const int I0 = -30;
const int J0 = -4;
const int L0 = 12;

int abs(int num) {
    if (num < 0) {
        return -1 * num;
    }
    return num;
}

int min(int num1, int num2){
    if (num1 > num2) {
        return num2;
    }
    return num1;
}

int max(int num1, int num2) {
    if (num1 > num2) {
        return num1;
    }
    return num2;
}

char checkPlace(int i, int j) {
    if (i + j + 20 <= 0 && i + j + 10 >= 0) {
        return 1;
    }
    return 0;
}

int main() {

    int iOld = I0;
    int jOld = J0;
    int lOld = L0;

    int iNew, jNew, lNew;

    if (checkPlace(I0, J0) == 1) {
        printf("Point in the right place; i = %d, j = %d, l = %d, k = 1\n", I0, J0, L0);
        return 0;
    }

    for (int k = 0; k < 50; k++) {
        iNew = abs(iOld - lOld) + min(jOld % 10, lOld % 10) - 20;
        jNew = max(k - iOld, min(jOld, max(iOld - lOld, jOld - lOld))) % 30;
        lNew = (lOld * lOld) % 20 - max(iOld, jOld) % (k + 1);

        printf("i = %d, j = %d\n", iNew, jNew);

        if (checkPlace(iNew, jNew) == 1) {
            printf("Point in the right place; i = %d, j = %d, l = %d, k = %d\n", iNew, jNew, lNew, k + 1);
            return 0;
        }

        iOld = iNew;
        jOld = jNew;
        lOld = lNew;
    }

    printf("Point haven`t been in the right place; i = %d, j = %d, l = %d\n", iNew, jNew, lNew);
    return 0;
    
}