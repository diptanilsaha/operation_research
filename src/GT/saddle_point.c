// Game Theory - Saddle Point

#include <stdlib.h>
#include <stdio.h>

void _calculate_row_col(int a[100][100], int m, int n, int row[100], int col[100]) {
	int min, max;
	int i, j;
	for(i=0; i<m; i++) {
        min = INT_MAX;
        for(j=0; j<n; j++) {
            if(a[i][j] < min) {
                min = a[i][j];
            }
        }
        row[i] = min;
    }

    for(i=0; i<n; i++) {
        max = INT_MIN;
        for(j=0; j<m; j++) {
            if(a[j][i] > max) {
                max = a[j][i];
            }
        }
        col[i] = max;
    }
}

void _print_array(int a[100], int n) {
	int i;
	for(i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
}

void minimum(int a[100], int m, int min[2]){
	int i, j;
	min[0] = INT_MAX;
	for(i=0; i<m; i++) {
		if(min[0] > a[i]) {
			min[0] = a[i];
			min[1] = i;
		}
	}
}

void maximum(int a[100], int m, int max[2]) {
	int i, j;
	max[0] = INT_MIN;
	for(i=0; i<m; i++) {
		if(max[0] < a[i]) {
			max[0] = a[i];
			max[1] = i;
		}
	}
}

int main() {
	int m, n;
	printf("\nNumber of rows: ");
	scanf("%d", &m);
	printf("\nNumber of columns: ");
	scanf("%d", &n);

	printf("\nMatrix:\n");
	int i, j;
	int a[100][100];
	for(i=0; i<m; i++) {
		for(j=0; j<n; j++) {
			scanf("%d", &a[i][j]);
		}
	}

	int row[100], col[100];

	_calculate_row_col(a, m, n, row, col);

	int max[2];
	maximum(row, m, max);
	int min[2];
	minimum(col, n, min);

	if(max[0] == min[0]) {
		printf("\nSaddle point exists at (%d, %d)", max[1]+1, min[1]+1);
	} else {
		printf("\nSaddle point does not exists!");
	}

	return 0;
}
