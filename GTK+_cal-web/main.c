/**
 * gcc `pkg-config --cflags gtk+-3.0` -o exe main.c `pkg-config --libs gtk+-3.0` -Wno-format -Wno-deprecated-declarations -Wno-format-security -lm -export-dynamic
 */
#include "soal_common1.c" //pemanggilan function yang ada pada "soal_common1.c"

#include <gtk/gtk.h>

char buffer[128];
	const gchar *entry_text1;
    const gchar *entry_text2;
                int num1;
            int num2;

struct _info
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *submit_button;
    GtkWidget *button_link;
    GtkWidget *exitButton;
    /// ***
    GtkWidget *month_entry;
    GtkWidget *month_label;
    /// ***
    GtkWidget *year_entry;
    GtkWidget *year_label;
} info;



static guint flag = 0;

static void submit_clicked ( );
void load_css ( void );
GtkWidget *createWindow ( const gint width, const gint height );
void activate_callback ( GtkWidget *widget );
 
int main ( int argc, char *argv[] )
{
	const gchar *const uri = "https://delameta.com/#/screens/Home_page";
    
    gtk_init ( &argc, &argv );
    load_css();
    info.window = createWindow ( 200, 150 );
    info.grid = gtk_grid_new();
    gtk_container_set_border_width ( GTK_CONTAINER ( info.grid ), 15 );
    gtk_widget_set_name ( info.grid, "myGrid" );
    gtk_grid_set_column_spacing ( GTK_GRID ( info.grid ), 5 );
    gtk_grid_set_row_spacing ( GTK_GRID ( info.grid ), 5 );
    /// ***
    info.label = gtk_label_new ( "Please enter Year and Month:" );
    gtk_widget_set_margin_top ( info.label, 25 );
    gtk_widget_set_margin_start ( info.label, 85 );
    /// ***
    info.year_label = gtk_label_new ( "Year: " );
    gtk_widget_set_margin_start ( info.year_label, 10 );
    info.year_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(info.year_entry),"Tahun");
    /// ***
    info.month_label = gtk_label_new ( "Month: " );
    gtk_widget_set_margin_start ( info.month_label, 10 );
    info.month_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(info.month_entry),"Bulan");
    /// ***
    g_signal_connect_swapped ( info.year_entry, "activate", G_CALLBACK ( activate_callback ),info.year_entry);
    g_signal_connect_swapped ( info.month_entry, "activate", G_CALLBACK ( activate_callback ),info.month_entry);
    /// ***
    info.submit_button = gtk_button_new_with_mnemonic ( "_Submit" );
    gtk_widget_set_name ( info.submit_button, "myButton" );
    
    info.button_link = gtk_link_button_new_with_label(uri, "Delameta Web");
    gtk_widget_set_name ( info.button_link, "buttonLink");
    info.exitButton = gtk_button_new_with_mnemonic( "_Exit");
    gtk_widget_set_name ( info.exitButton, "Exit");
    g_signal_connect_swapped (info.exitButton, "clicked", G_CALLBACK (gtk_widget_destroy), info.window);
    /// ***
    g_signal_connect(info.submit_button,"clicked",G_CALLBACK(submit_clicked),NULL);
    //g_signal_connect_swapped ( info.submit_button, "clicked", G_CALLBACK ( submit_clicked ), info.year_entry);
    //g_signal_connect_swapped ( info.submit_button, "clicked", G_CALLBACK ( submit_clicked ), info.month_entry );
    /// ***
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.label,            0, 0, 2, 1 );
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.year_label,      0, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.month_label,       0, 2, 1, 1 );
    /// ***
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.year_entry,      1, 1, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.month_entry,       1, 2, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.submit_button,   1, 6, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.button_link,     2, 6, 1, 1 );
    gtk_grid_attach ( GTK_GRID ( info.grid ), info.exitButton,     4, 8, 1, 1 );
    /// ***
    gtk_widget_set_sensitive ( info.month_entry,FALSE );
    gtk_widget_set_sensitive ( info.submit_button,FALSE );
    gtk_widget_set_sensitive ( info.button_link,TRUE );
    gtk_widget_set_sensitive ( info.exitButton,TRUE );
    /// ***
    gtk_container_add ( GTK_CONTAINER ( info.window ), info.grid );
    gtk_widget_show_all ( info.window );
    gtk_main();
}

void activate_callback ( GtkWidget *widget )
{

    //g_print ("Hello again - %s was pressed\n", (char *) calData);

    entry_text1 = gtk_entry_get_text (GTK_ENTRY (info.year_entry));
    entry_text2 = gtk_entry_get_text (GTK_ENTRY (info.month_entry));
    g_print ("Contents of entries:\n%s\n%s\n", entry_text1, entry_text2);
    
    const gchar *text;
    text = gtk_entry_get_text (GTK_ENTRY (widget));
    if ( strlen ( text )> 0 )
    {
        switch ( flag )
        {
        case 0:
            gtk_widget_set_sensitive ( info.month_entry, TRUE );
            gtk_entry_grab_focus_without_selecting ( GTK_ENTRY ( info.month_entry ) );
            gtk_widget_set_sensitive ( info.year_entry,  FALSE );
            flag++;
            break;

        case 1:
            gtk_widget_set_sensitive ( info.submit_button, TRUE );
            gtk_window_set_focus ( GTK_WINDOW ( info.window ), info.submit_button );
            gtk_widget_set_sensitive ( info.month_entry,  FALSE );
            num1 = atoi((char *)entry_text1);
            num2 = atoi((char *)entry_text2);
			printf("result1 value Year:%d\n", num1);
			printf("result2 value Month:%d\n", num2);
            flag++;
            break;
            
        default:
            flag = 2;
        }
    }
}

void submit_clicked ()
{
	calendar( num1, num2);
}

void load_css ( void )
{
    GtkCssProvider *provider;
    GdkDisplay     *display;
    GdkScreen      *screen;
    /// ***
    const gchar *css_style_file = "style.css";
    GFile *css_fp               = g_file_new_for_path ( css_style_file );
    GError *error               = 0;
    /// ***
    provider = gtk_css_provider_new ();
    display  = gdk_display_get_default ();
    screen   = gdk_display_get_default_screen ( display );
    /// ***
    gtk_style_context_add_provider_for_screen   ( screen, GTK_STYLE_PROVIDER ( provider ), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION );
    gtk_css_provider_load_from_file             ( provider, css_fp, &error );
    /// ***
    g_object_unref ( provider );
}

GtkWidget *createWindow ( const gint width, const gint height )
{
    GtkWidget *window = gtk_window_new  ( GTK_WINDOW_TOPLEVEL );
    g_signal_connect        ( window, "destroy", gtk_main_quit, window );
    gtk_widget_set_events   ( window, GDK_KEY_PRESS_MASK );
    /// ***
    gtk_window_set_default_size     ( GTK_WINDOW ( window ), width, height );
    gtk_container_set_border_width  ( GTK_CONTAINER ( window ), 50 );
    return window;
}

