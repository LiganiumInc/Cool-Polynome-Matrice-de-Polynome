#include"fonct_matrice.h"

Matrice* allouerMatrice(int l,int c){/*allouer une matrice de l lignes et c colonnes*/

	Matrice * A;
	int i;
	A=(Matrice*)malloc(sizeof(Matrice));

	A->n=l;
    A->m=c;
	A->P=(Poly**)malloc(l*sizeof(Poly*));

	for(i=0;i<l;i++) {

		A->P[i]=(Poly *)malloc(c*sizeof(Poly ));

	}
	return A;
}

void Mat_remplirMatrice(Matrice * A){/*remplie la matrice A par saisie au clavier*/

	int i,j;
    float temp;

	for(i=0;i<A->n;i++)
	{

		for(j=0;j<A->m;j++){
			
			scanf("%f",&temp);
            A->P[i][j] = *(creerMonome(temp,0));

        }

	}
}

void Mat_afficherMat(Matrice *A){/*affiche la matrice A*/

	int i,j;

	for(i=0;i<A->n;i++){

		for(j=0; j < A->m;j ++){

			afficherpoly(&(A->P[i][j]));
			printf("\t\t");

		}

		printf("\n");
	}
}

void libererMatrice(Matrice *A){/*libère l'espace mémoire occupé par la matrice par la matrice*/

	int i;

	for(i=0;i<A->n;i++)
        free(A->P[i]);

}

int deMemeDim(Matrice *A,Matrice *B){/*teste si les matrices A et B sont de meme dimension*/

	if(A->n == B->n && A->m == B->m)
        return 1;
	else
		return 0;

}

Matrice* Mat_add(Matrice *A,Matrice *B){/*renvoie la matrice issue de l'addition de A et de B*/

	int i,j;
	Matrice *C;

	if(!deMemeDim(A,B))
        return NULL;

	C=allouerMatrice(A->n,A->m);

	for(i=0;i<A->n;i++){

		for(j=0;j<A->m;j++){

			C->P[i][j]=*(somme(&(A->P[i][j]),&(B->P[i][j])));

		}
	}
	return C;
}

Matrice *Mat_prod(Matrice *A,Matrice *B){/*renvoie le produit de A et B,
	renvoie NULL si l'opération n'est pas possible*/

	int i,j,k;
	Matrice *C;

	if(A->m!=B->n)
        return NULL;

	C=allouerMatrice(A->n,B->m);

	for(i=0;i<C->n;i++){

		for(j=0;j<C->m;j++){

			for(k=0;k<A->m;k++){

			C->P[i][j]= *(somme(&(C->P[i][j]), multiplier2(&(A->P[i][k]), &(B->P[k][j]))));

			}
		}
	}	
	return C;
}

//calcul du déterminant d'une matrice de polynome
// Le principe est tres simple, il s'agit de developper le determinant
    // suivant la derniere colonne. Cet algorithme est evidemment recursif
    // puisqu'il faut les sous-determinants
    // 
    // Exemple sur une matrice 4x4 :
    // 
    // | *  *  *  a1 |
    // | *  *  *  a2 |
    // | *  *  *  a3 |
    // | *  *  *  a4 |
    // 
    // A chaque coefficient de la derniere colonne, on associe une sous-dertermiant ("sd") :
    // (notation : '#')
    // 
    // ds1 : | *  *  *  a1 |      ds2 : | #  #  #  a1 |
    //       | #  #  #  a2 |            | *  *  *  a2 |
    //       | #  #  #  a3 |            | #  #  #  a3 |
    //       | #  #  #  a4 |            | #  #  #  a4 |
    // 
    // ds3 : | #  #  #  a1 |      ds4 : | #  #  #  a1 |
    //       | #  #  #  a2 |            | #  #  #  a2 |
    //       | *  *  *  a3 |            | #  #  #  a3 |
    //       | #  #  #  a4 |            | *  *  *  a4 |
    // 
    // La formule du calcul du determinant par les cofacteurs est donnee par :
    // 
    //     det = a4.ds4 - a3.ds3 + a2.ds2 - a1.ds1
    //
    //     (notons l'alternance des signes)
    // 
    // On doit calculer les "ds", donc creer les matrices correspondants, et calculer
    // par recurrence leurs determinants. On remarque facilement que les matrices se
    // ressemblent à (toujours) 2 lignes pres. Donc pour eviter de toujours les recalculer,
    // on les initilise de facon "incrementale".
    // 
    
