#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//définition de la structure poly avec exp qui est un entier strictement positif et coef un nombre réel
typedef struct Poly{
    int exp;
    float coef;
    struct Poly * suivant;
}Poly;

Poly * creerMonome(float coef,int exp);
Poly * ajouterMonome(Poly * monPoly,float coef,int exp);
Poly * copierPolynome(Poly * monPoly);
Poly * somme(Poly * monpoly1,Poly * monpoly2);
void afficherpoly(Poly * monpoly);
float evaluation_polynome(Poly * monpoly,float x);
Poly * deriverPolynome(Poly * monPoly);
Poly * derive_n(Poly * monpoly,int n);
Poly * multiplier1(Poly* monpoly,float coef,int exp);
Poly * multiplier2(Poly * poly1,Poly * poly2);
