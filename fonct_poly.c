#include"poly.h"

Poly * creerMonome(float coef ,int exp){

    Poly * P;
    if (exp < 0) { // il n y a pas de monome ayant une puissance negative
        printf("erreur : puissance negative");

        return NULL;
    }
    else {

        P=(Poly *)malloc( sizeof(Poly) );
        if(P==NULL){

            return NULL;

        }
        else{

            P->coef = coef;
            P->exp = exp;
            P->suivant = NULL;

            return P;
        }  
    }
}

//Écrire une fonction qui ajoute un monôme a la liste du polynôme , en traite tous les cas possibles .
// le Polynôme doit être trié toujours en exposant décroissant
Poly * ajouterMonome(Poly * monPoly,float coef,int exp){

    Poly * P=creerMonome(coef,exp);
    Poly * cur=monPoly;

    if (monPoly==NULL) 
        return P; // si monPoly est nul , alors la somme serait just un monome

    else if(exp > monPoly->exp) {

            P->suivant=monPoly;
            return P;

    }
    else if (monPoly->suivant==NULL) { /*si le polynome est constitué d'un seul monome*/
    
        if(cur->exp ==exp) 
            cur->coef += coef;
        else{

            P->suivant=cur->suivant;
            cur->suivant=P;

        }

        return monPoly;
    }  
    else{

        while(cur->suivant != NULL && cur->suivant->exp > exp ) 
                    cur=cur->suivant;
        if(cur->suivant != NULL && cur->suivant->exp ==exp) 
            cur->suivant->coef += coef;
        else{

            P->suivant=cur->suivant;
            cur->suivant=P;

        }

        return monPoly;

    }
}


//copier un polynome
Poly * copierPolynome(Poly * monPoly){

    Poly * copie=NULL,*R =monPoly;

    while(R !=NULL ) { 

        copie =ajouterMonome(copie,R->coef,R->exp);
        R = R->suivant;

    }

    return copie;
}

//faire la somme de deux polynomes
Poly* somme(Poly * monpoly1, Poly * monpoly2){

    Poly* somme=copierPolynome(monpoly1), *cur=monpoly2;

    while(cur != NULL){

        somme=ajouterMonome(somme, cur->coef, cur->exp);

        cur=cur->suivant;

    }

    return somme;
}
//longueur du polynome
int poly_taille(Poly *L){

    int len=0;
    Poly *cur=L;

    while (cur != NULL) {

        cur = cur->suivant;
        len++;

    }

    return len;
}

//afficher un polynome
void afficherpoly(Poly * monpoly){

    while(monpoly)
    {

    
        if(monpoly->exp != 0){

            if(monpoly->suivant){

                printf("%.2fx^%d ", monpoly->coef, monpoly->exp);

                if(monpoly->suivant->coef >= 0)
                    printf(" + ");
                
            }  
            else{

                if(monpoly->coef > 0)
                    printf(" + ");

                printf("%.2fx^%d", monpoly->coef, monpoly->exp);
            }
	            

        }
        else
            printf("%.2f", monpoly->coef);

        monpoly = monpoly->suivant;
    }
}

//évaluer polynome
float evaluation_polynome(Poly * monpoly,float x){

    float valeur=0;
    Poly * cur=monpoly;

    while(cur!=NULL){

        valeur +=cur->coef*pow(x,cur->exp);
        cur=cur->suivant;

    }

    return valeur;
}

//dériver à l'ordre 1
Poly * deriverPolynome(Poly * monPoly){

    Poly * derive=copierPolynome(monPoly), *cur=derive;

    if(cur->exp==0){//si le polynome est une constante

       printf("Le polynome étant constant, sa dérivée est nulle\n");
       return creerMonome(0,0);

    }
    else{

        while(cur != NULL){

            cur->coef *=cur->exp;
            cur->exp--;

            if(cur->suivant!= NULL && cur->suivant->exp==0){

                cur->suivant = NULL;
                break;

            }
            else 
                cur =cur->suivant;
        }

    return derive;
    }
    
} 

//dériver d'ordre n
Poly * derive_n(Poly * monpoly,int n){

    int i;
    Poly * derive=copierPolynome(monpoly);

    for(i=0;i<n;i++){

         derive=deriverPolynome(derive);

         if(derive->coef==0 && derive->exp==0)
         break;

    }
       
    return derive;
}

//multiplier un polynome par un monome
Poly * multiplier1(Poly* monpoly,float coef,int exp){

    Poly * P=copierPolynome(monpoly), *cur=P;

    while(cur!=NULL){

        cur->coef *= coef;
        cur->exp  += exp;
        cur=cur->suivant;

    }

    return P;
}

//multiplication de deux polynomes
Poly * multiplier2(Poly * poly1,Poly * poly2){
    
    Poly * P=NULL,*S=NULL,*cur=poly2;

    while(cur != NULL){

        P=multiplier1(poly1,cur->coef,cur->exp);

        while(P!=NULL){

            S=ajouterMonome(S,P->coef,P->exp);
            P=P->suivant;
            
        }
        cur=cur->suivant;
        
    }
    return S;
}