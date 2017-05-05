#include <stdio.h>
#include <stdlib.h>

int n,m;

void read_matrix(int matrix[n][m],int n,int m);
void display_matrix(int matrix[n][m],int n,int m);
void add_matrix(int matrix1[n][m],int matrix2[n][m],int matrix3[n][m],int n,int m);
void alloc(int matrix[n][m],int n,int m);

int main(){

	int val;

	printf("Enter the number of rows :: ");
	scanf("%d",&n);

	printf("Enter the number of columns :: ");
	scanf("%d",&m);

	int matrix_f[n][m],matrix_s[n][m],matrix_a[n][m];

	printf("Enter first matrix :: \n");
	read_matrix(matrix_f,n,m);
	printf("Enter second matrix :: \n");
	read_matrix(matrix_s,n,m);

	add_matrix(matrix_f,matrix_s,matrix_a,n,m);

	printf("First matrix is :: \n");
	display_matrix(matrix_f,n,m);
	printf("Second matrix is :: \n");
	display_matrix(matrix_s,n,m);
	printf("Addition matrix is :: \n");
	display_matrix(matrix_a,n,m);

	return 0;
}

void read_matrix(int matrix[n][m],int n,int m){

	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<m ; j++){
			printf("[%d][%d] : ",i,j);
			scanf("%d",&matrix[i][j]); 
		}
	}
}

void display_matrix(int matrix[n][m],int n,int m){

	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<m ; j++){
			printf("%d ",matrix[i][j]); 
		}
		printf("\n");
	}

}

void add_matrix(int matrix1[n][m],int matrix2[n][m],int matrix3[n][m],int n,int m){

	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<m ; j++){
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j]; 
		}
		printf("\n");
	}	

}
