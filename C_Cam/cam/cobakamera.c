//compile gcc `pkg-config --cflags gtk+-3.0`  `pkg-config --libs gtk+-3.0` -ljpeg -DIO_READ -DIO_MMAP -DIO_USERPTR cobakamera.c -o cobakamera
#include "v4l2grab.c"

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
  // Timer start
	clock_t begin = clock();
	
	dataRGB = process_frame("/dev/video0");
	
	cobapixbuf = load_rgb_matrix_data_from_stream(dataRGB);
	
	clock_t end = clock();
	double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
	double time_in_ms;
	time_in_ms = time_spent*1000;
	printf("Execution duration: %.2f ms, %.2f fps\n", time_in_ms,(1/time_spent));
	
	show_gtk_component(cobapixbuf);
	

  return 0;
}
