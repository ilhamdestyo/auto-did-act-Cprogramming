#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
//#include "gui-pulsa-paket.c"

char pulsa_provider_text[20], provider_im[30];
char jenisPulsa_or_Data[20], jenis_PD_txt[100];
char input_number_text[20];

struct DataTransaksi{
	int pilihan_Transaksi, pilihan_sub_transaksi;
	long nominal_transaksi;
	long long nomor_masukan;
	int metode_pembayaran;
};

struct DataTransaksi tsc;

const int screenWidth = 1366, screenHight = 720;
int boxC_space, nboxC_space, boxC_side_margin, boxC_main_width;
int logo_width, logo_hight;
int imBack_width, imBack_hight;
int boxC_label_margin;

GtkCssProvider *cssProvider;
GtkBuilder *builder;

//mainWindow
GtkWidget *window;
GtkWidget *cek_order_btn;
GtkWidget *boxC, *MenuContainer;
GtkWidget *bt1, *bt2, *bt3, *bt4, *bt5, *bt6, *bt7, *bt8, *bt9, *bt10;
GtkWidget *bt1_c, *bt2_c,  *bt3_c, *bt4_c, *bt5_c, *bt6_c, *bt7_c, *bt8_c, *bt9_c, *bt10_c;
GtkWidget *logo_name, *bt1_imLogo, *bt2_imLogo, *bt3_imLogo, *bt4_imLogo, *bt5_imLogo, *bt6_imLogo, *bt7_imLogo, *bt8_imLogo, *bt9_imLogo, *bt10_imLogo;
GtkWidget *main_label, *bt_lb1, *bt_lb2, *bt_lb3, *bt_lb4, *bt_lb5, *bt_lb6, *bt_lb7, *bt_lb8, *bt_lb9, *bt_lb10;

void gtk_mainWindow_init();
void gtk_mainWindow_setAttrib();
void gtk_mainWindow_connect();
void gtk_builder_and_attrib_init();
void gtk_image_opt(GtkWidget *widget, char *fileName, int width, int hight, int margin_left);


int main(int argc, char **argv){
	/*deklarasi variabel
	 * ====================================*/
	boxC_space = screenWidth/30;
	boxC_side_margin = screenWidth/19;
	boxC_main_width = screenWidth/7;
	nboxC_space = screenWidth/13;
	boxC_label_margin = screenHight/8;

	logo_width = screenWidth/8;
	logo_hight = screenHight/15;
	imBack_width = screenWidth/100;
	imBack_hight = screenHight/40;
	/*=====================================*/
	gtk_init(&argc, &argv);
	/*main code
	 * ====================================*/
	//setup
	gtk_builder_and_attrib_init();

	gtk_mainWindow_init();
	gtk_mainWindow_connect();
	gtk_mainWindow_setAttrib();
	
	
	//start
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(window);
	g_object_unref(builder);
	gtk_main();
	return 0;
}

void gtk_builder_and_attrib_init(){
	builder=gtk_builder_new();
	gtk_builder_add_from_file (builder, "tugas_gtk1.glade", NULL);

	cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
}



//gtk_image_opt(bt1_imLogo, "img/logo_bt1.png", imWidth, imHight, im_margin);


void gtk_image_opt(GtkWidget *widget, char *fileName, int width, int hight, int margin_left){
	GdkPixbuf *my_img = gdk_pixbuf_new_from_file(fileName, NULL); //load picture from file 'filename'
	my_img = gdk_pixbuf_scale_simple(my_img, width, hight, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(widget), my_img);
	gtk_widget_set_margin_start(widget, margin_left);
}

void gtk_mainWindow_init(){
	window=GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
	cek_order_btn=GTK_WIDGET(gtk_builder_get_object(builder, "cek_order_btn"));;
	MenuContainer=GTK_WIDGET(gtk_builder_get_object(builder, "boxC_gridOpt"));
	boxC=GTK_WIDGET(gtk_builder_get_object(builder, "boxC"));

	//button
	bt1=GTK_WIDGET(gtk_builder_get_object(builder, "bt1"));
	bt2=GTK_WIDGET(gtk_builder_get_object(builder, "bt2"));
	bt3=GTK_WIDGET(gtk_builder_get_object(builder, "bt3"));
	bt4=GTK_WIDGET(gtk_builder_get_object(builder, "bt4"));
	bt5=GTK_WIDGET(gtk_builder_get_object(builder, "bt5"));
	bt6=GTK_WIDGET(gtk_builder_get_object(builder, "bt6"));
	bt7=GTK_WIDGET(gtk_builder_get_object(builder, "bt7"));
	bt8=GTK_WIDGET(gtk_builder_get_object(builder, "bt8"));
	bt9=GTK_WIDGET(gtk_builder_get_object(builder, "bt9"));
	bt10=GTK_WIDGET(gtk_builder_get_object(builder, "bt10"));

	bt1_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt1_imLogo"));
	bt2_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt2_imLogo"));
	bt3_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt3_imLogo"));
	bt4_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt4_imLogo"));
	bt5_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt5_imLogo"));
	bt6_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt6_imLogo"));
	bt7_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt7_imLogo"));
	bt8_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt8_imLogo"));
	bt9_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt9_imLogo"));
	bt10_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "bt10_imLogo"));
	logo_name=GTK_WIDGET(gtk_builder_get_object(builder, "logo_name"));

