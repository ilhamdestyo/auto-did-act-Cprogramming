//cc `pkg-config --cflags gtk+-3.0` -o exe mygui.c `pkg-config --libs gtk+-3.0` -Wno-format -Wno-deprecated-declarations -Wno-format-security -lm -export-dynamic

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()


// Make them global

GtkWidget	*window;
GtkWidget	*fixed1;
GtkWidget	*button1, *button2, *button3, *button4, *button5, *buttonHello;
GtkWidget	*labelsoal, *labelled, *labeltext;
GtkWidget	*switch1;
GtkWidget	*entryText;
GtkBuilder	*builder; 

//GtkListStore	*liststore1;
//GtkAdjustment	*adjustment2;
void send_data(char* a);
void gtk_mainWindow_connect();

int main(int argc, char *argv[]) {

	gtk_init(&argc, &argv); // init Gtk
//---------------------------------------------------------------------
// establish contact with xml code used to adjust widget settings
//---------------------------------------------------------------------
 
	builder = gtk_builder_new_from_file ("my-GUI.glade");
 
	window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        gtk_builder_connect_signals(builder, NULL);

	fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
	button1 = GTK_WIDGET(gtk_builder_get_object(builder, "forsoal1"));
	button2 = GTK_WIDGET(gtk_builder_get_object(builder, "forsoal2"));
	button3 = GTK_WIDGET(gtk_builder_get_object(builder, "forsoal3"));
	button4 = GTK_WIDGET(gtk_builder_get_object(builder, "forsoal4"));
	button5 = GTK_WIDGET(gtk_builder_get_object(builder, "forsoal5"));
	switch1 = GTK_WIDGET(gtk_builder_get_object(builder, "switch1"));
	labelsoal = GTK_WIDGET(gtk_builder_get_object(builder, "labelsoal"));
	labelled = GTK_WIDGET(gtk_builder_get_object(builder, "labelled"));
	labeltext = GTK_WIDGET(gtk_builder_get_object(builder, "labeltext"));
	entryText = GTK_WIDGET(gtk_builder_get_object(builder, "entryText"));
	buttonHello =GTK_WIDGET(gtk_builder_get_object(builder, "buttonHello"));

	//liststore1 = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore1"));
	//adjustment2 = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adjustment2"));

	/*******************
	struct GtkAdjustment {
                    gdouble lower,
                    gdouble upper,
                    gdouble step_increment,
                    gdouble page_increment,
                    gdouble page_size};
	****************************/
	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
}


//Button Callback
void	on_forsoal1_clicked (GtkButton *b) {
	send_data("1");
	gtk_label_set_text (GTK_LABEL(labelsoal), (const gchar* ) "Soal 1 di Convert");
}
void	on_forsoal2_clicked (GtkButton *b) {
	send_data("2");
	gtk_label_set_text (GTK_LABEL(labelsoal), (const gchar* ) "Soal 2 di Convert");
}
void	on_forsoal3_clicked (GtkButton *b) {
	send_data("3");
	gtk_label_set_text (GTK_LABEL(labelsoal), (const gchar* ) "Soal 3 di Convert");
}
void	on_forsoal4_clicked (GtkButton *b) {
	send_data("4");
	gtk_label_set_text (GTK_LABEL(labelsoal), (const gchar* ) "Soal 4 di Convert");
}
void	on_forsoal5_clicked (GtkButton *b) {
	send_data("5");
	gtk_label_set_text (GTK_LABEL(labelsoal), (const gchar* ) "Soal 5 di Convert");
}
//LED Callback
void	on_swLED1_state_set (GtkSwitch *s) {
	gboolean T = gtk_switch_get_active(s);
	if (T){	
		send_data("a");
		gtk_label_set_text (GTK_LABEL(labelled), (const gchar* ) "LED 1 Active");
	}else {
		send_data("b");
		gtk_label_set_text (GTK_LABEL(labelled), (const gchar* ) "LED 1 Not Active");
	}
}
//Text Callback
void	on_entryText_changed(GtkEntry *e) {
	char tmp[128];
	sprintf(tmp, "%s", gtk_entry_get_text(e));
	gtk_label_set_text (GTK_LABEL(labeltext), (const gchar* ) tmp);
	send_data(tmp);
}
void on_buttonHello_clicked (GtkButton *b) {
	send_data("H");
	gtk_label_set_text (GTK_LABEL(labelled), (const gchar* ) "Print Hello World!");
}

void send_data (char *a){
	int fd, len;
	char text[255];
	struct termios options; /* Serial ports setting */

	fd = open("/dev/ttyACM0", O_RDWR | O_NDELAY | O_NOCTTY);
	if (fd < 0) {
		perror("Error opening serial port");
		
	}

	/* Read current serial port settings */
	// tcgetattr(fd, &options);
	
	/* Set up serial port */
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;

	/* Apply the settings */
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);

	/* Write to serial port */
	strcpy(text, a);
	len = strlen(text);
	len = write(fd, text, len);
	

	close(fd);
}
