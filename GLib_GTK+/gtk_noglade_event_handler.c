/*
 * gtk_noglide_event_handler.c
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

#include <gtk/gtk.h>

/* Prototipe signal handler */
static gint window_closed(GtkWidget* w, GdkEventAny* e, gpointer data);

int main(int argc, char* argv[]){
	GtkWidget* window; /* Window */
	GtkWidget* label; /* Label */
	
	/*Inisialisai GTK+ */
	gtk_init(&argc, &argv);
	
	/*Membuat Window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Hello");
	
	/* Text di dalam window */
	label = gtk_label_new("Hallo Semua");
	gtk_container_add(GTK_CONTAINER(window), label);
	
	/* Memberikan event handler */
	gtk_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(window_closed), NULL);
	
	/* Menampilkan window dan semua isinya */
	gtk_widget_show_all(window);
	gtk_main();
	
	/* Keluar Program */
	return 0;
}

/* Event handler untuk window_closed */
static gint window_closed(GtkWidget* w, GdkEventAny* e, gpointer data){
	gtk_main_quit();
	return FALSE;
}


