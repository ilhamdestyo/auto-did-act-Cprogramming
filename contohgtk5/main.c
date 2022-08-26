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
GtkWidget *bt1, *bt2, *bt3, *bt4, *bt5, *bt6, *bt7, *bt8, *bt9, *bt10;
GtkWidget *bt1_c, *bt2_c,  *bt3_c, *bt4_c, *bt5_c, *bt6_c, *bt7_c, *bt8_c, *bt9_c, *bt10_c;
GtkWidget *logo_name, *bt1_imLogo, *bt2_imLogo, *bt3_imLogo, *bt4_imLogo, *bt5_imLogo, *bt6_imLogo, *bt7_imLogo, *bt8_imLogo, *bt9_imLogo, *bt10_imLogo;
GtkWidget *main_label, *bt_lb1, *bt_lb2, *bt_lb3, *bt_lb4, *bt_lb5, *bt_lb6, *bt_lb7, *bt_lb8, *bt_lb9, *bt_lb10;

//windowPulsa/Data
GtkWidget *windowPud;
GtkWidget *pud_boxC, *pud_boxC_main, *pud_menuGrid;
GtkWidget *pud_imLogo, *pud_imgKembali;
GtkWidget *pud_bt_main, *pud_menuBox_bt_kembali,*pud_menu_bt1, *pud_menu_bt2;
GtkWidget *pud_boxC_label, *pud_menu_bt1_lbl, *pud_menu_bt2_lbl;

//windowPulsa
GtkWidget *windowPulsa;
GtkWidget *pulsa_boxC, *pulsa_boxC_main, *pulsa_menuGrid;
GtkWidget *pulsa_imLogo, *pulsa_imgKembali, *pulsa_menu_bt_im1, *pulsa_menu_bt_im2, *pulsa_menu_bt_im3, *pulsa_menu_bt_im4, *pulsa_menu_bt_im5;
GtkWidget *pulsa_bt_main, *pulsa_menuBox_bt_kembali,*pulsa_menu_bt1, *pulsa_menu_bt2, *pulsa_menu_bt3, *pulsa_menu_bt4, *pulsa_menu_bt5;
GtkWidget *pulsa_boxC_label, *pulsa_menuBox_label;

//windowNominalPulsa
GtkWidget *windowNompul;
GtkWidget *nompul_boxC, *nompul_boxC_main, *nompul_menuGrid;
GtkWidget *nompul_imLogo, *nompul_imgKembali, *nompul_provider_logo;
GtkWidget *nompul_bt_main, *nompul_menuBox_bt_kembali,*nompul_menu_bt1, *nompul_menu_bt2, *nompul_menu_bt3, *nompul_menu_bt4, *nompul_menu_bt5;
GtkWidget *nompul_boxC_label, *nompul_menu_bt1_lbl, *nompul_menu_bt2_lbl, *nompul_menu_bt3_lbl, *nompul_menu_bt4_lbl, *nompul_menu_bt5_lbl;
GtkWidget *nompul_menuBox_label;

//windowNumberInput
GtkWidget *windowNumi;
GtkWidget *numi_boxC, *numi_boxC_main, *numi_menuGrid;
GtkWidget *numi_imLogo, *numi_imgKembali, *numi_provider_logo;
GtkWidget *numi_grid_num, *numi_numBox;
GtkWidget *numi_bt_main, *numi_menuBox_bt_kembali, *numi_num_bt1, *numi_num_bt2, *numi_num_bt3, *numi_num_bt4, *numi_num_bt5, *numi_num_bt6, *numi_num_bt7, *numi_num_bt8, *numi_num_bt9, *numi_num_bt0, *numi_num_btDel, *numi_num_btEnt;
GtkWidget *numi_boxC_label, *numi_menuBox_label, *numi_number;

//windowMetodePembayaran
GtkWidget *windowMpb;
GtkWidget *mpb_boxC, *mpb_boxC_main, *mpb_menuGrid;
GtkWidget *mpb_imLogo, *mpb_provider_logo, *mpb_imgKembali;
GtkWidget *mpb_bt_main, *mpb_menuBox_bt_kembali,*mpb_menu_bt1, *mpb_menu_bt2;
GtkWidget *mpb_boxC_label, *mpb_menu_bt1_lbl, *mpb_menu_bt2_lbl;

//windowPaketInternet
GtkWidget *windowPnet;
GtkWidget *pnet_boxC, *pnet_boxC_main, *pnet_menuGrid;
GtkWidget *pnet_imLogo, *pnet_imgKembali, *pnet_provider_logo;
GtkWidget *pnet_bt_main, *pnet_menuBox_bt_kembali,*pnet_menu_bt1, *pnet_menu_bt2, *pnet_menu_bt3, *pnet_menu_bt4, *pnet_menu_bt5, *pnet_menu_bt6, *pnet_menu_bt7, *pnet_menu_bt8;
GtkWidget *pnet_boxC_label, *pnet_menu_bt1_lbl, *pnet_menu_bt2_lbl, *pnet_menu_bt3_lbl, *pnet_menu_bt4_lbl, *pnet_menu_bt5_lbl, *pnet_menu_bt6_lbl, *pnet_menu_bt7_lbl, *pnet_menu_bt8_lbl;
GtkWidget *pnet_menuBox_label;

//windowListrik
GtkWidget *windowListrik;
GtkWidget *listrik_boxC, *listrik_boxC_main, *listrik_menuGrid;
GtkWidget *listrik_imLogo, *listrik_imgKembali, *listrik_menu_bt_im1, *listrik_menu_bt_im2, *listrik_menu_bt_im3;
GtkWidget *listrik_bt_main, *listrik_menuBox_bt_kembali,*listrik_menu_bt1, *listrik_menu_bt2, *listrik_menu_bt3;
GtkWidget *listrik_boxC_label, *listrik_menuBox_label;

//windowInternet/TV
GtkWidget *windowIntv;
GtkWidget *intv_boxC, *intv_boxC_main, *intv_menuGrid;
GtkWidget *intv_imLogo, *intv_imgKembali, *intv_menu_bt_im1, *intv_menu_bt_im2, *intv_menu_bt_im3, *intv_menu_bt_im4, *intv_menu_bt_im5, *intv_menu_bt_im6, *intv_menu_bt_im7, *intv_menu_bt_im8, *intv_menu_bt_im9;
GtkWidget *intv_bt_main, *intv_menuBox_bt_kembali,*intv_menu_bt1, *intv_menu_bt2, *intv_menu_bt3, *intv_menu_bt4, *intv_menu_bt5, *intv_menu_bt6, *intv_menu_bt7, *intv_menu_bt8, *intv_menu_bt9;
GtkWidget *intv_boxC_label, *intv_menuBox_label;

//windowCekOrder
GtkWidget *windowCko;
GtkWidget *cko_boxC, *cko_grid_num, *cko_numBox;
GtkWidget *cko_close_btn, *cko_num_bt1, *cko_num_bt2, *cko_num_bt3, *cko_num_bt4, *cko_num_bt5, *cko_num_bt6, *cko_num_bt7, *cko_num_bt8, *cko_num_bt9, *cko_num_bt0, *cko_num_btDel, *cko_num_btEnt;
GtkWidget *cko_number;

//windowPajak
GtkWidget *windowPajak;
GtkWidget *pajak_boxC, *pajak_boxC_main, *pajak_menuGrid;
GtkWidget *pajak_imLogo, *pajak_imgKembali;
GtkWidget *pajak_bt_main, *pajak_menuBox_bt_kembali, *pajak_bt_ok;
GtkWidget *pajak_boxC_label, *pajak_menuBox_label, *pajak_lbl_jenis_produk, *pajak_bt_ok_label;
GtkWidget *pajak_combo_pilihan, *pajak_combo_jenis_produk;

