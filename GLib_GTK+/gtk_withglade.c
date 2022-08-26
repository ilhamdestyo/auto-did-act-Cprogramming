/*
 * gtk_withglade.c
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
#include <stdio.h>
#include <gtk/gtk.h>

static GtkWidget *number1;
static GtkWidget *number2;
static GtkWidget *result;

static void load_CSS (void){
	GtkCssProvider* provider;
	GdkDisplay* display;
	GdkScreen* screen;
	///*
	const gchar* css_style_file	= "style.css";
	GFile* css_fp				=g_file_new_for_path(css_style_file);
	GError* error				= 0;
	///*
	provider	= gtk_css_provider_new();
	display		= gdk_display_get_default();
	screen		= gdk_display_get_default_screen(display);
	
	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_css_provider_load_from_file (provider, css_fp,&error);
	
	g_object_unref(provider);
	
}


void do_calculate(GtkWidget *calculate, gpointer data) {
	int num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number1)));
	int num2 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(number2)));
	
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "Hasil: %d", num1 + num2);
	
	gtk_label_set_text(GTK_LABEL(result), buffer);
}

// gcc gtk_withglade.c -o gtk_withglade `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv) {
	GtkWidget *window, *grid, *calculate;
	
	gtk_init(NULL, NULL);
	
	load_CSS();
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);
	
	number1 = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), number1, 0, 0, 1, 1);
	
	number2 = gtk_entry_new();
	gtk_grid_attach(GTK_GRID(grid), number2, 1, 0, 1, 1);
	
	calculate = gtk_button_new_with_label("Hitung Jumlah");
	gtk_container_add(GTK_CONTAINER(window),calculate);
	g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), NULL);
	gtk_grid_attach(GTK_GRID(grid), calculate, 2, 0, 1, 1);
	
	result = gtk_label_new("Hasil:");
	gtk_grid_attach(GTK_GRID(grid), result, 4, 0, 1, 1);
	
	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}

