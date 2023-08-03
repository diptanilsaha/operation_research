// Vogel's Approximation Method - Transportation Method

#include <stdio.h>
#include <stdlib.h>

void _print_matrix(int m[100][100], int o, int d) {
	int i, j;
	printf("\nMatrix:\n");
	for(i=0; i<o; i++) {
		for(j=0; j<d; j++) {
			printf("\t%d", m[i][j]);
		}
		printf("\n");
	}
}

void _calculate_penalty(int m[100][100], int o, int d, int row[100], int col[100]) {
    int i, j;
    printf("\nCalculating Penalty...");
    int min, smin;
    for(i=0; i<o; i++) {
        min = INT_MAX, smin = INT_MAX;
        for(j=0; j<d; j++) {
            if(m[i][j] < min) {
                smin = min;
                min = m[i][j];
            }
            if(m[i][j] < smin && m[i][j] != min) {
                smin = m[i][j];
            }
        }
        col[i] = smin - min;
    }

    for(i=0; i<d; i++) {
        min = INT_MAX, smin = INT_MAX;
        for(j=0; j<o; j++) {
            if(m[j][i] < min) {
                smin = min;
                min = m[j][i];
            }
            if(m[j][i] < smin && m[j][i] != min) {
                smin = m[j][i];
            }
        }
        row[i] = smin - min;
    }
}

void _print_array(int a[100], int n) {
	int i;
	for(i=0; i<n; i++) {
		printf("%d ", a[i]);
	}
}

void _delete_row_col(int m[100][100], int o, int d, int row, int col) {
	// if delete col, row = -1
	// if delete row, col = -1
	int i, j;
	if(row != -1) {
		for(i=row+1; i<o; i++) {
			for(j=0; j<d; j++) {
				m[i-1][j] = m[i][j];
			}
		}
	} else if(col != -1){
		for(j=col+1; j<d; j++) {
			for(i=0; i<o; i++) {
				m[i][j-1] = m[i][j];
			}
		}
	}
}

void _delete_array(int a[100], int n, int i) {
	int j;
	for(j=i+1; j<n; j++) {
		a[j-1] = a[j];
	}
}

void _matrix_min(int m[100][100], int o, int d, int a[3]) {
	int i, j;
	a[0] = INT_MAX;
	a[1] = 0;
	a[2] = 0;
	for(i=0; i<o; i++) {
		for(j=0; j<d; j++) {
			if(a[0] > m[i][j]) {
				a[0] = m[i][j];
				a[1] = i; //origin
				a[2] = j; //destination
			}
		}
	}
}

int main() {
	int m[100][100] = {0};
	int o, d; // origin and destination
	int s[100], r[100]; // supply and requirements
	int sa = 0, ra = 0; // supply add and requirements add
	int i, j;

	printf("\nNumber of Origins: ");
	scanf("%d", &o);

	printf("\nNumber of Destination: ");
	scanf("%d", &d);

	printf("\nMatrix: \n");
	for(i=0; i<o; i++) {
		for(j=0; j<d; j++) {
			scanf("%d", &m[i][j]);
		}
	}

    int row[100], col[100];

    _calculate_penalty(m, o, d, row, col);

    printf("\nRow: ");
    _print_array(row, d);

    printf("\nCol: ");
    _print_array(col, o);

	/*printf("\nSupply: ");
	for(i=0; i<o; i++) {
		scanf("%d", &s[i]);
		sa = sa + s[i];
	}

	printf("\nRequirements: ");
	for(i=0; i<d; i++) {
		scanf("%d", &r[i]);
		ra =  ra + r[i];
	}

	if (sa != ra) {
		printf("\nThe Matrix is unbalanced.");
		if (sa > ra) {
			r[d] = sa - ra;
			d++;
		} else {
			s[o] = ra - sa;
			o++;
		}
	}
	_print_matrix(m, o, d);
	printf("\nSupply: ");
	_print_array(s, o);
	printf("\nRequirements: ");
	_print_array(r, d);

	int a[3] = {0};
	int cost = 0;
	while(1) {
		_matrix_min(m, o, d, a);
		i = a[1];
		j = a[2];
		if(s[i] > r[j]) {
			cost = cost + (a[0]*r[j]);
			s[i] = s[i] - r[j];
			_delete_row_col(m, o, d, -1, j);
			_delete_array(r, d, j);
			d--;
		} else if(s[i] < r[j]) {
			cost = cost + (a[0]*s[i]);
			r[j] = r[j] - s[i];
			_delete_row_col(m, o, d, i, -1);
			_delete_array(s, o, i);
			o--;
		} else {
			cost = cost + (a[0]*s[i]);
			_delete_row_col(m, o, d, i, -1);
			_delete_array(s, o, i);
			o--;
			_delete_row_col(m, o, d, -1, j);
			_delete_array(r, d, j);
			d--;
		}


		if(o==0 || d==0) {
			break;
		}
	}
	printf("\nCost: %d", cost);*/
	return 0;
}
