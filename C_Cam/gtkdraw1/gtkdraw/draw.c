#include "v4l2grab.c"

gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	GdkPixbuf *cobapixbuf;
    color_coordinate_matrix dataRGB;
    //~ cobapixbuf = gdk_pixbuf_new_from_file("coba1.jpg",NULL);
	dataRGB = process_frame();
	cobapixbuf = load_rgb_matrix_data_from_stream(dataRGB);
       
	gdk_cairo_set_source_pixbuf(cr, cobapixbuf, 0, 0);
	cairo_paint(cr);
    cairo_stroke(cr);
    
    gtk_widget_queue_draw(widget);
    g_object_unref(cobapixbuf);
    
    return FALSE;
}



int main (int argc, char *argv[])
{
	gtk_init( &argc, &argv );
	
	
	GtkWidget *window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	g_signal_connect( window, "destroy", G_CALLBACK (gtk_main_quit), NULL );
	
	GtkWidget *cobadraw = gtk_drawing_area_new();
	
	tmpresultX = calloc((height*width)+1,sizeof(int));
	tmpresultY = calloc((height*width)+1,sizeof(int));
	resultR = calloc(height+1,sizeof(double));
	resultG = calloc(height+1,sizeof(double));
	resultB = calloc(height+1,sizeof(double));
	for(int i = 0;i < height;i++){
		resultR[i] = calloc(width+1,sizeof(double));
		resultG[i] = calloc(width+1,sizeof(double));
		resultB[i] = calloc(width+1,sizeof(double));
	}
	
	deviceName = "/dev/video0";
	// open and initialize device
	deviceOpen();
	deviceInit();
	// start capturing
	captureStart();
	
	
	gtk_widget_add_events( cobadraw, GDK_BUTTON_PRESS_MASK );
	gtk_widget_set_size_request( cobadraw, 640, 480 );
	g_signal_connect(cobadraw, "draw", G_CALLBACK(draw_cb), NULL );
	
	
	gtk_container_add( GTK_CONTAINER (window), cobadraw);
	gtk_widget_show(cobadraw);
	gtk_widget_show(window);
	
	
	
	gtk_main();
	
	// stop capturing
	captureStop();
	
	// close device
	deviceUninit();
	
	for(int i = 0;i < height;i++){
		free(resultR[i]),resultR[i]=NULL;
		free(resultG[i]),resultG[i]=NULL;
		free(resultB[i]),resultB[i]=NULL;
	}	
	free(resultR), resultR=NULL;
	free(resultG), resultG=NULL;
	free(resultB), resultB=NULL;
	free(tmpresultX),tmpresultX=NULL;
	free(tmpresultY),tmpresultY=NULL;
	
	deviceClose();
	
	return 0;
}
