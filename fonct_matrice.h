#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"poly.h"

typedef struct matricedepolynome{
	int n, m; /*n->lignes, m->colonnes*/
  	Poly **P;/*Matrice*/
}Matrice;

Matrice* allouerMatrice(int l,int c);
void Mat_remplirMatrice(Matrice * A);
void Mat_remplirMatrice(Matrice * A);
void Mat_afficherMat(Matrice *A);
void libererMatrice(Matrice *A);
int deMemeDim(Matrice *A,Matrice *B);
Matrice* Mat_add(Matrice *A,Matrice *B);
Matrice *Mat_prod(Matrice *A,Matrice *B);
Poly * polynome_caracteristique(Matrice *A);