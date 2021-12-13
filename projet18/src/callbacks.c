#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "stock.h"

char x[20]="jour",y[20]="stock1";





void
on_ajouter_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	Produit p;
	GtkWidget *id, *nom,*Type, *quantitee, *etat,*Jour,*Mois,*Annee; 	
	id=lookup_widget(objet,"entry1_id"); 
	nom=lookup_widget(objet,"entry2_nom"); 
	Type=lookup_widget(objet,"combobox2");	
	quantitee=lookup_widget(objet,"spinbutton1");	
	etat=lookup_widget(objet,"combobox1"); 	
	Jour=lookup_widget(objet, "spinbutton2"); 
	Mois=lookup_widget(objet,"spinbutton3"); 
	Annee=lookup_widget(objet, "spinbutton4");	
 
	

	strcpy(p.id,gtk_entry_get_text(GTK_ENTRY(id))); 
	strcpy(p.nom, gtk_entry_get_text(GTK_ENTRY(nom)));   
	
		
	if(strcmp("Drinks",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Type)))==0)
		strcpy(p.type,"Drinks");
	else if(strcmp("Food",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Type)))==0)
		strcpy(p.type,"Food");
	else 
		strcpy(p.type,"Accessories");	
	p.quantitee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (quantitee));	
	if(strcmp("Good",gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat)))==0)
		strcpy(p.etat,"Good");
	else if(strcmp("Acceptable",gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat)))==0)
		strcpy(p.etat,"Acceptable");
	else 
		strcpy(p.etat,"Bad");		
	p.Dt_ns.jour=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (Jour)); 
	p.Dt_ns.mois=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (Mois)); 
	p.Dt_ns.annee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (Annee));
	strcpy(p.service,x);
	strcpy(p.stock,y);
	ajouter_prod(p);
	
}


void
on_afficher_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion_stock,*action,*treeview1;
		
	action=lookup_widget(objet,"action");
	gtk_widget_destroy(action);
	gestion_stock=lookup_widget(objet,"gestion_stock");	
	gestion_stock=create_gestion_stock();
	gtk_widget_show(gestion_stock);
	treeview1=lookup_widget(gestion_stock,"treeview2");
	afficher_prod(treeview1,"produit.txt");
	//repture_stock(p);
}


void
on_refrech_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	Produit p;	
	GtkWidget *gestion_stock,*w1;
	GtkWidget *treeview1;	
	//action=lookup_widget(objet,"action");
	//gtk_widget_destroy(action);
	w1=lookup_widget(objet,"gestion_stock");	
	gestion_stock=create_gestion_stock();
	gtk_widget_show(gestion_stock);
	gtk_widget_hide(w1);	
	treeview1=lookup_widget(gestion_stock,"treeview2");
	afficher_prod(treeview1,"produit.txt");
	repture_stock(p);
}


void
on_rech_id_clicked                     (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *id,*treeview11;
	char id1[20];
	id=lookup_widget(objet,"entry6_recherche");
	treeview11=lookup_widget(objet,"treeview2");
	strcpy(id1,gtk_entry_get_text(GTK_ENTRY(id)));
	if(strcmp(id1,"")!=0)
	{
		recherche_prod(id1);
		afficher_prod(treeview11,"rech.txt");
		remove("rech.txt");
	}
	else
		afficher_prod(treeview11,"produit.txt");
}


void
on_button7_modifier_clicked            (GtkWidget       *objet,
                                        gpointer         user_data)
{
GtkWidget *action,*gestion_stock;
	GtkTreeModel     *model;
        GtkTreeSelection *selection;
        GtkTreeIter iter;
        GtkWidget* treeview;
	
        gchar* id;
	gchar* etat;
	gchar* nom;
	gint quantitee;
	gchar *service;
	gchar *stock;	
	gint jour;
	gint mois;
	gint annee;
	gchar *type;
	gestion_stock=lookup_widget(objet,"gestion_stock");
        treeview=lookup_widget(gestion_stock,"treeview2");
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
        if (gtk_tree_selection_get_selected(selection, &model, &iter))
        {
		gtk_tree_model_get (model,&iter,0,&id,1,&nom,2,&type,3,&quantitee,4,&etat,5,jour,6,mois,7,annee,8,&service,9,&stock,-1);
		gtk_widget_destroy(gestion_stock);
		action=lookup_widget(objet,"action");
		action=create_action();
		gtk_widget_show(action);
	        gtk_entry_set_text(GTK_ENTRY(lookup_widget(action,"entry1_id")),id);
                gtk_entry_set_text(GTK_ENTRY(lookup_widget(action,"entry2_nom")),nom);
		gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(action,"combobox2")),type);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(action,"spinbutton1")),quantitee);		
		gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(action,"combobox1")),etat);		
		//gtk_entry_set_text(GTK_ENTRY(lookup_widget(action,"entry4_quantitee")),quantitee);
		
		//gtk_entry_set_text(GTK_ENTRY(lookup_widget(action,"entry5_etat")),etat);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(action,"spinbutton2")),jour);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(action,"spinbutton3")),mois);
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(action,"spinbutton4")),annee);		
		//gtk_combo_box_set_active(GTK_COMBO_BOX(lookup_widget(action,"combobox1")),type);

	}
}


