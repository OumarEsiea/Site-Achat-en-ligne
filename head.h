#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//-----------------------------------------Head----------------------------------------//
//Constantes et variables globales
#define TAILLE_MAX_CATALOGUE 10
#define MONTANT_MAX_PANIER 500
#define TAILLE_MAX 100
#define TAILLE_SMALL 35
static int nombreArticle=0;
static int nombreHist=0;


//Libelles d'interfaces et messages d'erreurs
char infoUser[][TAILLE_MAX]={"Ndoba-Sy","Ndoba&Sy","63411","650","94120","Fontenay-sous-bois"};
char text[][TAILLE_MAX]={"LOGICIEL D'ACHAT EN LIGNE","ACCUEIL","Consulter le catalogue",
"Gestion du panier","Sortir du le logiciel","Choisir  une operation","VOTRE PANIER EST VIDE",
"VOS PRODUITS","VOS HISTORIQUES","HISTORIQUE VIDE","MERCI POUR VOTRE VISITE !","CATALOGUE VIDE","LES PRODUITS DU CATALOGUE","TOTAL FACTURE","CONFIRMER LE PAYEMENT :",
"VOUS VOULEZ AJOUTER UN PRODUIT DANS VOTRE PANIER "};
char error[][TAILLE_MAX]={"ERREUR DE SAISIE. Reessayez !","Operation reussie","Article n'existe pas","Operation Echouee"};

//Structures
typedef struct Coordonnees Coordonnees; // j'utilise cette notation pour eviter d'ecrire "struct" a chaque fois
typedef struct Vendeur Vendeur; //commercant (hors perimetre mais je declare pour information)
typedef struct DateHeure DateHeure; //date-heure
typedef struct Panier Panier;   //gestion du panier de l'acheteur
typedef struct Acheteur Acheteur;//acheteur
typedef struct Article Article; //represente un produit
typedef struct Catalogue Catalogue;//pour representer le catalogue sous forme d'arbre
typedef struct ListeArticle ListeArticle;// pour faire une liste des articles
typedef struct Operation Operation;//les operations des historiques des paniers
//Definitions des structures
struct Coordonnees{
    char *mail;
    char *adressePost;
    char *ville;
};
struct  Vendeur{
    char *nomVendeur;
    Coordonnees coordVendeur;
    char numRCS; // long pas suffisament grand , et pas d'opération sur le RCS
};
struct DateHeure{
    int jj,mm,aa,hh,mn,ss;
};
DateHeure DATE;
struct Panier{
  ListeArticle* articles;
  Operation* historiqueOperation;
  float montantTotal;
};
struct  Acheteur{
    char *nomAcheteur;
    Coordonnees coordAcheteur;
    Panier monPanier;
};
struct Article{
    int num;
    char codeArticle[TAILLE_SMALL];
    char nomCommercial[TAILLE_SMALL];
    char nomCommun[TAILLE_SMALL];
    char categoriePle[TAILLE_SMALL];
    char sousCategorie[TAILLE_SMALL];
    char marque[TAILLE_SMALL];
    char codeBarre[TAILLE_SMALL];
    char numSerie[TAILLE_SMALL];
    DateHeure dateFab;
    DateHeure dateExp;
    float TVA;
    float prixVente;
    int quantite;
};
struct Catalogue{
    int key;
    Article article;
    Catalogue *left,*right;
};
struct ListeArticle{
    int quantite;
    Article article;
    ListeArticle *suivant;
};
struct Operation{
    int numOperation;
    char *nomOperation;
    DateHeure dateOperation;
    Operation* suivant;
};
//--------------------------SIGNATURES DES FONCTIONS DU PROGRAMME----------------------------
//-------------------------Menu-------------------
int menuPrincipal();
int menuPanier();
//------------------------Acheteur---------------
/** FONCTIONS POUR REMPLIR ET AFFICHER LES  INFORMATIONS DE L'ACHETEUR*/
Acheteur initialiserUser();
void afficherInfoVendeur(Vendeur v);
void afficherCoordonnees(Coordonnees c);
/** FONCTIONS POUR AFFICHER LE PANIER ET LES PRODUITS DU PANIER*/
void afficherPanier(Acheteur acheteur);
void afficherAllArticle(ListeArticle *a);
void afficherArticle(Article article,int quantite);
/** FONCTIONS POUR CONSULTER LE PANIER ET LES FONCTIONNALITES DU PANIER*/
Acheteur ConsulterPanier(Acheteur acheteur);
Panier ajouterArticle(Panier p);
Panier supprimerArticle(Panier p);
int existeArticlePanier(Panier p,int num);
ListeArticle* supprimerArticleInListe(ListeArticle* a,int num);
float montant(ListeArticle *a);
void afficherHistorique(Acheteur a);
Operation* ajouterHistorique(Operation *p,char nom[TAILLE_MAX]);
Acheteur facturation(Acheteur);
//---------------------Catalogues--------------------
void consulterCatalogue();
void ajouterCatalogue(Catalogue** arbre,Article article);
void afficherCatalogue(Catalogue *a);
void afficherArticleDansCatalogue(Article a);
Article existeArticle(int num,int q);
int existeArticleDansArbre(Catalogue *arbre, int num,int q);


#endif // HEAD_H_INCLUDED
