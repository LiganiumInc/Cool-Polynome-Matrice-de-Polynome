Opérations sur les polynomes représentés par des listes chainées et détermination de polynome caractéristique d'une matrice--------------------

-----------------------------------------------------------
By Bernardin LIGAN aka Liganium
-----------------------------------------------------------

Bonjours chers amis.
Ce projet est divisé en deux volets

Volet 1:

Vous trouverez dans le premier volet un ensemble de fonctions qui permettent d'effectuer des opérations sur les polynomes. Je représente un polynome comme une liste chainée dont chaque élément est un monome. 

Structure qui représente le polynome:

typedef struct Poly{
    int exp;
    float coef;
    struct Poly * suivant;
}Poly;

Les fonctions implémentées permettent de faire la somme, le produit, la dérivée à l'ordre 1 et à l'ordre n. On peut également avoir la valeur d'un polynome pour une valeur x donnée.

Compilation:gcc fonct_poly.c main.c -o poly_liste -lm

Volet 2:

L'objectif du deuxieme volet est de déterminer le polynome caractéristique d'une matrice donnée.

/*Le polynôme caractéristique d'une matrice carrée A ∈ R n×n est le déterminant de A−xIn ,
où I n est la matrice identité n × n . Pour des rappels sur ces notions, aller voir :
http://fr.wikipedia.org/wiki/Polynôme_caractéristique*/

Pour cela, j'ai représenté une matrice avec la structure suivante:

typedef struct matricedepolynome{
	int n, m; /*n->lignes, m->colonnes*/
  	Poly **P;/*Matrice*/
}Matrice;

Ainsi, chaque élément de la matrice est un polynome. Les éléments qui sont des constantes sont donc des monomes d'expoxant 0. 
Le fichier fonct_matrice.c rassemble un certain nombre de fonctions permettant de faire des opérations telles que la somme, le produit, le déterminant de matrice ainsi que la détermination du polynome caractéristique d'une matrice donnée. 
Ces fonctions utilisent les fonctions précédentes de calculs sur les polynomes puisque chaque élément d'une matrice est représenté par un polynome.

Compilation: gcc fonct_poly.c fonct_matrice.c testmat.c-o testmat -lm


Références:

1- http://langage-info.blogspot.com/2014/06/exercice-gestion-des-polynomes-avec-les.html

2- Url     : http://codes-sources.commentcamarche.net/source/36387-determinants-gauss-cofacteurs