void
on_button6_ajouter_clicked             (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion_stock,*action,*treeview1;
	gestion_stock=lookup_widget(objet,"gestion_stock");
	action=lookup_widget(objet,"action");
	gtk_widget_destroy(gestion_stock);
	action=create_action();
	gtk_widget_show(action);
}


void
on_button8_supprimer_clicked           (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *action,*gestion_stock;
	GtkTreeModel  *model;
        GtkTreeSelection *selection;
        GtkTreeIter iter;
        GtkWidget *treeview1;
	
	
        gchar* id;
	
	gestion_stock=lookup_widget(objet,"gestion_stock");
        treeview1=lookup_widget(gestion_stock,"treeview2");
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview1));
        if (gtk_tree_selection_get_selected(selection, &model, &iter))
        {
		gtk_tree_model_get (model,&iter,0,&id,-1);
		supprimer_prod(id);
		afficher_prod(treeview1,"produit.txt");
	}

}

void
on_button9_dash_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion_stock,*examin ,*treeview3;
	gestion_stock=lookup_widget(objet,"gestion_stock");
	examin=lookup_widget(objet,"examin");
	gtk_widget_destroy(gestion_stock);
	examin=create_examin();
	gtk_widget_show(examin);
	treeview3=lookup_widget(examin,"treeview3");
	afficher_prod1(treeview3,"repture.txt");
}


void
on_modifier_clicked                    (GtkWidget       *objet,
                                        gpointer         user_data)
{
Produit p;
	GtkWidget *id, *nom,*Type, *quantitee, *etat, *Jour, *Mois, *Annee; 
	GtkCalendar *calendar1;	
	guint day, month, year;	
	id=lookup_widget(objet,"entry1_id"); 
	nom=lookup_widget(objet,"entry2_nom"); 
	Type=lookup_widget(objet,"combobox2"); 			
	quantitee=lookup_widget(objet,"spinbutton1");	
	etat=lookup_widget(objet,"combobox1"); 		
	Jour=lookup_widget(objet, "spinbutton2"); 
	Mois=lookup_widget(objet,"spinbutton3"); 
	Annee=lookup_widget(objet, "spinbutton4");
	

	strcpy(p.id,gtk_entry_get_text(GTK_ENTRY(id))); 
	strcpy(p.nom, gtk_entry_get_text(GTK_ENTRY(nom)));   
	if(strcmp("Good",gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat)))==0)
		strcpy(p.etat,"Good");
	else if(strcmp("Acceptable",gtk_combo_box_get_active_text(GTK_COMBO_BOX(etat)))==0)
		strcpy(p.etat,"Acceptable");
	else 
		strcpy(p.etat,"Bad");	
	p.quantitee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (quantitee));	
	if(strcmp("Drinks",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Type)))==0)
		strcpy(p.type,"Drinks");
	else if(strcmp("Food",gtk_combo_box_get_active_text(GTK_COMBO_BOX(Type)))==0)
		strcpy(p.type,"Food");
	else 
		strcpy(p.type,"Accessories");	
	p.quantitee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (quantitee));	
	//gtk_calendar_get_date(GTK_CALENDAR(calendar1), &day, &month, &year);	
	/*p.Dt_ns.jour=year;
	p.Dt_ns.mois=month+1;
	p.Dt_ns.annee=day;*/	
	//strcpy(p.etat,gtk_entry_get_text(GTK_ENTRY (etat)));
	p.Dt_ns.jour=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (Jour)); 
	p.Dt_ns.mois=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (Mois)); 
	p.Dt_ns.annee=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (Annee));
	strcpy(p.service,x);
	strcpy(p.stock,y);
	modifier_prod(p);
}
void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	strcpy(x,"jour");
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
	strcpy(x,"soir");
}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
	strcpy(y,"stock2");
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
	strcpy(y,"stock1");
}


void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton))
	strcpy(y,"stock3");
}


void
on_retour_clicked                      (GtkWidget       *objet,
                                        gpointer         user_data)
{
	GtkWidget *gestion_stock,*examin,*treeview2;
	gestion_stock=lookup_widget(objet,"gestion_stock");
	examin=lookup_widget(objet,"examin");
	gtk_widget_destroy(examin);
	gestion_stock=create_gestion_stock();
	gtk_widget_show(gestion_stock);
	treeview2=lookup_widget(gestion_stock,"treeview2");
	afficher_prod(treeview2,"produit.txt");
}


void
on_out_of_stock_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{		
	/*Produit P;	
	GtkWidget *examin,*treeview3;	
	repture_stock(P);	
	treeview3=lookup_widget(examin,"treeview3");
	afficher_prod1(treeview3,"repture.txt");*/
}

