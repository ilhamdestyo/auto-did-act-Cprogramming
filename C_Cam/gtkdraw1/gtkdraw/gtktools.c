#include <gtk/gtk.h>

static int *tmpresultX,*tmpresultY,msize;
static double **resultR,**resultG,**resultB; 

typedef struct{
 unsigned int *X;
 unsigned int *Y;
 unsigned int MSize;
} coordinate_matrix;  

struct matrix {
   int rows;
   int cols;
   double** matriks;
};

typedef struct{
 struct matrix matrix_R;
 struct matrix matrix_G;
 struct matrix matrix_B;
 coordinate_matrix Coordinate;
} color_coordinate_matrix;

static GtkWidget *del_jendela,*del_vbox,*del_hbox, *del_label[10],*del_gambar1;


void init_gtk_component(int *argc, char ***argv){
	gtk_init(argc, argv);
    del_jendela = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    //gtk grid========================================
    del_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    del_hbox = gtk_grid_new();
    gtk_grid_set_column_homogeneous(GTK_GRID(del_hbox), TRUE);
    const char *format = "<span style=\"normal\" font_desc=\"Sans 17\" foreground=\"#000000\" >\%s</span>";
    char *markup;
	//------------------
    del_label[1] = gtk_label_new("");
    markup = g_markup_printf_escaped(format, "what the Program see");
	gtk_label_set_markup(GTK_LABEL(del_label[1]), markup);
	g_free(markup);
    //================================================
}

void show_gtk_component(GdkPixbuf *pix1){
	del_gambar1 = gtk_image_new_from_pixbuf(pix1);
	gtk_grid_attach(GTK_GRID(del_hbox), del_gambar1,  0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(del_hbox), del_label[1],  0, 1, 1, 1);
    gtk_box_pack_start(GTK_BOX(del_vbox), del_hbox, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(del_jendela), del_vbox);
    
    gtk_window_set_position(GTK_WINDOW(del_jendela), GTK_WIN_POS_CENTER);
    gtk_widget_show_all (del_jendela);
    g_signal_connect (del_jendela, "destroy", G_CALLBACK (gtk_main_quit), NULL);
        g_signal_connect (del_jendela, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    gtk_main ();
}

GdkPixbuf* put_pixel_to_pixbuf(GdkPixbuf *pixbuf, int x, int y, guchar red, guchar green, guchar blue, guchar alpha)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);
  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
    p[0] = red;
    p[1] = green;
    p[2] = blue;
    p[3] = alpha;
    return pixbuf;
}

static GdkPixbuf* load_rgb_matrix_data_from_stream(color_coordinate_matrix ccordinate){
	GdkColorspace colorspace = GDK_COLORSPACE_RGB;
	GdkPixbuf* pixbuf;
	pixbuf = gdk_pixbuf_new(colorspace, TRUE, 8, ccordinate.matrix_R.cols,ccordinate.matrix_R.rows);

	int i,j,k;
	int x,y,r,g,b;
	
	k = 0;
	for (i=0;i<ccordinate.matrix_R.rows;i++){
		for (j=0;j<ccordinate.matrix_R.cols;j++){
			
			r = ccordinate.matrix_R.matriks[i][j];
			g = ccordinate.matrix_G.matriks[i][j];
			b = ccordinate.matrix_B.matriks[i][j];
			pixbuf = put_pixel_to_pixbuf(pixbuf, j, i, r, g, b, 255);
		}
	}
	
	
	return pixbuf;
}
