#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

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
GtkWidget *mainViewport, *mainScrollWindow, *mainBox;
GtkWidget *bt1, *bt2, *bt3, *bt4, *bt5, *bt6, *bt7, *bt8, *bt9, *bt10;
GtkWidget *bt1_c, *bt2_c,  *bt3_c, *bt4_c, *bt5_c, *bt6_c, *bt7_c, *bt8_c, *bt9_c, *bt10_c;
GtkWidget *logo_name, *bt1_imLogo, *bt2_imLogo, *bt3_imLogo, *bt4_imLogo, *bt5_imLogo, *bt6_imLogo, *bt7_imLogo, *bt8_imLogo, *bt9_imLogo, *bt10_imLogo;
GtkWidget *main_label, *bt_lb1, *bt_lb2, *bt_lb3, *bt_lb4, *bt_lb5, *bt_lb6, *bt_lb7, *bt_lb8, *bt_lb9, *bt_lb10;

//windowPayment
GtkWidget *windowPayment;
GtkWidget *payment_boxC, *payment_boxC_main, *payment_menuGrid;
GtkWidget *payment_imLogo, *payment_imgKembali, *payment_menu_bt_im1, *payment_menu_bt_im2, *payment_menu_bt_im3, *payment_menu_bt_im4, *payment_menu_bt_im5;
GtkWidget *payment_bt_main, *payment_menuBox_bt_kembali,*payment_menu_bt1, *payment_menu_bt2, *payment_menu_bt3, *payment_menu_bt4, *payment_menu_bt5;
GtkWidget *payment_boxC_label, *payment_menuBox_label;

//windowCekOrder
GtkWidget *windowCko;
GtkWidget *cko_boxC, *cko_grid_num;
GtkWidget *cko_close_btn;

//windowBarcode
GtkWidget *windowBarcode;
GtkWidget *bcd_boxC, *bcd_grid_num, *bcd_imgBox, *bcd_img;
GtkWidget *bcd_close_btn;


void gtk_mainWindow_init();
void gtk_mainWindow_setAttrib();
void gtk_mainWindow_connect();


void gtk_windowPayment_init();
void gtk_windowPayment_setAttrib();
void gtk_windowPayment_connect();
static void start_windowPayment();
static void close_windowPayment();
static void view_windowPayment();
static void payment_go_to_main();


static void start_windowCko();
static void view_windowCko();
void gtk_windowCko_init();
void gtk_windowCko_setAttrib();
void gtk_windowCko_connect();
static void close_windowCko();
//static void cko_setOrder(GtkWidget *numWidget);

static void start_windowBcd();
static void view_windowBcd();
void gtk_windowBcd_init();
void gtk_windowBcd_setAttrib();
void gtk_windowBcd_connect();
static void close_windowBcd();

void gtk_builder_and_attrib_init();
void gtk_image_opt(GtkWidget *widget, char *fileName, int width, int hight, int margin_left);