/*	//bt_C
	bt1_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C1"));
	bt2_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C2"));
	bt3_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C3"));
	bt4_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C4"));
	bt5_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C5"));
	bt6_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C6"));
	bt7_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C7"));
	bt8_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C8"));
	bt9_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C9"));
	bt10_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C10"));

/*	//label
	main_label=GTK_WIDGET(gtk_builder_get_object(builder, "main_label"));
	bt_lb1=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb1"));
	bt_lb2=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb2"));
	bt_lb3=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb3"));
	bt_lb4=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb4"));
	bt_lb5=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb5"));
	bt_lb6=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb6"));
	bt_lb7=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb7"));
	bt_lb8=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb8"));
	bt_lb9=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb9"));
	bt_lb10=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb10")); */
} 

void gtk_mainWindow_setAttrib(){
	//~ gtk_window_fullscreen(GTK_WINDOW(window));

	gtk_widget_set_name (window, "myWindow");
	gtk_widget_set_name (MenuContainer, "menuCtr1");

/*	//button
	gtk_widget_set_name (cek_order_btn, "cek_order_btn");
	gtk_widget_set_name (bt1, "bt1");
	gtk_widget_set_name (bt2, "bt2");
	gtk_widget_set_name (bt3, "bt3");
	gtk_widget_set_name (bt4, "bt4");
	gtk_widget_set_name (bt5, "bt5");
	gtk_widget_set_name (bt6, "bt6");
	gtk_widget_set_name (bt7, "bt7");
	gtk_widget_set_name (bt8, "bt8");
	gtk_widget_set_name (bt9, "bt9");
	gtk_widget_set_name (bt10, "bt10");

	//bt_C
	gtk_widget_set_name (bt1_c, "bt1_c");
	gtk_widget_set_name (bt2_c, "bt2_c");
	gtk_widget_set_name (bt3_c, "bt3_c");
	gtk_widget_set_name (bt4_c, "bt4_c");
	gtk_widget_set_name (bt5_c, "bt5_c");
	gtk_widget_set_name (bt6_c, "bt6_c");
	gtk_widget_set_name (bt7_c, "bt7_c");
	gtk_widget_set_name (bt8_c, "bt8_c");
	gtk_widget_set_name (bt9_c, "bt9_c");
	gtk_widget_set_name (bt10_c, "bt10_c");

	//label
	gtk_widget_set_name(main_label, "main_label");
	gtk_widget_set_name(bt_lb1, "bt_lb1");
	gtk_widget_set_name(bt_lb2, "bt_lb2");
	gtk_widget_set_name(bt_lb3, "bt_lb3");
	gtk_widget_set_name(bt_lb4, "bt_lb4");
	gtk_widget_set_name(bt_lb5, "bt_lb5");
	gtk_widget_set_name(bt_lb6, "bt_lb6");
	gtk_widget_set_name(bt_lb7, "bt_lb7");
	gtk_widget_set_name(bt_lb8, "bt_lb8");
	gtk_widget_set_name(bt_lb9, "bt_lb9");
	gtk_widget_set_name(bt_lb10, "bt_lb10"); */

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	//set dimension
/*	int imWidth, imHight;
	int im_margin = screenHight/70;
	imWidth=imHight=screenWidth/25;
	gtk_image_opt(bt1_imLogo, "img/logo_bt1.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt2_imLogo, "img/logo_bt2.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt3_imLogo, "img/logo_bt3.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt4_imLogo, "img/logo_bt4.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt5_imLogo, "img/logo_bt5.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt6_imLogo, "img/logo_bt6.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt7_imLogo, "img/logo_bt7.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt8_imLogo, "img/logo_bt8.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt9_imLogo, "img/logo_bt9.png", imWidth, imHight, im_margin);
	gtk_image_opt(bt10_imLogo, "img/logo_bt10.png", imWidth, imHight, im_margin);

	gtk_image_opt(logo_name, "img/logo.png", logo_width, logo_hight, 0);

	int lbl_width = screenWidth/5;
	int lbl_hight = screenHight/5;
	int lbc_width = screenWidth/13;
	int lbc_hight = screenHight/13;
	gtk_widget_set_size_request(bt1_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt2_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt3_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt4_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt5_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt6_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt7_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt8_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt9_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(bt10_c, lbl_width, lbl_hight);
	gtk_widget_set_size_request(main_label, lbc_width, lbc_hight); */

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(MenuContainer), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(MenuContainer), gspace_col);
	gtk_box_set_spacing(GTK_BOX(boxC), gspace_row);
	gtk_widget_set_margin_top(boxC, boxC_space);
	gtk_widget_set_margin_bottom(boxC, boxC_space);
	gtk_widget_set_margin_start(boxC, boxC_side_margin);
	gtk_widget_set_margin_end(boxC, boxC_side_margin);
}

void gtk_mainWindow_connect(){
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}
