#include"fonct_matrice.h"

int main()
{
    Matrice *A;
    Matrice *B,*C,*Sum,*prod;
    int n;
    int l,c;

	printf("Donnez la dimension de la matrice carrée:\n");
    printf("dimension: ");     
	scanf("%d",&n);	

	A=allouerMatrice(n,n);
	printf("Entrez les éléments de la matrice\n\n");
	Mat_remplirMatrice(A);
	printf("\n");
	Mat_afficherMat(A); 
	printf("\n");
    
	afficherpoly(polynome_caracteristique(A));
    return 0;
}