int main(int argc, char **argv){
	boxC_space = screenWidth/30;
	boxC_side_margin = screenWidth/19;
	boxC_main_width = screenWidth/7;
	nboxC_space = screenWidth/13;
	boxC_label_margin = screenHight/8;

	logo_width = screenWidth/8;
	logo_hight = screenHight/15;
	imBack_width = screenWidth/100;
	imBack_hight = screenHight/40;
	gtk_init(&argc, &argv);
	//setup
	gtk_builder_and_attrib_init();

	gtk_mainWindow_init();
	gtk_mainWindow_connect();
	gtk_mainWindow_setAttrib();
	
	start_windowPayment();
	start_windowCko();
	start_windowBcd();
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

void gtk_image_opt(GtkWidget *widget, char *fileName, int width, int hight, int margin_left){
	GdkPixbuf *my_img = gdk_pixbuf_new_from_file(fileName, NULL);
	my_img = gdk_pixbuf_scale_simple(my_img, width, hight, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(widget), my_img);
	gtk_widget_set_margin_start(widget, margin_left);
}

void gtk_mainWindow_init(){
	window=GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
	cek_order_btn=GTK_WIDGET(gtk_builder_get_object(builder, "cek_order_btn"));;
	MenuContainer=GTK_WIDGET(gtk_builder_get_object(builder, "boxC_gridOpt"));
	boxC=GTK_WIDGET(gtk_builder_get_object(builder, "boxC"));
	mainBox=GTK_WIDGET(gtk_builder_get_object(builder, "mainBox"));
	mainScrollWindow=GTK_WIDGET(gtk_builder_get_object(builder, "mainScrollWindow"));
	mainViewport=GTK_WIDGET(gtk_builder_get_object(builder, "mainViewport"));
	

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

	////bt_C
	//bt1_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C1"));
	//bt2_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C2"));
	//bt3_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C3"));
	//bt4_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C4"));
	//bt5_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C5"));
	//bt6_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C6"));
	//bt7_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C7"));
	//bt8_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C8"));
	//bt9_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C9"));
	//bt10_c=GTK_WIDGET(gtk_builder_get_object(builder, "bt_C10"));

	////label
	//main_label=GTK_WIDGET(gtk_builder_get_object(builder, "main_label"));
	//bt_lb1=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb1"));
	//bt_lb2=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb2"));
	//bt_lb3=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb3"));
	//bt_lb4=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb4"));
	//bt_lb5=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb5"));
	//bt_lb6=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb6"));
	//bt_lb7=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb7"));
	//bt_lb8=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb8"));
	//bt_lb9=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb9"));
	//bt_lb10=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb10"));
}

void gtk_mainWindow_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(window));

	gtk_widget_set_name (window, "myWindow");
	gtk_widget_set_name (MenuContainer, "menuCtr1");

	//button
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
	gtk_widget_set_name(bt_lb10, "bt_lb10");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	//set dimension
	//int imWidth, imHight;
	//int im_margin = screenHight/70;
	//imWidth=imHight=screenWidth/25;
	//gtk_image_opt(bt1_imLogo, "img/BtnExpresso.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt2_imLogo, "img/BtnCappuccino.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt3_imLogo, "img/BtnMacchiato.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt4_imLogo, "img/BtnLongBlack.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt5_imLogo, "img/BtnCoffeLatte.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt6_imLogo, "img/BtnMocca.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt7_imLogo, "img/BtnAmericano.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt8_imLogo, "img/BtnFlatWhite.png", imWidth, imHight, im_margin);
	//gtk_image_opt(bt9_imLogo, "img/BtnVienna.png", imWidth, imHight, im_margin);

	//gtk_image_opt(logo_name, "img/[removal.ai]_tmp-62b04a64c256c.png", logo_width, logo_hight, 0);

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
	gtk_widget_set_size_request(main_label, lbc_width, lbc_hight);

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
	g_signal_connect(bt1, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt2, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt3, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt4, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt5, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt6, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt7, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt8, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(bt9, "clicked", G_CALLBACK (view_windowPayment), NULL);
	g_signal_connect(cek_order_btn, "clicked", G_CALLBACK (view_windowCko), NULL);
}

static void view_windowPayment(){
	gtk_widget_show(windowPayment);
}


static void start_windowPayment(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowPayment_init();
	gtk_windowPayment_setAttrib();
	gtk_windowPayment_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowPayment);
}

//windowPayment
void gtk_windowPayment_init(){
	windowPayment=GTK_WIDGET(gtk_builder_get_object(builder, "windowPayment"));

	payment_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "payment_boxC"));
	payment_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "payment_boxC_main"));
	payment_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menuGrid"));

	payment_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "payment_bt_main"));
	payment_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt1"));
	payment_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt2"));
	payment_menu_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt3"));
	payment_menu_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt4"));
	payment_menu_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt5"));
	payment_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menuBox_bt_kembali"));

	payment_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "payment_imLogo"));
	payment_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "paymnet_imgKembali"));
	payment_menu_bt_im1=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt_im1"));
	payment_menu_bt_im2=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt_im2"));
	payment_menu_bt_im3=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt_im3"));
	payment_menu_bt_im4=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt_im4"));
	payment_menu_bt_im5=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menu_bt_im5"));

	payment_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "payment_boxC_label"));
	payment_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "payment_menuBox_label"));
}

