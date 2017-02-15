#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#include<math.h>
typedef struct {
  unsigned char red,green,blue;
} PPMPixel;

typedef struct {
  int x, y;
  PPMPixel *data;
} PPMImage;

typedef struct {
  unsigned char gs;
} PPMPixelGS;


typedef struct {
  int x, y;
  PPMPixelGS *data;
} PPMImageGS;



#define RGB_COMPONENT_COLOR 255


void writePPMGS(const char *filename, PPMImageGS *img)
{
  FILE *fp;
  //open file for output
  fp = fopen(filename, "wb");
  if (!fp) {
    fprintf(stderr, "Unable to open file '%s'\n", filename);
    exit(1);
  }

  //write the header file
  //image format
  fprintf(fp, "P5\n");

    

  //image size
  fprintf(fp, "%d %d\n",img->x,img->y);

  // rgb component depth
  fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

  // pixel data
  fwrite(img->data, img->x, img->y, fp);
  fclose(fp);
}



PPMImageGS * changeImage(PPMImage * im)
{
  int rows = im->x;
  int cols = im->y;
  int i,j;

  PPMImageGS *im2 = (PPMImageGS *) malloc(sizeof(PPMImageGS));
  im2->x = rows;
  im2->y = cols;
  im2->data = (PPMPixelGS *) malloc(rows*cols*sizeof(PPMPixelGS));
  int r,g,b,idx;	
  for(i=0;i<rows;i++)
    {
      for(j=0; j<cols; j++)
	{
	  idx = rows*i + j;
	  PPMPixel *temp = im->data + idx;
	  r = temp->red;
	  g = temp->green;
	  b = temp->blue;
	  PPMPixelGS *temp2 = im2->data + idx;
	  temp2->gs = 0.21*r+0.71*g+0.07*b;
	}	
    }
	
  return im2;
}

static PPMImage *readPPM(const char *filename)
{
  char buff[16];
  PPMImage *img;
  FILE *fp;
  int c, rgb_comp_color;
  //open PPM file for reading
  fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "Unable to open file '%s'\n", filename);
    exit(1);
  }

  //read image format
  if (!fgets(buff, sizeof(buff), fp)) {
    perror(filename);
    exit(1);
  }

  //check the image format
  if (buff[0] != 'P' || buff[1] != '6') {
    fprintf(stderr, "Invalid image format (must be 'P6')\n");
    exit(1);
  }

  //alloc memory form image
  img = (PPMImage *)malloc(sizeof(PPMImage));
  if (!img) {
    fprintf(stderr, "Unable to allocate memory\n");
    exit(1);
  }

  //check for comments
  c = getc(fp);
  while (c == '#') {
    while (getc(fp) != '\n') ;
    c = getc(fp);
  }

  ungetc(c, fp);
  //read image size information
  if (fscanf(fp, "%d %d", &img->x, &img->y) != 2) {
    fprintf(stderr, "Invalid image size (error loading '%s')\n", filename);
    exit(1);
  }

  //read rgb component
  if (fscanf(fp, "%d", &rgb_comp_color) != 1) {
    fprintf(stderr, "Invalid rgb component (error loading '%s')\n", filename);
    exit(1);
  }

  //check rgb component depth
  if (rgb_comp_color!= RGB_COMPONENT_COLOR) {
    fprintf(stderr, "'%s' does not have 8-bits components\n", filename);
    exit(1);
  }

  while (fgetc(fp) != '\n') ;
  //memory allocation for pixel data
  img->data = (PPMPixel*)malloc(img->x * img->y * sizeof(PPMPixel));

  if (!img) {
    fprintf(stderr, "Unable to allocate memory\n");
    exit(1);
  }

  //read pixel data from file
  if (fread(img->data, 3 * img->x, img->y, fp) != img->y) {
    fprintf(stderr, "Error loading image '%s'\n", filename);
    exit(1);
  }

  fclose(fp);
  return img;
}

void writePPM(const char *filename, PPMImage *img)
{
  FILE *fp;
  //open file for output
  fp = fopen(filename, "wb");
  if (!fp) {
    fprintf(stderr, "Unable to open file '%s'\n", filename);
    exit(1);
  }

  //write the header file
  //image format
  fprintf(fp, "P6\n");

  //comments


  //image size
  fprintf(fp, "%d %d\n",img->x,img->y);

  // rgb component depth
  fprintf(fp, "%d\n",255);

  // pixel data
  fwrite(img->data, 3 * img->x, img->y, fp);
  fclose(fp);
}

