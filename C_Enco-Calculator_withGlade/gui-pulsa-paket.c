GtkWidget *windowPud;
GtkWidget *pud_boxC, *pud_boxC_main, *pud_menuGrid;
GtkWidget *pud_imLogo, *pud_imgKembali;
GtkWidget *pud_bt_main, *pud_menuBox_bt_kembali,*pud_menu_bt1, *pud_menu_bt2;
GtkWidget *pud_boxC_label, *pud_menu_bt1_lbl, *pud_menu_bt2_lbl;

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

static void view_windowPud(){
	gtk_widget_show(windowPud);
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
