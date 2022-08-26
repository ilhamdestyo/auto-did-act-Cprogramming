//compile gcc `pkg-config --cflags gtk+-3.0`  `pkg-config --libs gtk+-3.0` -DIO_READ -DIO_MMAP -DIO_USERPTR cobakamera.c -o cobakamera
#include "v4l2grab.c"

char* gabung_kata(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char *IntToStr(int x){
	char *str=(char *)malloc(10 * sizeof (char));
	sprintf(str, "%d", x);
	return str;
}

int main(int argc, char *argv[] ) {

    init_gtk_component(&argc, &argv);
    GdkPixbuf *cobapixbuf;
    color_coordinate_matrix dataRGB;
    
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
	char *namafile;
	int count = 0;
	//~ for(int i=0;i<100;i++){
		//~ count++;
		//~ i=count;
  // Timer start
		clock_t begin = clock();
		
		dataRGB = process_frame();
		
		cobapixbuf = load_rgb_matrix_data_from_stream(dataRGB);
		
		//~ namafile = gabung_kata(gabung_kata("coba",IntToStr(i)),".jpg");
		namafile = "coba";
		gdk_pixbuf_save (cobapixbuf, namafile, "jpeg", NULL, "quality", "100", NULL);
		clock_t end = clock();
		double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
		double time_in_ms;
		time_in_ms = time_spent*1000;
		//printf("frame ke %d, Execution duration: %.2f ms, %.2f fps\n", 1,time_in_ms,(1/time_spent));
		
		 //show_gtk_component(cobapixbuf);
	//~ }
	
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