void gtk_windowPayment_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowPayment));

	gtk_widget_set_name(windowPayment, "windowPayment");

	gtk_widget_set_name(payment_bt_main, "payment_bt_main");
	gtk_widget_set_name(payment_menuBox_bt_kembali, "payment_menuBox_bt_kembali");
	gtk_widget_set_name(payment_menu_bt1, "payment_menu_bt1");
	gtk_widget_set_name(payment_menu_bt2, "payment_menu_bt2");
	gtk_widget_set_name(payment_menu_bt3, "payment_menu_bt3");
	gtk_widget_set_name(payment_menu_bt4, "payment_menu_bt4");
	gtk_widget_set_name(payment_menu_bt5, "payment_menu_bt5");

	gtk_widget_set_name(payment_imLogo, "payment_imLogo");

	gtk_widget_set_name(payment_boxC_label, "payment_boxC_label");
	gtk_widget_set_name(payment_menuBox_label, "payment_menuBox_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_label_set_text(GTK_LABEL(payment_boxC_label), jenisPulsa_or_Data);

	//set dimention
	int imWidth, imHight;
	imWidth=imHight=screenWidth/7;
	gtk_image_opt(payment_menu_bt_im1, "img/Dana Logo Vector.png", imWidth, imHight, 0);
	gtk_image_opt(payment_menu_bt_im2, "img/GoPay Logo Vector1.png", imWidth, imHight, 0);
	gtk_image_opt(payment_menu_bt_im3, "img/OVO Logo Vector.png", imWidth, imHight, 0);
	gtk_image_opt(payment_menu_bt_im4, "img/Link Aja Logo Vector1.png", imWidth, imHight, 0);
	gtk_image_opt(payment_menu_bt_im5, "img/Shopee Pay Logo Vector_vectrostudio-1.png", imWidth, imHight, 0);

	gtk_widget_set_margin_top(payment_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(payment_boxC_label, boxC_label_margin);

	gtk_widget_set_margin_start(payment_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(payment_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(payment_boxC, boxC_space);
	gtk_widget_set_margin_bottom(payment_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(payment_boxC), nboxC_space);
	gtk_widget_set_size_request(payment_boxC_main, boxC_main_width, -1);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(payment_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(payment_menuGrid), gspace_col);
	gtk_widget_set_margin_top(payment_menuGrid, boxC_space);

	gtk_image_opt(payment_imLogo, "img/My project.png", logo_width, logo_hight, 0);
	gtk_image_opt(payment_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);
}

void gtk_windowPayment_connect(){
	g_signal_connect(windowPayment, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(payment_menu_bt1, "clicked", G_CALLBACK(view_windowBcd), NULL);
	g_signal_connect(payment_menu_bt2, "clicked", G_CALLBACK(view_windowBcd), NULL);
	g_signal_connect(payment_menu_bt3, "clicked", G_CALLBACK(view_windowBcd), NULL);
	g_signal_connect(payment_menu_bt4, "clicked", G_CALLBACK(view_windowBcd), NULL);
	g_signal_connect(payment_menu_bt5, "clicked", G_CALLBACK(view_windowBcd), NULL);
	g_signal_connect(payment_bt_main, "clicked", G_CALLBACK (payment_go_to_main), NULL);
	g_signal_connect(payment_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowPayment), NULL);
}

static void close_windowPayment(){
	gtk_widget_hide(windowPayment);
}

static void payment_go_to_main(){
	gtk_widget_hide(windowPayment);
}


//windowCekOrder
void gtk_windowCko_init(){
	windowCko=GTK_WIDGET(gtk_builder_get_object(builder, "windowCko"));
	
	cko_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "cko_boxC"));
	cko_grid_num=GTK_WIDGET(gtk_builder_get_object(builder, "cko_grid_num"));
	
	cko_close_btn=GTK_WIDGET(gtk_builder_get_object(builder, "cko_close_btn"));
}

void gtk_windowCko_setAttrib(){
	gtk_window_set_position(GTK_WINDOW(windowCko), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_widget_set_name(windowCko, "windowCko");

	gtk_widget_set_name(cko_grid_num, "cko_grid_num");
	
	gtk_widget_set_name(cko_close_btn, "cko_close_btn");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	//set dimention
	int cko_margin = screenWidth/60;
	int cko_boxC_space = screenWidth/40;
	int cko_bt_dimention = screenWidth/19;
	int cko_grid_num_space = screenWidth/80;

	gtk_widget_set_margin_start(cko_boxC, cko_margin);
	gtk_widget_set_margin_end(cko_boxC, cko_margin);
	gtk_widget_set_margin_top(cko_boxC, cko_margin);
	gtk_widget_set_margin_bottom(cko_boxC, cko_margin);
	gtk_box_set_spacing(GTK_BOX(cko_boxC), cko_boxC_space);

	gtk_grid_set_row_spacing(GTK_GRID(cko_grid_num), cko_grid_num_space);
	gtk_grid_set_column_spacing(GTK_GRID(cko_grid_num), cko_grid_num_space);
	gtk_widget_set_margin_top(cko_grid_num, cko_margin);
	gtk_widget_set_margin_bottom(cko_grid_num, cko_margin);

	gtk_widget_set_size_request(cko_close_btn, cko_bt_dimention/2, cko_bt_dimention/2);
}

static void view_windowCko(){
	gtk_widget_show(windowCko);
}

static void start_windowCko(){
	int argc; char **argv;
	//gtk_widget_set_opacity(window, 0.5);
	//gtk_widget_set_sensitive(window, FALSE);
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowCko_init();
	gtk_windowCko_setAttrib();
	gtk_windowCko_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowCko);
}

void gtk_windowCko_connect(){
	g_signal_connect(windowCko, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(cko_close_btn, "clicked", G_CALLBACK(close_windowCko), NULL);
}

static void close_windowCko(){
	gtk_widget_hide(windowCko);
}
	
//static void cko_setOrder(GtkWidget *numWidget){
	//char myNumber[10];

	//strcpy(myNumber, (const char *)gtk_button_get_label(GTK_BUTTON(numWidget)));
	//if (strlen(input_number_text)<12 || myNumber[0]=='D'){
		//if(myNumber[0]!='D'){
			//input_number_text[strlen(input_number_text)]=myNumber[0];
			//input_number_text[strlen(input_number_text)]=0;
		//}
		//else input_number_text[strlen(input_number_text)-1]=0;

		//char format[200];
		//char markup_text[200];

		//if(strlen(input_number_text)>0){
			//strcpy(format, "<span foreground='#000'><b>\%s</b></span>");
			//strcpy(markup_text, g_markup_printf_escaped (format, input_number_text));
		//}
		//else{
			//strcpy(format, "<span foreground='#777777'><b>\%s</b></span>");
			//strcpy(markup_text, g_markup_printf_escaped (format, "000104xxxxxx"));
		//}
		//gtk_label_set_markup(GTK_LABEL(cko_number), (const gchar *) markup_text);
	//}
//}

//windowBarcode
void gtk_windowBcd_init(){
	windowBarcode=GTK_WIDGET(gtk_builder_get_object(builder, "windowBarcode"));
	
	bcd_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "bcd_boxC"));
	bcd_grid_num=GTK_WIDGET(gtk_builder_get_object(builder, "bcd_grid_num"));
	bcd_imgBox=GTK_WIDGET(gtk_builder_get_object(builder, "bcd_imgBox"));
	
	bcd_img=GTK_WIDGET(gtk_builder_get_object(builder, "bcd_img"));
	
	bcd_close_btn=GTK_WIDGET(gtk_builder_get_object(builder, "bcd_close_btn"));
}