Poly * determinant(Matrice * M){
	// calcul d'un determinant avec les cofacteurs
	// la complexite est en n!

	Matrice * cof=NULL; // matrice qui represente un cofacteur
  	Poly *   det=creerMonome(0,0); // le determinant

  	int      i,j,k=M->n; // <i> pour les colonnes// <j> pour les lignes

  	Poly * sgn=creerMonome(1,0);//représente le signe (1 ou -1)

	Poly * B,*C,*D;

	// cas trivial d'une matrice 1x1
	if(k == 1)
	{
		return &(M->P[0][0]);
	}

	// cas trivial d'une matrice 2x2
	// 
	// | a b |
	// | c d |  = a.d - c.b
	// 

	else if(k == 2)
	{
		B=multiplier2(&(M->P[0][0]), &(M->P[1][1]));

		C=multiplier2(&(M->P[0][1]), &(M->P[1][0]));

		D=creerMonome(-1,0);

		C=multiplier2(C,D);

	return somme(B,C);
	}

	else{
		// on cree une matrice temporaire pour le calcul des cofacteurs
		cof = allouerMatrice(k-1,k-1);

		for(j=0;j<k-1;j++)
		{
			for(i=0;i<k-1;i++)
			{

			cof->P[j][i] = M->P[j][i];

			}

		}

		// on balaye la derniere colonne (de bas en haut)
		for(j=k-1;j>=0;j--){
			// on modifie la bonne ligne pour la matrice des cofacteurs

			if(j < k-1 ){

				for(i=0;i<k-1;i++){
					cof->P[j][i] = M->P[j+1][i];
				}
			}
			// la recurrence en personne :
			//En langage sans polynome: det += sgn * mat[j][n-1] * determinant(cof);
			//Et avec les polynomes on procède pas à pas

			B=multiplier2(sgn, &(M->P[j][k-1]));

			C=multiplier2(B, determinant(cof));

			det=somme(det,C);
			
			// changement de signe (l'alternance remarquee)
			sgn = multiplier2(sgn, creerMonome(-1,0));//multiplication par -1
		}
		
	return det;
	}
}


//Détermination du polynome caractéristique
/*Le polynôme caractéristique d'une matrice carrée A ∈ R n×n est le déterminant de A−xIn ,
où I n est la matrice identité n × n . Pour des rappels sur ces notions, aller voir :
http://fr.wikipedia.org/wiki/Polynôme_caractéristique*/

Poly * polynome_caracteristique(Matrice *A){

	Matrice * M=NULL;
	Matrice * xIn=allouerMatrice(A->n,A->m);
	Poly * polcarac=NULL;
	int i,j;
	
	/*on crée la matrice -xIn de meme dimension que A*/
	for(i=0;i<A->n;i++)
		for(j=0;j<A->n;j++){
			if(i==j)
				xIn->P[i][j]=*(creerMonome(-1,1));
			else
				xIn->P[i][j]=*(creerMonome(0,0));
		}
	
	
	/*calcul de la matrice A-xIn*/

	M=Mat_add(A,xIn);

	printf("Matrice A-xIn:\n");
	Mat_afficherMat(M);
	printf("\n");

	//le polynome caracteristique c'est le déterminant de la matrice A-xIn
	printf("Le polynome caractéristique est:\n");
	polcarac=determinant(M);

	return polcarac;

}

	