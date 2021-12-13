#include<gtk/gtk.h>
typedef struct
{
    int jour;
    int mois;
    int annee;

}Date;
typedef struct 
{
    char id[20];
    char nom[20];
    char type[20];
    int quantitee;
    char etat[20];
    Date Dt_ns;
    char service[20];
    char stock[20];    
                   
} Produit;

void ajouter_prod(Produit P);
void supprimer_prod(char id[20]);
void modifier_prod(Produit P);
void afficher_prod(GtkWidget *liste,char file[20]);
void recherche_prod(char id[20]);
void repture_stock();
void afficher_prod1(GtkWidget *liste,char file[20]);

