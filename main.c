#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"
Catalogue* arbre=NULL;

//--------------------------------------MAIN------------------------------------------------//
int main(){
    DATE.aa=2021;DATE.hh=15;DATE.jj=10;DATE.mm=11;DATE.mn=46;DATE.ss=14;
    Acheteur acheteur=initialiserUser();
    Article a;

    FILE *fichier=fopen("produit.txt","r");
    if(fichier){
       while(!feof(fichier)){
            fscanf(fichier,"%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%f\t%f\t%d\n",&a.num,a.nomCommun,a.nomCommercial,a.codeArticle,a.categoriePle,a.sousCategorie,a.marque,a.codeBarre,a.numSerie,&a.TVA,&a.prixVente,&a.quantite);
            ajouterCatalogue(&arbre,a);
       }
        fclose(fichier);
    }
    int quitter=1;
    while(quitter){
        system("cls");
        afficherInfoAcheteur(acheteur);
        switch(menuPrincipal())
            {
            case 1: //Consulter catalogue
                system("cls");
                consulterCatalogue();
                system("PAUSE");
                break;
            case 2:  //Consulter Panier
                system("cls");
                acheteur=ConsulterPanier(acheteur);
                break;
            default://Fermer
                quitter=0;
                break;
            }
    }
    system("cls");
    printf("\n\n\n\t\t\t\t%s\n\n",text[10]);
    return 0;
}

//------------------------------------------FICHIER--------------------------------------------//
Acheteur ConsulterPanier(Acheteur a){
    int quitter=1;
    printf("\t\t\t\tOPERATIONS DU PANIER\n");
    while(quitter){
            system("cls");
        switch(menuPanier()){
            case 1:
                system("cls");
                a.monPanier = ajouterArticle(a.monPanier);
                system("PAUSE");
                break;
            case 2:
                system("cls");
                a.monPanier = supprimerArticle(a.monPanier);
                system("PAUSE");
                break;
            case 3:
                system("cls");
                afficherPanier(a);
                system("PAUSE");
                break;
            case 4:
                system("cls");
                afficherHistorique(a);
                system("PAUSE");
                break;
            case 5:
                system("cls");
                a=facturation(a);
                system("PAUSE");
                break;
            default:
                quitter=0;
                break;
        }
    }
    return a;
}

