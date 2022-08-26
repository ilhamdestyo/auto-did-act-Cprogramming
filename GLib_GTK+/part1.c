/*
 * part1.c
 * 
 * Copyright 2022 lime <lime@lime-ThinkPad-T450>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>

//make them global
GtkWidget* window;
GtkWidget* fixed1;
GtkWidget* button1;
GtkWidget* label1;
GtkBuilder* builder;

int main(int argc, char **argv) {
	
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new_from_file("part1.glade");//akses glide 
	
	window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));//
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_builder_connect_signals(builder,NULL);
	
	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder,"button1"));
	label1 = GTK_WIDGET(gtk_builder_get_object(builder,"label1"));
	
	gtk_widget_show(window);
	
	gtk_main();
	
	return EXIT_SUCCESS;
}

void on_button1_clicked (GtkButton *b){
	gtk_link_button_new((const gchar*) "/home/lime/Documents/Delameta_Work/source-code/GTK+_cal-web/calendar/caltemplate.c");
}

