//Compile : gcc -Wno-format -o integrasi2 integrasi2.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <mysql.h>


void send_data(char* a);
char input[1000];
char *IntToStr(int x);
char *temp;
char textread[10];
char format[256];
char markup_text[256];
gboolean timer_handler(GtkWidget *);


//Inisialisasi window menu
GtkWidget	*window;
GtkWidget	*box, *fixed;
GtkWidget	*scroll1, *entry;

GtkWidget	*label1, *label2;

GtkAdjustment *adjustment1;



GtkBuilder	*builder; 

int main (int argc, char **argv)
{
		MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	char *server = "127.0.0.1";
	char *user = "root";
	char *password = "12345"; /* set me first */
	char *database = "mysql";
	
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password,database, 0, NULL, 0)) {
				char q[1000];
		sprintf(q,"insert to payment_table(uid) values('%s')",gtk_label_get_text(textread));
		if(mysql_query(conn,q)){
			g_print("Error:%d",mysql_errno(conn));
		}else{
			g_print("Error:%d",mysql_errno(conn));
		}
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	gtk_init (&argc, &argv);
		/* send SQL query */
	if (mysql_query(conn, "show tables")) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
   
	res = mysql_use_result(conn);

	
	//connect dengan glade
	builder = gtk_builder_new_from_file ("glade.glade");
	
	//WindowMenu
	window = GTK_WIDGET (gtk_builder_get_object(builder, "window"));
	g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	gtk_builder_connect_signals (builder, NULL);
	box = GTK_WIDGET (gtk_builder_get_object (builder, "box"));
	fixed = GTK_WIDGET (gtk_builder_get_object (builder, "fixed"));
	scroll1 = GTK_WIDGET (gtk_builder_get_object (builder, "scroll1"));
	entry = GTK_WIDGET (gtk_builder_get_object (builder, "entry"));
	label1 = GTK_WIDGET (gtk_builder_get_object (builder, "label1"));
	label2 = GTK_WIDGET (gtk_builder_get_object (builder, "label2"));

	
	adjustment1 = GTK_ADJUSTMENT (gtk_builder_get_object(builder, "adjustment1")); 
	
	gtk_widget_show(window);			//Print window
	g_timeout_add_seconds(1,(GSourceFunc) timer_handler, label1); //set
	gtk_main();
	
	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
	
	return EXIT_SUCCESS;
}



char *IntToStr(int x){						//Merubah integer ke string
	char *str=(char *)malloc(1 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}

int receive_data(){
	int fd = 0, len;
	struct termios options; /* Serial ports setting */
	
	//int serial_port = open("/dev/ttyACM1", O_RDWR);
	fd = open("/dev/ttyACM0", O_RDWR);
	
	//~ // Read in existing settings, and handle any error
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
	cfsetispeed(&options, B115200);
	cfsetospeed(&options, B115200);
	
		// Save tty settings, also checking for error
	if (tcsetattr(fd, TCSANOW, &options) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return 1;
	}
	
	//~ /* Read from serial port */
	//memset(&read_buf, '\0', sizeof(read_buf));
	memset(&textread, '\0', sizeof(textread));
	
	//read(serial_port, &read_buf, 100);	
	int num_bytes = read(fd, &textread, 255);

	
	// n is the number of bytes read. n may be 0 if no bytes were received, and can also be -1 to signal an error.
	if (num_bytes < 0) {
      printf("Error reading: %s", strerror(errno));
      return 1;
	}
	
	
	printf("Received string: %s\n", textread);
	
	close(fd);
	
	strcpy(format, "<span font_desc='monospace 15' foreground='#ffffff' ><b>%s</b></span>");
	strcpy(markup_text, g_markup_printf_escaped (format, textread));
	gtk_label_set_markup(GTK_LABEL(label1), (const gchar *) markup_text);
	
	return 0;
}

gboolean timer_handler(GtkWidget *labeladc){
	
	time_t t = time(0);
	receive_data();
	//gtk_label_set_text(GTK_LABEL(nilaiadc_lbl), read_buf);	// update time of day
	
	return TRUE; // False kills the timer
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