void gtk_windowBcd_setAttrib(){
	gtk_window_set_position(GTK_WINDOW(windowBarcode), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_widget_set_name(windowBarcode, "windowBarcode");

	gtk_widget_set_name(bcd_grid_num, "bcd_grid_num");
	gtk_widget_set_name(bcd_imgBox, "bcd_imgBox");
	gtk_widget_set_name(bcd_img, "bcd_img");
	
	gtk_widget_set_name(bcd_close_btn, "bcd_close_btn");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	////set dimention
	int imWidth, imHight;
	imWidth=imHight=screenWidth/7;
	gtk_image_opt(bcd_imgBox, "img/qr_code_PNG.png", imWidth, imHight, 0);
	int bcd_margin = screenWidth/60;
	int bcd_boxC_space = screenWidth/40;
	int bcd_bt_dimention = screenWidth/19;
	int bcd_grid_num_space = screenWidth/80;

	gtk_widget_set_margin_start(bcd_boxC, bcd_margin);
	gtk_widget_set_margin_end(bcd_boxC, bcd_margin);
	gtk_widget_set_margin_top(bcd_boxC, bcd_margin);
	gtk_widget_set_margin_bottom(bcd_boxC, bcd_margin);
	gtk_box_set_spacing(GTK_BOX(bcd_boxC), bcd_boxC_space);

	gtk_grid_set_row_spacing(GTK_GRID(bcd_grid_num), bcd_grid_num_space);
	gtk_grid_set_column_spacing(GTK_GRID(bcd_grid_num), bcd_grid_num_space);
	gtk_widget_set_margin_top(bcd_grid_num, bcd_margin);
	gtk_widget_set_margin_bottom(bcd_grid_num, bcd_margin);

	gtk_widget_set_size_request(bcd_close_btn, bcd_bt_dimention/2, bcd_bt_dimention/2);
}

static void view_windowBcd(){
	gtk_widget_show(windowBarcode);
}

static void start_windowBcd(){
	int argc; char **argv;
	//gtk_widget_set_opacity(window, 0.5);
	//gtk_widget_set_sensitive(window, FALSE);
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowBcd_init();
	gtk_windowBcd_setAttrib();
	gtk_windowBcd_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowBarcode);
}

void gtk_windowBcd_connect(){
	g_signal_connect(windowBarcode, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(bcd_close_btn, "clicked", G_CALLBACK(close_windowBcd), NULL);
}

static void close_windowBcd(){
	gtk_widget_hide(windowBarcode);
}