void gtk_mainWindow_init();
void gtk_mainWindow_setAttrib();
void gtk_mainWindow_connect();

static void start_windowPud();
static void start_windowListrik();
static void start_windowPnet();
static void start_windowNompul();
static void start_windowIntv();
static void start_windowCko();
static void start_windowPajak();
static void start_windowNumi();
static void start_windowMpb();

static void view_windowPud();
static void view_windowListrik();
static void view_windowIntv();
static void view_windowCko();
static void view_windowPajak();
static void view_windowNumi();
static void view_windowMpb();

void gtk_windowPud_init();
void gtk_windowPud_setAttrib();
void gtk_windowPud_connect();
static void start_windowPulsaData(GtkWidget *widgetPud);
static void close_windowPud();

void gtk_windowPulsa_init();
void gtk_windowPulsa_setAttrib();
void gtk_windowPulsa_connect();
static void view_windowNompul_or_pnet(GtkWidget *providerWidget, int argc, char **argv);
static void close_windowPulsa();
static void pulsa_go_to_main();

void gtk_windowNompul_init();
void gtk_windowNompul_setAttrib();
void gtk_windowNompul_connect();
static void close_windowNompul();
static void nompul_go_to_main();

void gtk_windowNumi_init();
void gtk_windowNumi_setAttrib();
void gtk_windowNumi_connect();
static void numi_setNumber(GtkWidget *numWidget);
static void close_windowNumi();
static void numi_go_to_main();

void gtk_windowMpb_init();
void gtk_windowMpb_setAttrib();
void gtk_windowMpb_connect();
static void close_windowMpb();
static void mpb_go_to_main();

void gtk_windowPnet_init();
void gtk_windowPnet_setAttrib();
void gtk_windowPnet_connect();
static void close_windowPnet();
static void pnet_go_to_main();

void gtk_windowListrik_init();
void gtk_windowListrik_setAttrib();
void gtk_windowListrik_connect();
static void close_windowListrik();
static void listrik_go_to_main();

void gtk_windowIntv_init();
void gtk_windowIntv_setAttrib();
void gtk_windowIntv_connect();
static void close_windowIntv();
static void intv_go_to_main();

void gtk_windowCko_init();
void gtk_windowCko_setAttrib();
void gtk_windowCko_connect();
static void close_windowCko();
static void cko_setNumber(GtkWidget *numWidget);

void gtk_windowPajak_init();
void gtk_windowPajak_setAttrib();
void gtk_windowPajak_connect();
static void close_windowPajak();
static void pajak_go_to_main();
static void set_attrib_to_numi();

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
	
	start_windowPud();
	start_windowNompul();
	start_windowPnet();
	start_windowListrik();
	start_windowIntv();
	start_windowCko();
	start_windowPajak();
	start_windowNumi();
	start_windowMpb();
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

	//bt_C
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

	//label
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
	bt_lb10=GTK_WIDGET(gtk_builder_get_object(builder, "bt_lb10"));
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
	int imWidth, imHight;
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
	g_signal_connect(bt1, "clicked", G_CALLBACK (view_windowPud), NULL);
	g_signal_connect(bt4, "clicked", G_CALLBACK (view_windowListrik), NULL);
	g_signal_connect(bt7, "clicked", G_CALLBACK (view_windowIntv), NULL);
	g_signal_connect(bt9, "clicked", G_CALLBACK (view_windowPajak), NULL);
	g_signal_connect(cek_order_btn, "clicked", G_CALLBACK (view_windowCko), NULL);
}

static void start_windowPud(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowPud_init();
	gtk_windowPud_setAttrib();
	gtk_windowPud_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(windowPud);
	gtk_widget_hide(windowPud);
}

static void start_windowNompul(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowNompul_init();
	gtk_windowNompul_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(windowNompul);
	gtk_widget_hide(windowNompul);
}

static void start_windowPnet(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowPnet_init();
	gtk_windowPnet_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(windowPnet);
	gtk_widget_hide(windowPnet);
}

static void start_windowListrik(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowListrik_init();
	gtk_windowListrik_setAttrib();
	gtk_windowListrik_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowListrik);
}

static void start_windowIntv(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowIntv_init();
	gtk_windowIntv_setAttrib();
	gtk_windowIntv_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowIntv);
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

static void start_windowPajak(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowPajak_init();
	gtk_windowPajak_setAttrib();
	gtk_windowPajak_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowPajak);
}

static void start_windowNumi(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowNumi_init();
	gtk_windowNumi_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowNumi);
}

static void start_windowMpb(){
	int argc; char **argv;
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowMpb_init();
	gtk_windowMpb_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_hide(windowMpb);
}

static void view_windowPud(){
	gtk_widget_show(windowPud);
}
static void view_windowListrik(){
	gtk_widget_show(windowListrik);
}
static void view_windowIntv(){
	gtk_widget_show(windowIntv);
}
static void view_windowCko(){
	gtk_widget_show(windowCko);
}
static void view_windowPajak(){
	gtk_widget_show(windowPajak);
}
static void view_windowNumi(){
	gtk_windowNumi_setAttrib();
	gtk_widget_show(windowNumi);
}
static void view_windowMpb(){
	gtk_windowMpb_setAttrib();
	gtk_widget_show(windowMpb);
}

//windowPud
void gtk_windowPud_init(){
	windowPud=GTK_WIDGET(gtk_builder_get_object(builder, "windowPud"));

	pud_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "pud_boxC"));
	pud_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "pud_boxC_main"));
	pud_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "pud_menuGrid"));

	pud_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "pud_bt_main"));
	pud_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "pud_menu_bt1"));
	pud_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "pud_menu_bt2"));
	pud_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "pud_menuBox_bt_kembali"));

	pud_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "pud_imLogo"));
	pud_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "pud_imgKembali"));

	pud_menu_bt1_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pud_menu_bt1_lbl"));
	pud_menu_bt2_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pud_menu_bt2_lbl"));

	pud_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "pud_boxC_label"));
}

