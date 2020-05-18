#include"poly.h"

int main()
{
    float valeur;
    Poly * polynome1=NULL, *polynome2=NULL, * derive=NULL,*derive1=NULL,*som=NULL,*mult=NULL;
    int ordre=3;

    polynome1=ajouterMonome(polynome1,9,2);
    polynome1=ajouterMonome(polynome1,4,1);
    polynome1=ajouterMonome(polynome1,2,0);

    printf("Polynome1: ");
    afficherpoly(polynome1);

    valeur=evaluation_polynome(polynome1,0);
    printf("\n\nLe polynome1 prend la valeur %f en 0",valeur);

    polynome2=ajouterMonome(polynome2,4,3);
    polynome2=ajouterMonome(polynome2,1,2);
    polynome2=ajouterMonome(polynome2,12,1);
    polynome2=ajouterMonome(polynome2,1,0);

    printf("\n\nPolynome2: ");
    afficherpoly(polynome2);

    som=somme(polynome1,polynome2);
    printf("\n\nSomme des deux polynomes: ");
    afficherpoly(som);

    mult=multiplier2(polynome1,polynome2);
    printf("\n\nProduit des deux polynomes:\n");
    afficherpoly(mult);

    printf("\n\nLa dérivée à l'ordre 1 du polynome2 est:\n ");
    derive=deriverPolynome(polynome2);
    afficherpoly(derive);

    return 0;

}