void afficherPanier(Acheteur a){
    if(a.monPanier.articles==NULL)
        printf("%s\n",text[6]);
    else{
            ListeArticle *courant=a.monPanier.articles;
        printf("%s\n",text[7]);
        printf("_______________________________________________________________________________________\n");
        while(courant!=0){
            afficherArticle(courant->article,courant->quantite);
            courant=courant->suivant;
        }
        printf("________________________________________________________________________________________\n");
        printf("\t\t\t\t\t\t\t\t\tTOTAL:\t%.1f TTC\n\n\n",a.monPanier.montantTotal);
    }
}
void afficherArticle(Article article,int quantite){
        printf("%d\t%s\t%s\t\t%d\t%.1f\t\t%.1f\n",article.num,article.codeArticle,article.nomCommun,
        quantite,article.prixVente+((article.prixVente*article.TVA)/100),article.prixVente+((article.prixVente*article.TVA)/100)*quantite);
}
Acheteur  initialiserUser(){
    Acheteur acheteur;
    acheteur.nomAcheteur=infoUser[0];
    Coordonnees c;
    c.adressePost=infoUser[4];
    c.ville=infoUser[5];
    c.mail=infoUser[1];
    acheteur.coordAcheteur=c;
    Panier p;
    p.articles=NULL;
    p.historiqueOperation=NULL;
    p.montantTotal=0.0;
    acheteur.monPanier=p;
    return acheteur;
}
void afficherInfoAcheteur(Acheteur a){
    printf("\n\n\t\tPROFIL\n\n");
    printf("\tNOM:\t\t%s\n",a.nomAcheteur);
    afficherCoordonnees(a.coordAcheteur);
}
void afficherCoordonnees(Coordonnees c){
    printf("\tMAIL:\t\t%s\n",c.mail);
    printf("\tVILLE:\t\t%s\n",c.ville);
    printf("\tPOSTAL:\t\t%s\n\n\n",c.adressePost);
}
int menuPrincipal(){
    int choix=-1;
    printf("\t\t\t\t%s\n",text[0]);
    printf("\t\t\t\t\t%s\n\n\n",text[1]);
    printf("\t\t\t\t1- %s\n\t\t\t\t2- %s\n",text[2],text[3]);
    printf("\t\t\t\t0- %s\n\n\n",text[4]);
        do
        {
            printf("\t\t\t\t%s:  ",text[5]);
            scanf("%d",&choix);
            if(choix<0 || choix>2)
                printf("%s\n",error[0]);
        }
        while(choix<0 || choix>2);
    return choix;
}
int menuPanier(){
    int choix=-1;
     printf("\n\n\n\t\t\t\tOPERATIONS DU PANIER\n");
     printf("\n\n\t\t\t1- Ajout d'un article dans panier\n\t\t\t2- Suppression d'un article du panier\n");
        printf("\t\t\t3- Afficher les articles du panier\n");
        printf("\t\t\t4- Affichage de l'historique des operations\n");
        printf("\t\t\t5- Passez a la facturation\n");
        printf("\t\t\t0- Quitter le panier\n\n");
    do
    {
        printf("\t\t\tChoisir une operation: ");
        scanf("%d",&choix);
        if(choix<0 || choix>5)
            printf("ERREUR DE SAISIE. Reessayez !\n");
    }while(choix<0 || choix>5);
    return choix;
}
Panier ajouterArticle(Panier p){
    printf("\t\t\t\t\t\tLES PRODUITS DU CATALOGUE\n");
    printf("\t\t\t\t\t\t\t__________\n\n");
    afficherCatalogue(arbre);
    printf("\t\t\CHOISIR LE PRODUIT A AJOUTER\n");
    int num=-1,q=-1;
    do{
            printf("Choisir le numero  de  l'article a ajouter :    ");
            scanf("%d",&num);
            printf("Donner la quantite  de  l'article a ajouter :   ");
            scanf("%d",&q);
            if(num<=0 || q<=0)
                printf("%s\n",error[0]);
    }while(num<=0 || q<=0);
    if(existeArticleDansArbre(arbre,num,q)){
             Article tmp=existeArticle(num,q);
    ListeArticle *a=malloc(sizeof(*a));
    a->quantite=q;
    a->suivant=NULL;
    strcpy(a->article.categoriePle,tmp.categoriePle);
    strcpy(a->article.codeArticle,tmp.codeArticle);
    strcpy(a->article.codeBarre,tmp.codeBarre);
    a->article.dateExp=tmp.dateExp;
    a->article.dateFab=tmp.dateFab;
    strcpy(a->article.marque,tmp.marque);
    strcpy(a->article.nomCommercial,tmp.nomCommercial);
    strcpy(a->article.nomCommun,tmp.nomCommun);
    a->article.num=num;
    strcpy(a->article.numSerie,tmp.numSerie);
    a->article.prixVente=tmp.prixVente;
    a->article.quantite=q;
    strcpy(a->article.sousCategorie,tmp.sousCategorie);
    a->article.TVA=tmp.TVA;
    if(a!=NULL){
            a->suivant=p.articles;
            p.articles=a;
            p.montantTotal+=a->quantite*(a->article.prixVente+((a->article.prixVente*a->article.TVA)/100));
            p.historiqueOperation=ajouterHistorique(p.historiqueOperation,"Ajout produit");
        }
    }
    else printf("\nARTICLE N'EXISTE PAS OU QUANTITE INSUFFISANTE! \n Reessayer !");
    return p;
}
Panier supprimerArticle(Panier p){
    afficherAllArticle(p.articles);
    if(p.articles!=0)
    {int num=-1;
    printf("Choisir le numero  de  l'article a supprimer :");
    do{
            scanf("%d",&num);
            if(num<=0)
                printf("%s\n",error[0]);
    }while(num<=0);
    if(existeArticlePanier(p,num)){
        p.articles=supprimerArticleInListe(p.articles,num);
        p.montantTotal=montant(p.articles);
        p.historiqueOperation=ajouterHistorique(p.historiqueOperation,"Suppression article");
    }
    else printf("%s. Ressayez a nouveau !\n",error[2]);}
    else printf("%s\n",text[6]);
    return p;
}
void afficherHistorique(Acheteur a){
     if(a.monPanier.historiqueOperation==0)
        printf("%s\n",text[9]);
    else{
            Operation *courant=a.monPanier.historiqueOperation;
        printf("%s\n",text[8]);
        printf("__________________________________________________________________________\n");
        while(courant!=0){
            printf("%d\t\t%s\t\t\t",courant->numOperation,courant->nomOperation);
            afficherDate(courant->dateOperation);
            courant=courant->suivant;
        }
        printf("__________________________________________________________________________\n");
    }
}
void afficherDate(DateHeure d){
    printf("%d-%d-%d %d:%d:%d\n",d.aa,d.mm,d.jj,d.hh,d.mm,d.ss);
}
Operation* ajouterHistorique(Operation *o,char nom[TAILLE_MAX]){
    Operation *nouveau=malloc(sizeof(*nouveau));
    if(nouveau!=NULL){
    nouveau->nomOperation=nom;
    nouveau->dateOperation=DATE;
    nouveau->numOperation=++nombreHist;
    if(o==0){
        nouveau->suivant=0;
        o=nouveau;
    }
    else{
         nouveau->suivant=o;
         o=nouveau;
    }
    }
    return o;
}
void afficherAllArticle(ListeArticle *a){
    if(a==NULL)
        printf("%s\n",text[6]);
    else{
        ListeArticle *courant=a;
        printf("%s\n",text[7]);
        printf("__________________________________________________________________________\n");
        while(courant!=0){
            afficherArticle(courant->article,courant->quantite);
            courant=courant->suivant;
        }
        printf("__________________________________________________________________________\n");
    }
}
int existeArticlePanier(Panier p,int num){
    ListeArticle* a=p.articles;
     while(a!=0){
        if(a->article.num==num) return 1;
        else  a=a->suivant;
    }
    return 0;
}
ListeArticle* supprimerArticleInListe(ListeArticle* a,int num){
    if(a!=NULL){
         if(a->article.num==num){
            free(a);
            a=NULL;
            printf("%s\n",error[1]);
            }
    else{
     ListeArticle* courant=a;
     int trouve=0;
     while(courant!=0 && trouve==0){
        if(courant->article.num!=num)
            courant=courant->suivant;
        else{
            trouve==1;
            ListeArticle* sup=courant;
            courant=courant->suivant;
            free(sup);
          }
        }
        if(trouve) printf("%s\n",error[1]);
        else printf("%s\n",error[2]);
    }
    }
    else printf("%s\n",error[3]);
    return a;
}
float montant(ListeArticle *a){
    float sum=0;
    while(a!=0){
        sum+=a->quantite*(a->article.prixVente+((a->article.prixVente*a->article.TVA)/100));
        a=a->suivant;
    }
    return sum;
}
Acheteur facturation(Acheteur a){
    afficherInfoAcheteur(a);
    printf("\t\t\t\t\t\tFACTURE PRE-EDITEE\n\n\t");
    afficherAllArticle(a.monPanier.articles);
    printf("\t\t\t\t\t\t\t\t\t\t%s : %.2f TTC\n\n",text[13],montant(a.monPanier.articles));
    if(a.monPanier.articles!=0){
         printf("%s (1)- Oui   (2)- Non\n",text[14]); int choix=-1;
    do{
         scanf("%d",&choix);
         if(choix!=1 && choix!=0)
            printf("%s",error[0]);
    }while(choix!=1 && choix!=0);
    if(choix){
            system("cls");
        afficherInfoAcheteur(a);
        printf("\t\t\t\tFACTURE NUMERO %d\n\n",rand()%600);
        afficherAllArticle(a.monPanier.articles);
        printf("\t\t\t\t\t\t\t%s : %.2f TTC\n\n",text[13],montant(a.monPanier.articles));
        a.monPanier.articles=0;
        a.monPanier.montantTotal=0.0;
        a.monPanier.historiqueOperation=ajouterHistorique(a.monPanier.historiqueOperation,"Facturation");
        }
        else printf("PAIEMENT ANNULLE !! Continuer vos achats\n");
    }
    else printf("\t\t\tVEUILLEZ AJOUTER DES PRODUITS AVANT DE PASSER A LA FACTURATION !\n\n\n\t\t\t\t");
    return a;
}
//Catalogues
void afficherCatalogue(Catalogue *a){
    Catalogue* courant=a;
    if(!courant) return;
    if(courant->left) afficherCatalogue(courant->left);
    afficherArticleDansCatalogue(courant->article);
    if(courant->right) afficherCatalogue(courant->right);
}
void afficherArticleDansCatalogue(Article a){
     printf("%d\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2f\t%.2f\t%d\n",a.num,a.nomCommun,a.nomCommercial,a.codeArticle,a.categoriePle,a.sousCategorie,a.marque,a.codeBarre,a.numSerie,a.TVA,a.prixVente,a.quantite);
     printf("_______________________________________________________________________________________________________________________\n");
}
Article existeArticle(int num,int q){
    if(existeArticleDansArbre(arbre,num,q)){
        Catalogue* courant=arbre;
        while(courant)
        {
            if(num == courant->key && courant->article.quantite>=q) return courant->article;
            if(num > courant->key ) courant = courant->right;
            else courant = courant->left;
        }
    }
    else printf("\nARTICLE N'EXISTE PAS OU QUANTITE INSUFFISANTE! \n Reessayer !");
}
void ajouterCatalogue(Catalogue** arbre,Article article){
    Catalogue *a=malloc(sizeof(*a));
    if(a!=0){
        a->article=article;
        a->key=article.num;
        a->left=NULL;
        a->right=NULL;
    }
    Catalogue *tmpNode;
    Catalogue *tmpTree = *arbre;
    if(tmpTree){
            do{
                    tmpNode = tmpTree;
                    if(a->key > tmpTree->key )
                    {
                        tmpTree = tmpTree->right;
                        if(!tmpTree) tmpNode->right = a;
                    }
                    else
                    {
                        tmpTree = tmpTree->left;
                        if(!tmpTree) tmpNode->left = a;
                    }

            }while(tmpTree);
    }
    else *arbre=a;
}
int existeArticleDansArbre(Catalogue *a, int num,int q){
    Catalogue* arbre=a;
    while(arbre)
    {
        if(num == arbre->key && arbre->article.quantite>=q) return 1;
        if(num > arbre->key ) arbre = arbre->right;
        else arbre = arbre->left;
    }
    return 0;
}
void consulterCatalogue(){
    printf("\t\t\t\t\t\tLES PRODUITS DU CATALOGUE\n");
    printf("\t\t\t\t\t\t\t__________\n\n");
    afficherCatalogue(arbre);
}
Panier ajouterArticlePanier(Panier p,Article ar){
    ListeArticle *a=malloc(sizeof(*a));
    a->quantite=ar.quantite;
    a->suivant=NULL;
    strcpy(a->article.categoriePle,ar.categoriePle);
    strcpy(a->article.codeArticle,ar.codeArticle);
    strcpy(a->article.codeBarre,ar.codeBarre);
    a->article.dateExp=ar.dateExp;
    a->article.dateFab=ar.dateFab;
    strcpy(a->article.marque,ar.marque);
    strcpy(a->article.nomCommercial,ar.nomCommercial);
    strcpy(a->article.nomCommun,ar.nomCommun);
    a->article.num=ar.num;
    strcpy(a->article.numSerie,ar.numSerie);
    a->article.prixVente=ar.prixVente;
    a->article.quantite=ar.quantite;
    strcpy(a->article.sousCategorie,ar.sousCategorie);
    a->article.TVA=ar.TVA;
    if(a!=NULL){
            a->suivant=p.articles;
            p.articles=a;
            p.montantTotal+=a->quantite*(a->article.prixVente+((a->article.prixVente*a->article.TVA)/100));
            p.historiqueOperation=ajouterHistorique(p.historiqueOperation,"Ajout produit");
        }
    return p;
}