void gtk_windowPud_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowPud));

	gtk_widget_set_name(windowPud, "windowPud");

	gtk_widget_set_name(pud_bt_main, "pud_bt_main");
	gtk_widget_set_name(pud_menuBox_bt_kembali, "pud_menuBox_bt_kembali");
	gtk_widget_set_name(pud_menu_bt1, "pud_menu_bt1");
	gtk_widget_set_name(pud_menu_bt2, "pud_menu_bt2");

	gtk_widget_set_name(pud_imLogo, "pud_imLogo");
	gtk_widget_set_name(pud_menu_bt1_lbl, "pud_menu_bt1_lbl");
	gtk_widget_set_name(pud_menu_bt2_lbl, "pud_menu_bt2_lbl");

	gtk_widget_set_name(pud_boxC_label, "pud_boxC_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	//set dimention
	gtk_widget_set_margin_start(pud_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(pud_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(pud_boxC, boxC_space);
	gtk_widget_set_margin_bottom(pud_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(pud_boxC), nboxC_space);
	gtk_widget_set_size_request(pud_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(pud_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(pud_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(pud_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(pud_menuGrid), gspace_col);
	gtk_widget_set_margin_top(pud_menuGrid, boxC_space);

	gtk_image_opt(pud_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(pud_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);

	int btn_width = screenWidth/8;
	int btn_hight = screenWidth/8;
	gtk_widget_set_size_request(pud_menu_bt1, btn_width,btn_hight);
	gtk_widget_set_size_request(pud_menu_bt2, btn_width,btn_hight);
}

void gtk_windowPud_connect(){
	g_signal_connect(windowPud, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(pud_menu_bt1, "clicked", G_CALLBACK (start_windowPulsaData), NULL);
	g_signal_connect(pud_menu_bt2, "clicked", G_CALLBACK (start_windowPulsaData), NULL);
	g_signal_connect(pud_bt_main, "clicked", G_CALLBACK (close_windowPud), NULL);
	g_signal_connect(pud_menuBox_bt_kembali, "clicked", G_CALLBACK (close_windowPud), NULL);
}

//yang perlu diubah
static void start_windowPulsaData(GtkWidget *widgetPud){
	int argc;
	char **argv;
	char jenisPD[100];
	strcpy(jenisPD, (const char *)gtk_widget_get_name(widgetPud));
	if(jenisPD[strlen(jenisPD)-1]=='1'){
		strcpy(jenisPulsa_or_Data, "Pulsa Reguler");
		strcpy(jenis_PD_txt, "Pilihan Nominal Pulsa ");
	}
	else{
		strcpy(jenisPulsa_or_Data, "Paket Internet");
		strcpy(jenis_PD_txt, "Pilihan Paket Internet ");
	}
	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();

	gtk_windowPulsa_init();
	gtk_windowPulsa_setAttrib();
	gtk_windowPulsa_connect();

	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(windowPulsa);
	g_object_unref(builder);
	gtk_main();
}

static void close_windowPud(){
	gtk_widget_hide(windowPud);
}

//windowPulsa
void gtk_windowPulsa_init(){
	windowPulsa=GTK_WIDGET(gtk_builder_get_object(builder, "windowPulsa"));

	pulsa_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_boxC"));
	pulsa_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_boxC_main"));
	pulsa_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menuGrid"));

	pulsa_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_bt_main"));
	pulsa_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt1"));
	pulsa_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt2"));
	pulsa_menu_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt3"));
	pulsa_menu_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt4"));
	pulsa_menu_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt5"));
	pulsa_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menuBox_bt_kembali"));

	pulsa_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_imLogo"));
	pulsa_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_imgKembali"));
	pulsa_menu_bt_im1=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt_im1"));
	pulsa_menu_bt_im2=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt_im2"));
	pulsa_menu_bt_im3=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt_im3"));
	pulsa_menu_bt_im4=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt_im4"));
	pulsa_menu_bt_im5=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menu_bt_im5"));

	pulsa_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_boxC_label"));
	pulsa_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "pulsa_menuBox_label"));
}

void gtk_windowPulsa_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowPulsa));

	gtk_widget_set_name(windowPulsa, "windowPulsa");

	gtk_widget_set_name(pulsa_bt_main, "pulsa_bt_main");
	gtk_widget_set_name(pulsa_menuBox_bt_kembali, "pulsa_menuBox_bt_kembali");
	gtk_widget_set_name(pulsa_menu_bt1, "pulsa_menu_bt1");
	gtk_widget_set_name(pulsa_menu_bt2, "pulsa_menu_bt2");
	gtk_widget_set_name(pulsa_menu_bt3, "pulsa_menu_bt3");
	gtk_widget_set_name(pulsa_menu_bt4, "pulsa_menu_bt4");
	gtk_widget_set_name(pulsa_menu_bt5, "pulsa_menu_bt5");

	gtk_widget_set_name(pulsa_imLogo, "pulsa_imLogo");

	gtk_widget_set_name(pulsa_boxC_label, "pulsa_boxC_label");
	gtk_widget_set_name(pulsa_menuBox_label, "pulsa_menuBox_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_label_set_text(GTK_LABEL(pulsa_boxC_label), jenisPulsa_or_Data);

	//set dimention
	int imWidth, imHight;
	imWidth=imHight=screenWidth/7;
	gtk_image_opt(pulsa_menu_bt_im1, "img/btnTelkomsel.png", imWidth, imHight, 0);
	gtk_image_opt(pulsa_menu_bt_im2, "img/btnSmartfren.png", imWidth, imHight, 0);
	gtk_image_opt(pulsa_menu_bt_im3, "img/btnXL.png", imWidth, imHight, 0);
	gtk_image_opt(pulsa_menu_bt_im4, "img/btnIndosat.png", imWidth, imHight, 0);
	gtk_image_opt(pulsa_menu_bt_im5, "img/btnTri.png", imWidth, imHight, 0);

	gtk_widget_set_margin_top(pulsa_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(pulsa_boxC_label, boxC_label_margin);

	gtk_widget_set_margin_start(pulsa_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(pulsa_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(pulsa_boxC, boxC_space);
	gtk_widget_set_margin_bottom(pulsa_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(pulsa_boxC), nboxC_space);
	gtk_widget_set_size_request(pulsa_boxC_main, boxC_main_width, -1);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(pulsa_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(pulsa_menuGrid), gspace_col);
	gtk_widget_set_margin_top(pulsa_menuGrid, boxC_space);

	gtk_image_opt(pulsa_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(pulsa_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);
}

void gtk_windowPulsa_connect(){
	g_signal_connect(windowPulsa, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(pulsa_menu_bt1, "clicked", G_CALLBACK(view_windowNompul_or_pnet), NULL);
	g_signal_connect(pulsa_menu_bt2, "clicked", G_CALLBACK(view_windowNompul_or_pnet), NULL);
	g_signal_connect(pulsa_menu_bt3, "clicked", G_CALLBACK(view_windowNompul_or_pnet), NULL);
	g_signal_connect(pulsa_menu_bt4, "clicked", G_CALLBACK(view_windowNompul_or_pnet), NULL);
	g_signal_connect(pulsa_menu_bt5, "clicked", G_CALLBACK(view_windowNompul_or_pnet), NULL);
	g_signal_connect(pulsa_bt_main, "clicked", G_CALLBACK (pulsa_go_to_main), NULL);
	g_signal_connect(pulsa_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowPulsa), NULL);
}


//yang perlu diubah
static void view_windowNompul_or_pnet(GtkWidget *providerWidget, int argc, char **argv){
	char jenisProvider[20];
	strcpy(jenisProvider, (const char *)gtk_widget_get_name(providerWidget));
	if (jenisProvider[strlen(jenisProvider)-1]=='1'){
		strcpy(pulsa_provider_text, "Telkomsel");
		strcpy(provider_im, "img/Telkomsel_provider.png");
	}
	else if (jenisProvider[strlen(jenisProvider)-1]=='2'){
		strcpy(pulsa_provider_text, "Smartfren");
		strcpy(provider_im, "img/Smartfren_provider.png");
	}
	else if (jenisProvider[strlen(jenisProvider)-1]=='3'){
		strcpy(pulsa_provider_text, "XL");
		strcpy(provider_im, "img/XL_provider.png");
	}
	else if (jenisProvider[strlen(jenisProvider)-1]=='4'){
		strcpy(pulsa_provider_text, "Indosat");
		strcpy(provider_im, "img/Indosat_provider.png");
	}
	else if (jenisProvider[strlen(jenisProvider)-1]=='5'){
		strcpy(pulsa_provider_text, "Tri");
		strcpy(provider_im, "img/Tri_provider.png");
	}
	if(jenisPulsa_or_Data[strlen(jenisPulsa_or_Data)-1]=='r'){
		strcpy(jenis_PD_txt, "Pilihan Nominal Pulsa ");
	}
	else{
		strcpy(jenis_PD_txt, "Pilihan Paket Internet ");
	}
	strcat(jenis_PD_txt, pulsa_provider_text);
	jenis_PD_txt[strlen(jenis_PD_txt)]=0;

	gtk_init(&argc, &argv);
	gtk_builder_and_attrib_init();
	if(jenisPulsa_or_Data[strlen(jenisPulsa_or_Data)-1]=='r'){
		gtk_windowNompul_init();
		gtk_windowNompul_setAttrib();
		gtk_windowNompul_connect();

		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show(windowNompul);
	}
	else{
		gtk_windowPnet_init();
		gtk_windowPnet_setAttrib();
		gtk_windowPnet_connect();

		gtk_builder_connect_signals(builder, NULL);
		gtk_widget_show(windowPnet);
	}
}

static void close_windowPulsa(){
	gtk_widget_hide(windowPulsa);
}

static void pulsa_go_to_main(){
	gtk_widget_hide(windowPud);
	gtk_widget_hide(windowPulsa);
}

//windowNominalPulsa
void gtk_windowNompul_init(){
	windowNompul=GTK_WIDGET(gtk_builder_get_object(builder, "windowNompul"));

	nompul_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_boxC"));
	nompul_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_boxC_main"));
	nompul_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menuGrid"));

	nompul_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_bt_main"));
	nompul_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt1"));
	nompul_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt2"));
	nompul_menu_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt3"));
	nompul_menu_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt4"));
	nompul_menu_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt5"));
	nompul_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menuBox_bt_kembali"));

	nompul_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_imLogo"));
	nompul_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_imgKembali"));
	nompul_provider_logo=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_provider_logo"));

	nompul_menu_bt1_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt1_lbl"));
	nompul_menu_bt2_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt2_lbl"));
	nompul_menu_bt3_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt3_lbl"));
	nompul_menu_bt4_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt4_lbl"));
	nompul_menu_bt5_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menu_bt5_lbl"));

	nompul_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_boxC_label"));
	nompul_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "nompul_menuBox_label"));
}

void gtk_windowNompul_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowNompul));

	gtk_widget_set_name(windowNompul, "windowNompul");

	gtk_widget_set_name(nompul_bt_main, "nompul_bt_main");
	gtk_widget_set_name(nompul_menuBox_bt_kembali, "nompul_menuBox_bt_kembali");
	gtk_widget_set_name(nompul_menu_bt1, "nompul_menu_bt1");
	gtk_widget_set_name(nompul_menu_bt2, "nompul_menu_bt2");
	gtk_widget_set_name(nompul_menu_bt3, "nompul_menu_bt3");
	gtk_widget_set_name(nompul_menu_bt4, "nompul_menu_bt4");
	gtk_widget_set_name(nompul_menu_bt5, "nompul_menu_bt5");

	gtk_widget_set_name(nompul_imLogo, "nompul_imLogo");
	gtk_widget_set_name(nompul_provider_logo, "nompul_provider_logo");

	gtk_widget_set_name(nompul_menu_bt1_lbl, "nompul_menu_bt1_lbl");
	gtk_widget_set_name(nompul_menu_bt2_lbl, "nompul_menu_bt2_lbl");
	gtk_widget_set_name(nompul_menu_bt3_lbl, "nompul_menu_bt3_lbl");
	gtk_widget_set_name(nompul_menu_bt4_lbl, "nompul_menu_bt4_lbl");
	gtk_widget_set_name(nompul_menu_bt5_lbl, "nompul_menu_bt5_lbl");

	gtk_widget_set_name(nompul_boxC_label, "nompul_boxC_label");
	gtk_widget_set_name(nompul_menuBox_label, "nompul_menuBox_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_label_set_text(GTK_LABEL(nompul_menuBox_label), (const gchar*)jenis_PD_txt);

	//set dimention
	gtk_widget_set_margin_start(nompul_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(nompul_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(nompul_boxC, boxC_space);
	gtk_widget_set_margin_bottom(nompul_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(nompul_boxC), nboxC_space);
	gtk_widget_set_size_request(nompul_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(nompul_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(nompul_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(nompul_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(nompul_menuGrid), gspace_col);
	gtk_widget_set_margin_top(nompul_menuGrid, boxC_space);

	gtk_image_opt(nompul_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(nompul_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);

	int pvLogo_width = screenWidth/8;
	int pvLogo_hight = screenWidth/8;
	int pvTopMargin = screenHight/7;
	gtk_image_opt(nompul_provider_logo, provider_im, pvLogo_width, pvLogo_width, 0);
	gtk_widget_set_margin_top(nompul_provider_logo, pvTopMargin);

	int bt_width = screenWidth/7;
	int bt_hight = screenHight/7;
	gtk_widget_set_size_request(nompul_menu_bt1, bt_width, bt_hight);
	gtk_widget_set_size_request(nompul_menu_bt2, bt_width, bt_hight);
	gtk_widget_set_size_request(nompul_menu_bt3, bt_width, bt_hight);
	gtk_widget_set_size_request(nompul_menu_bt4, bt_width, bt_hight);
	gtk_widget_set_size_request(nompul_menu_bt5, bt_width, bt_hight);
}

void gtk_windowNompul_connect(){
	g_signal_connect(windowNompul, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(nompul_menu_bt1, "clicked", G_CALLBACK(view_windowNumi), NULL);
	g_signal_connect(nompul_bt_main, "clicked", G_CALLBACK (nompul_go_to_main), NULL);
	g_signal_connect(nompul_menuBox_bt_kembali, "clicked", G_CALLBACK (close_windowNompul), NULL);
}

static void close_windowNompul(){
	gtk_widget_hide(windowNompul);
}

static void nompul_go_to_main(){
	gtk_widget_hide(windowNompul);
	gtk_widget_hide(windowPulsa);
	gtk_widget_hide(windowPud);
}

//Window Number Input
void gtk_windowNumi_init(){
	windowNumi=GTK_WIDGET(gtk_builder_get_object(builder, "windowNumi"));

	numi_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "numi_boxC"));
	numi_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "numi_boxC_main"));
	numi_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "numi_menuGrid"));

	numi_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "numi_imLogo"));
	numi_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "numi_imgKembali"));
	numi_provider_logo=GTK_WIDGET(gtk_builder_get_object(builder, "numi_provider_logo"));

	numi_grid_num=GTK_WIDGET(gtk_builder_get_object(builder, "numi_grid_num"));
	numi_numBox=GTK_WIDGET(gtk_builder_get_object(builder, "numi_numBox"));

	numi_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "numi_bt_main"));
	numi_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "numi_menuBox_bt_kembali"));
	numi_num_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt1"));
	numi_num_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt2"));
	numi_num_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt3"));
	numi_num_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt4"));
	numi_num_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt5"));
	numi_num_bt6=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt6"));
	numi_num_bt7=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt7"));
	numi_num_bt8=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt8"));
	numi_num_bt9=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt9"));
	numi_num_bt0=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_bt0"));
	numi_num_btDel=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_btDel"));
	numi_num_btEnt=GTK_WIDGET(gtk_builder_get_object(builder, "numi_num_btEnt"));

	numi_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "numi_menuBox_label"));
	numi_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "numi_boxC_label"));
	numi_number=GTK_WIDGET(gtk_builder_get_object(builder, "numi_number"));
}
void gtk_windowNumi_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowNumi));

	gtk_widget_set_name(windowNumi, "windowNumi");

	gtk_widget_set_name(numi_imLogo, "numi_imLogo");
	gtk_widget_set_name(numi_provider_logo, "numi_provider_logo");
	
	gtk_widget_set_name(numi_grid_num, "numi_grid_num");
	gtk_widget_set_name(numi_numBox, "numi_numBox");

	gtk_widget_set_name(numi_bt_main, "numi_bt_main");
	gtk_widget_set_name(numi_menuBox_bt_kembali, "numi_menuBox_bt_kembali");
	gtk_widget_set_name(numi_num_bt1, "numi_num_bt1");
	gtk_widget_set_name(numi_num_bt2, "numi_num_bt2");
	gtk_widget_set_name(numi_num_bt3, "numi_num_bt3");
	gtk_widget_set_name(numi_num_bt4, "numi_num_bt4");
	gtk_widget_set_name(numi_num_bt5, "numi_num_bt5");
	gtk_widget_set_name(numi_num_bt6, "numi_num_bt6");
	gtk_widget_set_name(numi_num_bt7, "numi_num_bt7");
	gtk_widget_set_name(numi_num_bt8, "numi_num_bt8");
	gtk_widget_set_name(numi_num_bt9, "numi_num_bt9");
	gtk_widget_set_name(numi_num_bt0, "numi_num_bt0");
	gtk_widget_set_name(numi_num_btDel, "numi_num_btDel");
	gtk_widget_set_name(numi_num_btEnt, "numi_num_btEnt");

	gtk_widget_set_name(numi_menuBox_label, "numi_menuBox_label");
	gtk_widget_set_name(numi_boxC_label, "numi_boxC_label");
	gtk_widget_set_name(numi_number, "numi_number");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	char markup_text[200];
	strcpy(markup_text, "<span foreground='#777777'><b>081234xxxxxx</b></span>");
	gtk_label_set_markup(GTK_LABEL(numi_number), (const gchar *) markup_text);

	memset(input_number_text, 0x00, 20*sizeof(char));

	//set dimention
	gtk_widget_set_margin_start(numi_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(numi_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(numi_boxC, boxC_space);
	gtk_widget_set_margin_bottom(numi_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(numi_boxC), nboxC_space);
	gtk_widget_set_size_request(numi_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(numi_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(numi_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(numi_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(numi_menuGrid), gspace_col);
	gtk_widget_set_margin_top(numi_menuGrid, boxC_space);

	gtk_image_opt(numi_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(numi_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);

	int pvLogo_width = screenWidth/8;
	int pvLogo_hight = screenWidth/8;
	int pvTopMargin = screenHight/7;
	gtk_image_opt(numi_provider_logo, provider_im, pvLogo_width, pvLogo_width, 0);
	gtk_widget_set_margin_top(numi_provider_logo, pvTopMargin);    
    
	int num_top_margin = screenHight/8;
	int num_width = (screenWidth/2) - (screenWidth/13);
	gtk_widget_set_margin_top(numi_numBox, num_top_margin);
	gtk_widget_set_size_request(numi_numBox, num_width, -1);

	int bt_width = screenWidth/16;
	int bt_hight = screenWidth/16;
	gtk_widget_set_size_request(numi_num_bt1, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt2, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt3, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt4, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt5, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt6, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt7, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt8, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt9, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_bt0, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_btDel, bt_width, bt_hight);
	gtk_widget_set_size_request(numi_num_btEnt, bt_width, bt_hight);
}
void gtk_windowNumi_connect(){
	g_signal_connect(windowNumi, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(numi_num_bt1, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt2, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt3, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt4, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt5, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt6, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt7, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt8, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt9, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_bt0, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_btDel, "clicked", G_CALLBACK(numi_setNumber), NULL);
	g_signal_connect(numi_num_btEnt, "clicked", G_CALLBACK(view_windowMpb), NULL);
	g_signal_connect(numi_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowNumi), NULL);
	g_signal_connect(numi_bt_main, "clicked", G_CALLBACK(numi_go_to_main), NULL);
}


//ini yang perlu diubah
static void numi_setNumber(GtkWidget *numWidget){
	char myNumber[10];
	strcpy(myNumber, (const char *)gtk_button_get_label(GTK_BUTTON(numWidget)));
	if (strlen(input_number_text)<12 || myNumber[0]=='D'){
		if(myNumber[0]!='D'){
			input_number_text[strlen(input_number_text)]=myNumber[0];
			input_number_text[strlen(input_number_text)]=0;
		}
		else input_number_text[strlen(input_number_text)-1]=0;

		char format[200];
		char markup_text[200];

		if(strlen(input_number_text)>0){
			strcpy(format, "<span foreground='#000'><b>\%s</b></span>");
			strcpy(markup_text, g_markup_printf_escaped (format, input_number_text));
		}
		else{
			strcpy(format, "<span foreground='#777777'><b>\%s</b></span>");
			strcpy(markup_text, g_markup_printf_escaped (format, "081234xxxxxx"));
		}
		gtk_label_set_markup(GTK_LABEL(numi_number), (const gchar *) markup_text);
	}
}

static void close_windowNumi(){
	gtk_widget_hide(windowNumi);
}

static void numi_go_to_main(){
	gtk_widget_hide(windowNumi);
	gtk_widget_hide(windowNompul);
	gtk_widget_hide(windowPulsa);
	gtk_widget_hide(windowPud);
}

//windowMpb
void gtk_windowMpb_init(){
	windowMpb=GTK_WIDGET(gtk_builder_get_object(builder, "windowMpb"));

	mpb_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_boxC"));
	mpb_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_boxC_main"));
	mpb_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_menuGrid"));

	mpb_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_bt_main"));
	mpb_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_menu_bt1"));
	mpb_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_menu_bt2"));
	mpb_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_menuBox_bt_kembali"));

	mpb_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_imLogo"));
	mpb_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_imgKembali"));
	mpb_provider_logo=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_provider_logo"));

	mpb_menu_bt1_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_menu_bt1_lbl"));
	mpb_menu_bt2_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_menu_bt2_lbl"));

	mpb_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "mpb_boxC_label"));
}

void gtk_windowMpb_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowMpb));

	gtk_widget_set_name(windowMpb, "windowMpb");

	gtk_widget_set_name(mpb_bt_main, "mpb_bt_main");
	gtk_widget_set_name(mpb_menuBox_bt_kembali, "mpb_menuBox_bt_kembali");
	gtk_widget_set_name(mpb_menu_bt1, "mpb_menu_bt1");
	gtk_widget_set_name(mpb_menu_bt2, "mpb_menu_bt2");

	gtk_widget_set_name(mpb_imLogo, "mpb_imLogo");
	gtk_widget_set_name(mpb_provider_logo, "mpb_provider_logo");

	gtk_widget_set_name(mpb_menu_bt1_lbl, "mpb_menu_bt1_lbl");
	gtk_widget_set_name(mpb_menu_bt2_lbl, "mpb_menu_bt2_lbl");

	gtk_widget_set_name(mpb_boxC_label, "mpb_boxC_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	//set dimention
	gtk_widget_set_margin_start(mpb_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(mpb_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(mpb_boxC, boxC_space);
	gtk_widget_set_margin_bottom(mpb_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(mpb_boxC), nboxC_space);
	gtk_widget_set_size_request(mpb_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(mpb_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(mpb_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(mpb_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(mpb_menuGrid), gspace_col);
	gtk_widget_set_margin_top(mpb_menuGrid, boxC_space);

	gtk_image_opt(mpb_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(mpb_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);

	int btn_width = screenWidth/8;
	int btn_hight = screenWidth/8;
	gtk_widget_set_size_request(mpb_menu_bt1, btn_width, btn_hight);
	gtk_widget_set_size_request(mpb_menu_bt2, btn_width, btn_hight);

	int pvLogo_width = screenWidth/8;
	int pvLogo_hight = screenWidth/8;
	int pvTopMargin = screenHight/7;
	gtk_image_opt(mpb_provider_logo, provider_im, pvLogo_width, pvLogo_hight, 0);
	gtk_widget_set_margin_top(mpb_provider_logo, pvTopMargin);
}

void gtk_windowMpb_connect(){
	g_signal_connect(windowMpb, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(mpb_bt_main, "clicked", G_CALLBACK (mpb_go_to_main), NULL);
	g_signal_connect(mpb_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowMpb), NULL);
}

static void close_windowMpb(){
	gtk_widget_hide(windowMpb);
}

static void mpb_go_to_main(){
	gtk_widget_hide(windowMpb);
	gtk_widget_hide(windowNumi);
	gtk_widget_hide(windowNompul);
	gtk_widget_hide(windowPulsa);
	gtk_widget_hide(windowPud);
}

//windowPaketInternet
void gtk_windowPnet_init(){
	windowPnet=GTK_WIDGET(gtk_builder_get_object(builder, "windowPnet"));

	pnet_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_boxC"));
	pnet_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_boxC_main"));
	pnet_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menuGrid"));

	pnet_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_bt_main"));
	pnet_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt1"));
	pnet_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt2"));
	pnet_menu_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt3"));
	pnet_menu_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt4"));
	pnet_menu_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt5"));
	pnet_menu_bt6=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt6"));
	pnet_menu_bt7=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt7"));
	pnet_menu_bt8=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt8"));
	pnet_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menuBox_bt_kembali"));

	pnet_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_imLogo"));
	pnet_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_imgKembali"));
	pnet_provider_logo=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_provider_logo"));

	pnet_menu_bt1_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt1_lbl"));
	pnet_menu_bt2_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt2_lbl"));
	pnet_menu_bt3_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt3_lbl"));
	pnet_menu_bt4_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt4_lbl"));
	pnet_menu_bt5_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt5_lbl"));
	pnet_menu_bt6_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt6_lbl"));
	pnet_menu_bt7_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt7_lbl"));
	pnet_menu_bt8_lbl=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menu_bt8_lbl"));

	pnet_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_boxC_label"));
	pnet_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "pnet_menuBox_label"));
}

void gtk_windowPnet_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowPnet));

	gtk_widget_set_name(windowPnet, "windowPnet");

	gtk_widget_set_name(pnet_bt_main, "pnet_bt_main");
	gtk_widget_set_name(pnet_menuBox_bt_kembali, "pnet_menuBox_bt_kembali");
	gtk_widget_set_name(pnet_menu_bt1, "pnet_menu_bt1");
	gtk_widget_set_name(pnet_menu_bt2, "pnet_menu_bt2");
	gtk_widget_set_name(pnet_menu_bt3, "pnet_menu_bt3");
	gtk_widget_set_name(pnet_menu_bt4, "pnet_menu_bt4");
	gtk_widget_set_name(pnet_menu_bt5, "pnet_menu_bt5");
	gtk_widget_set_name(pnet_menu_bt6, "pnet_menu_bt6");
	gtk_widget_set_name(pnet_menu_bt7, "pnet_menu_bt7");
	gtk_widget_set_name(pnet_menu_bt8, "pnet_menu_bt8");

	gtk_widget_set_name(pnet_imLogo, "pnet_imLogo");
	gtk_widget_set_name(pnet_provider_logo, "pnet_provider_logo");

	gtk_widget_set_name(pnet_menu_bt1_lbl, "pnet_menu_bt1_lbl");
	gtk_widget_set_name(pnet_menu_bt2_lbl, "pnet_menu_bt2_lbl");
	gtk_widget_set_name(pnet_menu_bt3_lbl, "pnet_menu_bt3_lbl");
	gtk_widget_set_name(pnet_menu_bt4_lbl, "pnet_menu_bt4_lbl");
	gtk_widget_set_name(pnet_menu_bt5_lbl, "pnet_menu_bt5_lbl");
	gtk_widget_set_name(pnet_menu_bt6_lbl, "pnet_menu_bt6_lbl");
	gtk_widget_set_name(pnet_menu_bt7_lbl, "pnet_menu_bt7_lbl");
	gtk_widget_set_name(pnet_menu_bt8_lbl, "pnet_menu_bt8_lbl");

	gtk_widget_set_name(pnet_boxC_label, "pnet_boxC_label");
	gtk_widget_set_name(pnet_menuBox_label, "pnet_menuBox_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_label_set_text(GTK_LABEL(pnet_menuBox_label), (const gchar*)jenis_PD_txt);

	//set dimention
	gtk_widget_set_margin_start(pnet_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(pnet_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(pnet_boxC, boxC_space);
	gtk_widget_set_margin_bottom(pnet_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(pnet_boxC), nboxC_space);
	gtk_widget_set_size_request(pnet_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(pnet_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(pnet_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(pnet_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(pnet_menuGrid), gspace_col);
	gtk_widget_set_margin_top(pnet_menuGrid, boxC_space);

	gtk_image_opt(pnet_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(pnet_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);

	int pvLogo_width = screenWidth/8;
	int pvLogo_hight = screenWidth/8;
	int pvTopMargin = screenHight/7;
	gtk_image_opt(pnet_provider_logo, provider_im, pvLogo_width, pvLogo_width, 0);
	gtk_widget_set_margin_top(pnet_provider_logo, pvTopMargin);

	int bt_width = screenWidth/8;
	int bt_hight = screenWidth/8;
	gtk_widget_set_size_request(pnet_menu_bt1, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt2, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt3, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt4, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt5, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt6, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt7, bt_width, bt_hight);
	gtk_widget_set_size_request(pnet_menu_bt8, bt_width, bt_hight);
}

void gtk_windowPnet_connect(){
	g_signal_connect(windowPnet, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(pnet_menu_bt1, "clicked", G_CALLBACK(start_windowNumi), NULL);
	g_signal_connect(pnet_bt_main, "clicked", G_CALLBACK (pnet_go_to_main), NULL);
	g_signal_connect(pnet_menuBox_bt_kembali, "clicked", G_CALLBACK (close_windowPnet), NULL);
}

static void close_windowPnet(){
	gtk_widget_hide(windowPnet);
}

static void pnet_go_to_main(){
	gtk_widget_hide(windowPnet);
	gtk_widget_hide(windowPulsa);
	gtk_widget_hide(windowPud);
}

//windowListrik
void gtk_windowListrik_init(){
	windowListrik=GTK_WIDGET(gtk_builder_get_object(builder, "windowListrik"));

	listrik_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_boxC"));
	listrik_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_boxC_main"));
	listrik_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menuGrid"));

	listrik_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_bt_main"));
	listrik_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menu_bt1"));
	listrik_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menu_bt2"));
	listrik_menu_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menu_bt3"));
	listrik_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menuBox_bt_kembali"));

	listrik_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_imLogo"));
	listrik_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_imgKembali"));
	listrik_menu_bt_im1=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menu_bt_im1"));
	listrik_menu_bt_im2=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menu_bt_im2"));
	listrik_menu_bt_im3=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menu_bt_im3"));

	listrik_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_boxC_label"));
	listrik_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "listrik_menuBox_label"));
}

void gtk_windowListrik_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowListrik));

	gtk_widget_set_name(windowListrik, "windowListrik");

	gtk_widget_set_name(listrik_bt_main, "listrik_bt_main");
	gtk_widget_set_name(listrik_menuBox_bt_kembali, "listrik_menuBox_bt_kembali");
	gtk_widget_set_name(listrik_menu_bt1, "listrik_menu_bt1");
	gtk_widget_set_name(listrik_menu_bt2, "listrik_menu_bt2");
	gtk_widget_set_name(listrik_menu_bt3, "listrik_menu_bt3");

	gtk_widget_set_name(listrik_imLogo, "listrik_imLogo");

	gtk_widget_set_name(listrik_boxC_label, "listrik_boxC_label");
	gtk_widget_set_name(listrik_menuBox_label, "listrik_menuBox_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	//set dimention
	int imWidth, imHight;
	imWidth=imHight=screenWidth/7;
	gtk_image_opt(listrik_menu_bt_im1, "img/btnListrikPintar.png", imWidth, imHight, 0);
	gtk_image_opt(listrik_menu_bt_im2, "img/btnPLNPrabayar.png", imWidth, imHight, 0);
	gtk_image_opt(listrik_menu_bt_im3, "img/btnPLNPascabayar.png", imWidth, imHight, 0);

	gtk_widget_set_margin_start(listrik_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(listrik_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(listrik_boxC, boxC_space);
	gtk_widget_set_margin_bottom(listrik_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(listrik_boxC), nboxC_space);
	gtk_widget_set_size_request(listrik_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(listrik_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(listrik_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(listrik_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(listrik_menuGrid), gspace_col);
	gtk_widget_set_margin_top(listrik_menuGrid, boxC_space);

	gtk_image_opt(listrik_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(listrik_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);
}

void gtk_windowListrik_connect(){
	g_signal_connect(windowListrik, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect(listrik_menu_bt1, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(listrik_menu_bt2, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(listrik_menu_bt3, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	g_signal_connect(listrik_bt_main, "clicked", G_CALLBACK (listrik_go_to_main), NULL);
	g_signal_connect(listrik_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowListrik), NULL);
}

static void close_windowListrik(){
	gtk_widget_hide(windowListrik);
}

static void listrik_go_to_main(){
	gtk_widget_hide(windowListrik);
}

//windowInternet/TV
void gtk_windowIntv_init(){
	windowIntv=GTK_WIDGET(gtk_builder_get_object(builder, "windowIntv"));

	intv_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "intv_boxC"));
	intv_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "intv_boxC_main"));
	intv_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menuGrid"));

	intv_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "intv_bt_main"));
	intv_menu_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt1"));
	intv_menu_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt2"));
	intv_menu_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt3"));
	intv_menu_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt4"));
	intv_menu_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt5"));
	intv_menu_bt6=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt6"));
	intv_menu_bt7=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt7"));
	intv_menu_bt8=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt8"));
	intv_menu_bt9=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt9"));
	intv_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menuBox_bt_kembali"));

	intv_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "intv_imLogo"));
	intv_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "intv_imgKembali"));
	intv_menu_bt_im1=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im1"));
	intv_menu_bt_im2=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im2"));
	intv_menu_bt_im3=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im3"));
	intv_menu_bt_im4=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im4"));
	intv_menu_bt_im5=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im5"));
	intv_menu_bt_im6=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im6"));
	intv_menu_bt_im7=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im7"));
	intv_menu_bt_im8=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im8"));
	intv_menu_bt_im9=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menu_bt_im9"));

	intv_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "intv_boxC_label"));
	intv_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "intv_menuBox_label"));
}

void gtk_windowIntv_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowIntv));

	gtk_widget_set_name(windowIntv, "windowIntv");

	gtk_widget_set_name(intv_bt_main, "intv_bt_main");
	gtk_widget_set_name(intv_menuBox_bt_kembali, "intv_menuBox_bt_kembali");
	gtk_widget_set_name(intv_menu_bt1, "intv_menu_bt1");
	gtk_widget_set_name(intv_menu_bt2, "intv_menu_bt2");
	gtk_widget_set_name(intv_menu_bt3, "intv_menu_bt3");
	gtk_widget_set_name(intv_menu_bt4, "intv_menu_bt4");
	gtk_widget_set_name(intv_menu_bt5, "intv_menu_bt5");
	gtk_widget_set_name(intv_menu_bt6, "intv_menu_bt6");
	gtk_widget_set_name(intv_menu_bt7, "intv_menu_bt7");
	gtk_widget_set_name(intv_menu_bt8, "intv_menu_bt8");
	gtk_widget_set_name(intv_menu_bt9, "intv_menu_bt9");

	gtk_widget_set_name(intv_imLogo, "intv_imLogo");

	gtk_widget_set_name(intv_boxC_label, "intv_boxC_label");
	gtk_widget_set_name(intv_menuBox_label, "intv_menuBox_label");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	//set dimention
	int imWidth, imHight;
	imWidth=imHight=screenWidth/9;
	gtk_image_opt(intv_menu_bt_im1, "img/btnIndiHome.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im2, "img/btnCBN.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im3, "img/btnTransVision.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im4, "img/btnFirstMedia.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im5, "img/btnMNCVision.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im6, "img/btnBiznet.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im7, "img/btnKVision.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im8, "img/btnBigTV.png", imWidth, imHight, 0);
	gtk_image_opt(intv_menu_bt_im9, "img/btnNextMedia.png", imWidth, imHight, 0);

	gtk_widget_set_margin_top(intv_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(intv_boxC_label, boxC_label_margin);

	gtk_widget_set_margin_start(intv_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(intv_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(intv_boxC, boxC_space);
	gtk_widget_set_margin_bottom(intv_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(intv_boxC), nboxC_space);
	gtk_widget_set_size_request(intv_boxC_main, boxC_main_width, -1);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_grid_set_row_spacing(GTK_GRID(intv_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(intv_menuGrid), gspace_col);
	gtk_widget_set_margin_top(intv_menuGrid, boxC_space);

	gtk_image_opt(intv_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(intv_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);
}

void gtk_windowIntv_connect(){
	g_signal_connect(windowIntv, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect(intv_menu_bt1, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt2, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt3, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt4, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt5, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	g_signal_connect(intv_bt_main, "clicked", G_CALLBACK (intv_go_to_main), NULL);
	g_signal_connect(intv_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowIntv), NULL);
}

static void close_windowIntv(){
	gtk_widget_hide(windowIntv);
}

static void intv_go_to_main(){
	gtk_widget_hide(windowIntv);
}

//windowCekOrder
void gtk_windowCko_init(){
	windowCko=GTK_WIDGET(gtk_builder_get_object(builder, "windowCko"));
	
	cko_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "cko_boxC"));
	cko_grid_num=GTK_WIDGET(gtk_builder_get_object(builder, "cko_grid_num"));
	cko_numBox=GTK_WIDGET(gtk_builder_get_object(builder, "cko_numBox"));
	
    cko_num_bt1=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt1"));
	cko_num_bt2=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt2"));
	cko_num_bt3=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt3"));
	cko_num_bt4=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt4"));
	cko_num_bt5=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt5"));
	cko_num_bt6=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt6"));
	cko_num_bt7=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt7"));
	cko_num_bt8=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt8"));
	cko_num_bt9=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt9"));
	cko_num_bt0=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_bt0"));
	cko_num_btDel=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_btDel"));
	cko_num_btEnt=GTK_WIDGET(gtk_builder_get_object(builder, "cko_num_btEnt"));
	cko_close_btn=GTK_WIDGET(gtk_builder_get_object(builder, "cko_close_btn"));
	
	cko_number=GTK_WIDGET(gtk_builder_get_object(builder, "cko_number"));

	memset(input_number_text, 0x00, 20*sizeof(char));
}

void gtk_windowCko_setAttrib(){
	gtk_window_set_position(GTK_WINDOW(windowCko), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_widget_set_name(windowCko, "windowCko");

	gtk_widget_set_name(cko_grid_num, "cko_grid_num");
	gtk_widget_set_name(cko_numBox, "cko_numBox");

	gtk_widget_set_name(cko_num_bt1, "cko_num_bt1");
	gtk_widget_set_name(cko_num_bt2, "cko_num_bt2");
	gtk_widget_set_name(cko_num_bt3, "cko_num_bt3");
	gtk_widget_set_name(cko_num_bt4, "cko_num_bt4");
	gtk_widget_set_name(cko_num_bt5, "cko_num_bt5");
	gtk_widget_set_name(cko_num_bt6, "cko_num_bt6");
	gtk_widget_set_name(cko_num_bt7, "cko_num_bt7");
	gtk_widget_set_name(cko_num_bt8, "cko_num_bt8");
	gtk_widget_set_name(cko_num_bt9, "cko_num_bt9");
	gtk_widget_set_name(cko_num_bt0, "cko_num_bt0");
	gtk_widget_set_name(cko_num_btDel, "cko_num_btDel");
	gtk_widget_set_name(cko_num_btEnt, "cko_num_btEnt");
	gtk_widget_set_name(cko_close_btn, "cko_close_btn");

	gtk_widget_set_name(cko_number, "cko_number");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	char markup_text[200];
	strcpy(markup_text, "<span foreground='#777777'><b>000104xxxxxx</b></span>");
	gtk_label_set_markup(GTK_LABEL(cko_number), (const gchar *) markup_text);

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

	gtk_widget_set_size_request(cko_num_bt1, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt2, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt3, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt4, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt5, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt6, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt7, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt8, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt9, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_bt0, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_btDel, cko_bt_dimention, cko_bt_dimention);
	gtk_widget_set_size_request(cko_num_btEnt, cko_bt_dimention, cko_bt_dimention);

	gtk_widget_set_size_request(cko_close_btn, cko_bt_dimention/2, cko_bt_dimention/2);
}

void gtk_windowCko_connect(){
	g_signal_connect(windowCko, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(cko_num_bt1, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt2, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt3, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt4, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt5, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt6, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt7, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt8, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt9, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_bt0, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_btDel, "clicked", G_CALLBACK(cko_setNumber), NULL);
	g_signal_connect(cko_num_btEnt, "clicked", G_CALLBACK(close_windowCko), NULL);
	g_signal_connect(cko_close_btn, "clicked", G_CALLBACK(close_windowCko), NULL);
}

static void close_windowCko(){
	gtk_widget_hide(windowCko);
}

static void cko_setNumber(GtkWidget *numWidget){
	char myNumber[10];

	strcpy(myNumber, (const char *)gtk_button_get_label(GTK_BUTTON(numWidget)));
	if (strlen(input_number_text)<12 || myNumber[0]=='D'){
		if(myNumber[0]!='D'){
			input_number_text[strlen(input_number_text)]=myNumber[0];
			input_number_text[strlen(input_number_text)]=0;
		}
		else input_number_text[strlen(input_number_text)-1]=0;

		char format[200];
		char markup_text[200];

		if(strlen(input_number_text)>0){
			strcpy(format, "<span foreground='#000'><b>\%s</b></span>");
			strcpy(markup_text, g_markup_printf_escaped (format, input_number_text));
		}
		else{
			strcpy(format, "<span foreground='#777777'><b>\%s</b></span>");
			strcpy(markup_text, g_markup_printf_escaped (format, "000104xxxxxx"));
		}
		gtk_label_set_markup(GTK_LABEL(cko_number), (const gchar *) markup_text);
	}
}

//windowPajak
void gtk_windowPajak_init(){
	windowPajak=GTK_WIDGET(gtk_builder_get_object(builder, "windowPajak"));

	pajak_boxC=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_boxC"));
	pajak_boxC_main=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_boxC_main"));
	pajak_menuGrid=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_menuGrid"));

	pajak_bt_main=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_bt_main"));
	pajak_menuBox_bt_kembali=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_menuBox_bt_kembali"));
	pajak_bt_ok=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_bt_ok"));

	pajak_imLogo=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_imLogo"));
	pajak_imgKembali=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_imgKembali"));

	pajak_boxC_label=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_boxC_label"));
	pajak_menuBox_label=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_menuBox_label"));
	pajak_lbl_jenis_produk=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_lbl_jenis_produk"));
	pajak_bt_ok_label=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_bt_ok_label"));

	pajak_combo_jenis_produk=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_combo_jenis_produk"));
	pajak_combo_pilihan=GTK_WIDGET(gtk_builder_get_object(builder, "pajak_combo_pilihan"));
}

void gtk_windowPajak_setAttrib(){
	gtk_window_fullscreen(GTK_WINDOW(windowPajak));

	gtk_widget_set_name(windowPajak, "windowPajak");

	gtk_widget_set_name(pajak_bt_main, "pajak_bt_main");
	gtk_widget_set_name(pajak_menuBox_bt_kembali, "pajak_menuBox_bt_kembali");
	gtk_widget_set_name(pajak_bt_ok, "pajak_bt_ok");

	gtk_widget_set_name(pajak_imLogo, "pajak_imLogo");

	gtk_widget_set_name(pajak_boxC_label, "pajak_boxC_label");
	gtk_widget_set_name(pajak_menuBox_label, "pajak_menuBox_label");
	gtk_widget_set_name(pajak_lbl_jenis_produk, "pajak_lbl_jenis_produk");
	gtk_widget_set_name(pajak_bt_ok_label, "pajak_bt_ok_label");

	gtk_widget_set_name(pajak_combo_jenis_produk, "pajak_combo_jenis_produk");
	gtk_widget_set_name(pajak_combo_pilihan, "pajak_combo_pilihan");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	//set dimention
	gtk_widget_set_margin_start(pajak_boxC, boxC_side_margin);
	gtk_widget_set_margin_end(pajak_boxC, boxC_side_margin);
	gtk_widget_set_margin_top(pajak_boxC, boxC_space);
	gtk_widget_set_margin_bottom(pajak_boxC, boxC_space);
	gtk_box_set_spacing(GTK_BOX(pajak_boxC), nboxC_space);
	gtk_widget_set_size_request(pajak_boxC_main, boxC_main_width, -1);

	gtk_widget_set_margin_top(pajak_imLogo, boxC_label_margin);
	gtk_widget_set_margin_top(pajak_boxC_label, boxC_label_margin);

	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;

	gtk_grid_set_row_spacing(GTK_GRID(pajak_menuGrid), gspace_row);
	gtk_grid_set_column_spacing(GTK_GRID(pajak_menuGrid), gspace_col);
	gtk_widget_set_margin_top(pajak_menuGrid, boxC_space);

	gtk_image_opt(pajak_imLogo, "img/logo.png", logo_width, logo_hight, 0);
	gtk_image_opt(pajak_imgKembali, "img/imgBack.png", imBack_width, imBack_hight, 0);

	int pajak_combo_width = (screenWidth/2) + (screenWidth/8);
	int pajak_combo_hight = screenHight/15;
	int pajak_combo_margin = screenHight/30;
	gtk_widget_set_size_request(pajak_combo_jenis_produk, pajak_combo_width, pajak_combo_hight);
	gtk_widget_set_size_request(pajak_combo_pilihan, pajak_combo_width, pajak_combo_hight);

	int btn_width = screenWidth/10;
	int btn_hight = screenWidth/10;
	int btn_margin = screenHight/8;
	gtk_widget_set_size_request(pajak_bt_ok, btn_width, btn_hight);
	gtk_widget_set_margin_top(pajak_bt_ok, btn_margin);
}

void gtk_windowPajak_connect(){
	g_signal_connect(windowPajak, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect(intv_menu_bt1, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt2, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt3, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt4, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	//g_signal_connect(intv_menu_bt5, "clicked", G_CALLBACK(start_windowNompul_or_pnet), NULL);
	g_signal_connect(pajak_bt_ok, "clicked", G_CALLBACK(set_attrib_to_numi), NULL);
	g_signal_connect(pajak_bt_main, "clicked", G_CALLBACK (pajak_go_to_main), NULL);
	g_signal_connect(pajak_menuBox_bt_kembali, "clicked", G_CALLBACK(close_windowPajak), NULL);
}

static void close_windowPajak(){
	gtk_widget_hide(windowPajak);
}

static void pajak_go_to_main(){
	gtk_widget_hide(windowPajak);
}

static void set_attrib_to_numi(){

}