/*function to perform bilinear interpolation for given image pixel
	//returns a pixel
*/
PPMPixel bilinearinterpolation(PPMImage* image, int rows, int columns, double x, double y) 
{

	// the values of x and y to interpolate on		
	int xf= floor(x);
	int yf= floor(y);

	int xc= ceil(x);
	int yc=	ceil(y);

	//changes made to return pixel instead of pointer to it
	PPMPixel *fq11, *fq21, *fq12, *fq22; // *f;
	PPMPixel pixtoreturn,fxy1, fxy2;
	
	double xfactor1, xfactor2, yfactor1, yfactor2;

	// constants for first interpolation
	xfactor1 = (xc-x)/(xc-xf);
	xfactor2 = (x-xf)/(xc-xf);

	// accessing data for first interpolation
	fq11 = image->data + xf*columns + yf;
	fq21 = image->data + xf*columns + yc;
	fq12 = image->data + xc*columns + yf;
	fq22 = image->data + xc*columns + yc;

	// first interpolation
	fxy1.red = xfactor1 * fq11->red + xfactor2 * fq21->red;
	fxy1.green = xfactor1 * fq11->green + xfactor2 * fq21->green;
	fxy1.blue = xfactor1 * fq11->blue + xfactor2 * fq21->blue;
	
	fxy2.red = xfactor1 * fq12->red + xfactor2 * fq22->red;
	fxy2.green = xfactor1 * fq12->green + xfactor2 * fq22->green;
	fxy2.blue = xfactor1 * fq12->blue + xfactor2 * fq22->blue;

	// constants for second interpolation
	yfactor1 = (yc-y)/(yc-yf);
	yfactor2 = (y-yf)/(yc-yf);
	 
	//second interpolation
	pixtoreturn.red= yfactor1 * fxy1.red + yfactor2 * fxy2.red;
	pixtoreturn.green = yfactor1 * fxy1.green + yfactor2 * fxy2.green;
	pixtoreturn.blue = yfactor1 * fxy1.blue + yfactor2 * fxy2.blue; 
	 
	return pixtoreturn;
}

/*
	Function to perform image warping for given input image
	takes in input as ppmimage
	warps and returns a ppm
*/
PPMImage* warping (PPMImage *impimage)
{
	int cx,cy,i,j;
	double x_toreadfrom,y_toreadfrom;	// variable from which we need to read data for a given warped image pixel
	int idx2;

	// total rows andd columns
	int rows=impimage->x;
	int columns=impimage->y;
	
	//image 2 declaration
	PPMImage *im2 = (PPMImage*) malloc(sizeof(PPMImage));
  	im2->x = rows;
  	im2->y = columns;
  	im2->data = (PPMPixel *) malloc(rows*columns*sizeof(PPMPixel));

	// finding centre
	cx=rows/2;
	cy=columns/2; // assume rotation centre is images centre itself
	
	// value of theta for the rotation in warping
 	double theta0 = 1*3.14159/(2*180.0);

	// distance of given point from the centre of the image
 	double distcen=0;
 	
 	//double par_start, par_end;
 	//par_start=omp_get_wtime();
 	
	//loop through for the warped image
	for (i=0;i<rows;i++)
	{
		for(j=0;j<columns;j++)
		{
			distcen= sqrtf( (i-cx)*(i-cx) + (j-cy)*(j-cy) ) ;

			// find pixel from which to read data for the given warped pixel
			x_toreadfrom= (i - cx)*cos(theta0*distcen) + (j-cy)*sin(theta0*distcen) + cx ;
			y_toreadfrom= -(i - cx)*sin(theta0*distcen) + (j-cy)*cos(theta0*distcen) + cy;

			idx2= columns*i + j; // column major expansion
			
			// if pixel is within image then perform bilinear interpolation. Otherwise it will give segmentation fault
			if (x_toreadfrom<rows && x_toreadfrom>=0 && y_toreadfrom<columns && y_toreadfrom>=0 ) 
				*(im2->data+idx2) = bilinearinterpolation(impimage, rows, columns, x_toreadfrom, y_toreadfrom); //value at 
		}
	}

	//par_end=omp_get_wtime();
//	printf("MFLOPS: %f\n", 87*rows*columns/(100000*(par_end-par_start)) ); // We have counter the of FLOP to be 87 considering the %, sin(), cos(), sqrt() to be a single operation from the perspective of the programmer.

	return im2;
}


int main(int argc, char* argv[]){
  if(argc<2)
    printf("Enter filename\n");
  char* filename=argv[1];

  PPMImage *image;
  clock_t start, end;

  image = readPPM(filename);

  start=clock();
  // warping 
  PPMImage* warped_image = warping (image);
  end=clock();
 
  printf("Serial Time: %f\n", (end-start)/(double)CLOCKS_PER_SEC );

  writePPM("warpedimage.ppm",warped_image);
  return 0;
}

