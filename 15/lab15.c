#include <stdio.h>


int isDuplicate(int n, int m, int matrix[n][m], int row1, int row2) {
    for (int col = 0; col < m; col++) {
        if (matrix[row1][col] != matrix[row2][col]) {
        return 0;
        }
    }
    return 1;
}


void replaceDuplicate(int n, int m, int matrix[n][m], int row1, int row2) {
    matrix[row1][0] = '$';
}

int main() {
    int n, m, num = 0;
    scanf("%d", &n);
    scanf("%d", &m);
    int matrix[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &num);
            matrix[i][j] = num;
        }
    }
    for (int i = 1; i < n; i++){
        
    }




    for (int row1 = 0; row1 < n; row1++) {
        for (int row2 = row1 + 1; row2 < n; row2++) {
            if (isDuplicate(n, m, matrix, row1, row2)) {
                matrix[row2][0] = '$';
            }
        }
    }


    for (int row = 0; row < n; row++) {
        if (matrix[row][0] != '$') {
            for (int col = 0; col < m; col++) {
                printf("%d ", matrix[row][col]);
            }
            printf("\n");
        }
    }
    return 0;
}