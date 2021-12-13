#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "callbacks.h"
#include <gtk/gtk.h>


enum{
	PID,
	PNOM,
	PTYPE,
	PQUANTITEE,
	PETAT,
	PJOUR,
	PMOIS,
	PANNEE,
	PSERVICE,
	PSTOCK,
	COLUMNS
};

void ajouter_prod(Produit P)
{
	FILE *f;
	f=fopen("produit.txt","a+");
	if(f!=NULL)
	{
		fprintf(f,"%s %s %s %d %s %d %d %d %s %s \n",P.id,P.nom,P.type,P.quantitee,P.etat,P.Dt_ns.jour,P.Dt_ns.mois,P.Dt_ns.annee,P.service,P.stock);
	}
	else
		return;
	fclose(f);
}
void supprimer_prod(char id[20])
{
	Produit P; 
	FILE *f,*g; 
	f=fopen("produit.txt", "r"); 
	g=fopen("dump.txt", "a+");
	if(f!=NULL && g!=NULL)
	{
		while(fscanf(f,"%s %s %s %d %s %d %d %d %s %s \n",P.id,P.nom,P.type,&P.quantitee,P.etat,&P.Dt_ns.jour,&P.Dt_ns.mois,&P.Dt_ns.annee,P.service,P.stock)!=EOF)
		{
			if(strcmp(id,P.id)!=0)
				fprintf(g,"%s %s %s %d %s %d %d %d %s %s \n",P.id,P.nom,P.type,P.quantitee,P.etat,P.Dt_ns.jour,P.Dt_ns.mois,P.Dt_ns.annee,P.service,P.stock);
		
       		}
	
	}
	fclose(f);
	fclose (g); 
	remove("produit.txt"); 
	rename("dump.txt", "produit.txt");
}
void modifier_prod(Produit P)
{
	Produit Pr;
	FILE *F, *FW;
	F=fopen("produit.txt","r");
	FW=fopen("tmp.txt","a+");
	if (F!=NULL && FW!=NULL)
 	{
		while (fscanf(F,"%s %s %s %d %s %d %d %d %s %s \n",Pr.id,Pr.nom,Pr.type,&Pr.quantitee,Pr.etat,&Pr.Dt_ns.jour,&Pr.Dt_ns.mois,&Pr.Dt_ns.annee,Pr.service,Pr.stock)!=EOF){
    			if (strcmp(Pr.id,P.id)!=0)
     			{
				fprintf(FW,"%s %s %s %d %s %d %d %d %s %s\n",Pr.id,Pr.nom,Pr.type,Pr.quantitee,Pr.etat,Pr.Dt_ns.jour,Pr.Dt_ns.mois,Pr.Dt_ns.annee,Pr.service,Pr.stock);
				    			
			}
     			else
     			{	     
 				fprintf(FW,"%s %s %s %d %s %d %d %d %s %s",P.id,P.nom,P.type,P.quantitee,P.etat,P.Dt_ns.jour,P.Dt_ns.mois,P.Dt_ns.annee,P.service,P.stock);  
     			}
  		}   
	}
	fclose(F);
	fclose(FW);
	remove("produit.txt");
	rename("tmp.txt","produit.txt");
}
void recherche_prod(char id[20])
{
	FILE *F,*FW;
	Produit P;
	F=fopen("produit.txt","r");
	FW=fopen("rech.txt","a+");
	if(F!=NULL && FW!=NULL)
 	{
		while (fscanf(F,"%s %s %s %d %s %d %d %d %s %s\n",P.id,P.nom,P.type,&P.quantitee,P.etat,&P.Dt_ns.jour,&P.Dt_ns.mois,&P.Dt_ns.annee,P.service,P.stock)!=EOF)		{
    			if (strcmp(id,P.id)==0)
     			{
       				fprintf(FW, "%s %s %s %d %s %d %d %d %s %s\n",P.id,P.nom,P.type,P.quantitee,P.etat,P.Dt_ns.jour,P.Dt_ns.mois,P.Dt_ns.annee,P.service,P.stock);
    		 	}
  		}   
	}
     	fclose(F);
  	fclose(FW);
}
void afficher_prod(GtkWidget *liste,char file[20])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
        
	char id[20];
	char nom[20];
	char type[20];
	char quantitee[20];
	char etat[20];
	char jour[20];
	char mois[20];
	char annee[20];
	char service[20];
	char stock[20];
	Produit P;
	store=NULL;
	FILE *f=NULL;	
	store=gtk_tree_view_get_model(liste);	
 	if(store==NULL)
	{
		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",PID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("nom",renderer,"text",PNOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("type",renderer,"text",PTYPE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("quantitee",renderer,"text",PQUANTITEE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("etat",renderer,"text",PETAT,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("jour",renderer,"text",PJOUR,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("mois",renderer,"text",PMOIS,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("annee",renderer,"text",PANNEE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("service",renderer,"text",PSERVICE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("stock",renderer,"text",PSTOCK,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);	

	}
	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
	f=fopen(file,"r");
	if(f==NULL){return;}
	else
	{ 	
		while(fscanf(f,"%s %s %s %d %s %d %d %d %s %s \n",P.id,P.nom,P.type,&P.quantitee,P.etat,&P.Dt_ns.jour,&P.Dt_ns.mois,&P.Dt_ns.annee,P.service,P.stock)!=EOF)
		{
			gtk_list_store_append(store,&iter); 				
gtk_list_store_set(store,&iter,PID,P.id,PNOM,P.nom,PTYPE,P.type,PQUANTITEE,P.quantitee,PETAT,P.etat,PJOUR,P.Dt_ns.jour,PMOIS,P.Dt_ns.mois,PANNEE,P.Dt_ns.annee,PSERVICE,P.service,PSTOCK,P.stock,-1);
		}
	fclose(f); 
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store)); 	
	g_object_unref(store);                                 
	}
}
void repture_stock(Produit P)
{
	FILE *f,*g;
	f=fopen("produit.txt","r");
	g=fopen("repture.txt","a+");	
	if(f!=NULL && g!=NULL)
	{
		while(fscanf(f,"%s %s %s %d %s %d %d %d %s %s \n",P.id,P.nom,P.type,&P.quantitee,P.etat,&P.Dt_ns.jour,&P.Dt_ns.mois,&P.Dt_ns.annee,P.service,P.stock)!=EOF)
		{
			if(P.quantitee<=15)
				fprintf(g, "%s %s %s %d %s %d %d %d %s %s\n",P.id,P.nom,P.type,P.quantitee,P.etat,P.Dt_ns.jour,P.Dt_ns.mois,P.Dt_ns.annee,P.service,P.stock);

		}	
	}

	fclose(f);
	fclose(g);
}
void afficher_prod1(GtkWidget *liste,char file[20])
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
        
	char id[20];
	char nom[20];
	char type[20];
	char quantitee[20];
	char etat[20];
	char jour[20];
	char mois[20];
	char annee[20];
	char service[20];
	char stock[20];
	Produit P;
	store=NULL;
	FILE *f=NULL;	
	store=gtk_tree_view_get_model(liste);	
	//repture_stock(P);	
	if(store==NULL)
	{
		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("id",renderer,"text",PID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	
		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("nom",renderer,"text",PNOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("type",renderer,"text",PTYPE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("quantitee",renderer,"text",PQUANTITEE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		
		column=gtk_tree_view_column_new_with_attributes("etat",renderer,"text",PETAT,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("jour",renderer,"text",PJOUR,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("mois",renderer,"text",PMOIS,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("annee",renderer,"text",PANNEE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("service",renderer,"text",PSERVICE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("stock",renderer,"text",PSTOCK,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);	

	}
	store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING);
	
			
	f=fopen(file,"r");
	if(f==NULL){return;}
	else
	{ 	
		while(fscanf(f,"%s %s %s %d %s %d %d %d %s %s \n",P.id,P.nom,P.type,&P.quantitee,P.etat,&P.Dt_ns.jour,&P.Dt_ns.mois,&P.Dt_ns.annee,P.service,P.stock)!=EOF)
		{
			gtk_list_store_append(store,&iter); 				
gtk_list_store_set(store,&iter,PID,P.id,PNOM,P.nom,PTYPE,P.type,PQUANTITEE,P.quantitee,PETAT,P.etat,PJOUR,P.Dt_ns.jour,PMOIS,P.Dt_ns.mois,PANNEE,P.Dt_ns.annee,PSERVICE,P.service,PSTOCK,P.stock,-1);
		}
	fclose(f); 
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store)); 	
	g_object_unref(store);                                 
	}
	
}



