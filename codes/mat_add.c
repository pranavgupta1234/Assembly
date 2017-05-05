#include <stdio.h>
#include <stdlib.h>

void read_matrix(int** matrix,int n,int m);
void display_matrix(int** matrix,int n,int m);
void add_matrix(int** matrix1,int** matrix2,int** matrix3,int n,int m);
void alloc(int** matrix,int n,int m);

int main(){

	//int i,j;
	int n,m;
	int** matrix_f,matrix_s,matrix_a;
	int val;

	printf("Enter the number of rows :: ");
	scanf("%d",&n);

	printf("Enter the number of columns :: ");
	scanf("%d",&m);

	printf("Enter first matrix :: \n");
	read_matrix(matrix_f,n,m);
	printf("Enter second matrix :: \n");
	read_matrix(matrix_s,n,m);

	alloc(matrix_a,n,m);

	add_matrix(matrix_f,matrix_s,matrix_a,n,m);

	printf("First matrix is :: \n");
	display_matrix(matrix_f,n,m);
	printf("Second matrix is :: \n");
	display_matrix(matrix_s,n,m);
	printf("Addition matrix is :: \n");
	display_matrix(matrix_a,n,m);

	return 0;
}

void read_matrix(int** matrix,int n,int m){

	matrix = (int**)malloc(n*sizeof(int*));

	for(int i=0 ; i<m ; i++){
		matrix[i] = (int*)malloc(m*sizeof(int));
	}

	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<m ; j++){
			printf("[%d][%d] : ",i,j);
			scanf("%d",&matrix[i][j]); 
		}
	}
}

void display_matrix(int** matrix,int n,int m){

	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<m ; j++){
			printf("%d ",matrix[i][j]); 
		}
		printf("\n");
	}

}

void add_matrix(int** matrix1,int** matrix2,int** matrix3,int n,int m){

	for(int i=0 ; i<n ; i++){
		for(int j=0 ; j<m ; j++){
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j]; 
		}
		printf("\n");
	}	

}

void alloc(int** matrix,int n,int m){

	matrix = (int**)malloc(n*sizeof(int*));

	for(int i=0 ; i<m ; i++){
		matrix[i] = (int*)malloc(m*sizeof(int));
	}

}