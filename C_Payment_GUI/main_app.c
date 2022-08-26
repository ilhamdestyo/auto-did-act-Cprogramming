// Compile : gcc -Wno-format -o exe myGui.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

#include <mysql.h>

void send_data(char* a);
int get_data();
char *IntToStr(int x);
char input[1000];

char uid[255];

const int screenWidth = 500, screenHight = 	500;
int main_box_space, main_nbox_space, main_box_side_margin, main_box_main_width;
int logo_width, logo_hight;
int imBack_width, imBack_hight;
int main_box_label_margin;
gboolean timer_handler(GtkWidget *);
GtkCssProvider *cssProvider;
GtkBuilder *builder;

int	countDownMax, countCurrent;
//mainWindow
GtkWidget *window;
GtkWidget *main_box;
GtkWidget *lb_uid;

void gtk_mainWindow_init();
void gtk_mainWindow_setAttrib();
void gtk_mainWindow_connect();
void gtk_builder_and_attrib_init();

int main(int argc, char **argv){
	/*deklarasi variabel
	 * ====================================*/
	main_box_space = screenWidth/100;
	main_box_side_margin = screenWidth/50;
	main_box_main_width = screenWidth/60;
	main_nbox_space = screenWidth/200;
	main_box_label_margin = screenHight/8;

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
	guint ID = g_timeout_add(700,(GSourceFunc) timer_handler, lb_uid);
	
	//start
	gtk_builder_connect_signals(builder, NULL);
	gtk_widget_show(window);
	g_object_unref(builder);
	gtk_main();
	
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server = "127.0.0.1";
	char *user = "root";
	char *password = "12345"; /* set me first */
	char *database = "mysql";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	//setelah data base adalah parameter port, *unix_socket dan flag
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("connection succesfull!\n\n");
	/* send SQL query */
	if (mysql_query(conn, "SELECT * FROM mysql.payment_table")) {
		char q[1000];
		sprintf(q,"insert to payment_table(uid) values('%s')",gtk_label_get_text(GTK_LABEL(lb_uid)));
		if(mysql_query(conn,q)){
			g_print("Error:%d",mysql_errno(conn));
		}else{
			g_print("Error:%d",mysql_errno(conn));
		}
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
   
	res = mysql_use_result(conn);
	
	/* output table name */
	printf("MySQL Tables in mysql database:\n");
   
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s \n", row[0]);
   
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
	return EXIT_SUCCESS;
	return 0;
}

// function uid show to GTK
gboolean timer_handler(GtkWidget *lb_uid){

	get_data();
	gtk_label_set_text(GTK_LABEL(lb_uid), uid);

	return TRUE; // False kills the timer
}

void gtk_builder_and_attrib_init(){
	builder=gtk_builder_new();
	gtk_builder_add_from_file (builder, "UI_App_Payment.glade", NULL);
	
	cssProvider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(cssProvider, "style.css", NULL);
}



void gtk_mainWindow_init(){
	window=GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
	main_box=GTK_WIDGET(gtk_builder_get_object(builder, "boxC"));
	lb_uid=GTK_WIDGET(gtk_builder_get_object(builder, "labeluid"));
} 

void gtk_mainWindow_setAttrib(){
	//~ gtk_window_fullscreen(GTK_WINDOW(window));

	gtk_widget_set_name (window, "mainWindow");
	gtk_widget_set_name (main_box, "boxC");
	gtk_widget_set_name (lb_uid, "labeluid");

	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	
	int gspace_row = screenWidth/60; 
	int gspace_col = screenWidth/60;
	gtk_box_set_spacing(GTK_BOX(main_box), gspace_row);
	gtk_widget_set_margin_top(main_box, main_box_space);
	gtk_widget_set_margin_bottom(main_box, main_box_space);
	gtk_widget_set_margin_start(main_box, main_box_side_margin);
	gtk_widget_set_margin_end(main_box, main_box_side_margin);
}

void gtk_mainWindow_connect(){
	g_signal_connect(window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
}

// Mengkonvert dari Integer ke String
char *IntToStr(int x){
	char *str=(char *)malloc(10 * sizeof (char));	// Mengalokasikan blok memory sebesar 10byte dan di pointing ke pointer str
	sprintf(str, "%d", x);	// Memasukkan data integer x ke str
	return str;
}


	
// ambil data dari UART	
int get_data(){
	int fd = 0, len;
	struct termios options; /* Serial ports setting */
	
	//int serial_port = open("/dev/ttyACM1", O_RDWR);
	fd = open("/dev/ttyACM0", O_RDWR);
	
	// Read in existing settings, and handle any error
	if(tcgetattr(fd, &options) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      return 1;
	}

	//~ /* Read current serial port settings */
	//~ // tcgetattr(fd, &options);
	options.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
	options.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
	options.c_cflag &= ~CSIZE; // Clear all bits that set the data size 
	options.c_cflag |= CS8; // 8 bits per byte (most common)
	options.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
	options.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

	options.c_lflag &= ~ICANON;
	options.c_lflag &= ~ECHO; // Disable echo
	options.c_lflag &= ~ECHOE; // Disable erasure
	options.c_lflag &= ~ECHONL; // Disable new-line echo
	options.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
	options.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
	options.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

	options.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
	options.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

	options.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
	options.c_cc[VMIN] = 0;

	// Set in/out baud rate to be 115200
	cfsetispeed(&options, B115200);	// in
	cfsetospeed(&options, B115200);	//out
	
		// Save tty settings, also checking for error
	if (tcsetattr(fd, TCSANOW, &options) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
	}
	
	//~ /* Read from serial port */
	//memset(&read_buf, '\0', sizeof(read_buf));
	memset(&uid, '\0', sizeof(uid));
	
	//read(serial_port, &read_buf, 100);	
	int num_bytes = read(fd, &uid, 255);

	
	// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
	if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return 1;
	}
	
	//~ printf("Received string: %s\n", uid);
	
	close(fd);
	
	return 0;
}
