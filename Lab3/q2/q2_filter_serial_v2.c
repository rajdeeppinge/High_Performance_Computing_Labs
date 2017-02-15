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
double parallel_time;


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

  PPMImageGS *filtered_image = (PPMImageGS *) malloc(sizeof(PPMImageGS));
  filtered_image->x = rows;
  filtered_image->y = cols;
  filtered_image->data = (PPMPixelGS *) malloc(rows*cols*sizeof(PPMPixelGS));
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
		  PPMPixelGS *temp2 = filtered_image->data + idx;
		  temp2->gs = 0.21*r+0.71*g+0.07*b;
		}	
    }
	
  return filtered_image;
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

	
int partition(int *arr, int left, int right) {
	int pivot = arr[right];
	int i = left-1;
	int temp, j;
	
	for(j = left; j < right; j++) {
		if(arr[j] <= pivot) {
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	
	temp = arr[i+1];
	arr[i+1] = pivot;
	arr[right] = temp;
	
	return i+1;
}

void quick_sort(int *arr, int left, int right) {
	if(right <= left) {
		return;
	}		
	int index = partition(arr, left, right);
	quick_sort(arr, left, index-1);
	quick_sort(arr, index+1, right);
}

PPMImage *filter(PPMImage *impimage)
{
	// takes in input as ppmimage
	//filters and returns a ppm

	// x,y, pixel

	int i,j, half_width = 3, ri, rj;
	int num_pixels_block = (2*half_width+1)*(2*half_width+1);
	
	int rows = impimage->x;
	int columns = impimage->y;
	
	//image 2 declaration
	PPMImage *filtered_image = (PPMImage*) malloc(sizeof(PPMImage));
  	filtered_image->x = rows;
  	filtered_image->y = columns;
  	filtered_image->data = (PPMPixel *) malloc(rows*columns*sizeof(PPMPixel));
  	
  	int r[num_pixels_block],g[num_pixels_block],b[num_pixels_block];
  	
  	int idx,idx2;
  	/*int *neighbourCount = (int *) malloc(rows*columns*sizeof(int));
  	for (i=0;i<rows;i++)
	{
		for(j=0;j<columns;j++)
		{
			*(neighbourCount+i*columns+j) = 0;
		}
	}*/
  	PPMPixel *temp;
	
	//printf("%d %d %d\n", num_pixels_block, rows, columns);
	double par_start, par_end;
	
	par_start = omp_get_wtime();
	//loop through whole image
	
	for (i=half_width;i<rows-half_width;i++)
	{
		for(j=half_width;j<columns-half_width;j++)
		{
			//idx2= columns*i + j;
			
			//neighbourCount = 0;
			//printf("%d %d %d\n", idx2, i, j);
			//if(i >= half_width && i < rows-half_width && j >= half_width && j < columns-half_width) 
			//{			
				for(ri = i-half_width; ri <= i+half_width; ri++) {
					for(rj = j-half_width; rj<=j+half_width; rj++) {
						
						//if ( ri >= 0 && ri < rows && rj >= 0 && rj < columns) {
							idx = ri*columns + rj;
							//printf("%d\n", idx);
							temp = impimage->data + idx;
							r[(2*half_width+1)*(ri-(i-half_width))+(rj-(j-half_width))] = temp->red;
							g[(2*half_width+1)*(ri-(i-half_width))+(rj-(j-half_width))] = temp->green;
							b[(2*half_width+1)*(ri-(i-half_width))+(rj-(j-half_width))] = temp->blue;
							
							//r[*(neighbourCount+i*columns+j)] = temp->red;
							//g[*(neighbourCount+i*columns+j)] = temp->green;
							//b[*(neighbourCount+i*columns+j)] = temp->blue;
							//(*(neighbourCount+i*columns+j))++;
						//}
					}
				}
			
				//quick_sort(r, 0, (*(neighbourCount+i*columns+j))-1);
				//quick_sort(g, 0, (*(neighbourCount+i*columns+j))-1);
				//quick_sort(b, 0, (*(neighbourCount+i*columns+j))-1);
				quick_sort(r, 0, num_pixels_block-1);
				quick_sort(g, 0, num_pixels_block-1);
				quick_sort(b, 0, num_pixels_block-1);
				temp = filtered_image->data + columns*i + j;
				
				/*if(*(neighbourCount+i*columns+j) % 2 == 1) {
					temp->red = r[(*(neighbourCount+i*columns+j))/2];
					temp->green = g[(*(neighbourCount+i*columns+j))/2];
					temp->blue = b[(*(neighbourCount+i*columns+j))/2];
				}
				else {
					temp->red = ( r[(*(neighbourCount+i*columns+j))/2] + r[(*(neighbourCount+i*columns+j))/2 - 1] ) / 2;
					temp->green = ( g[(*(neighbourCount+i*columns+j))/2] + g[(*(neighbourCount+i*columns+j))/2 - 1] ) / 2;
					temp->blue = ( b[(*(neighbourCount+i*columns+j))/2] + b[(*(neighbourCount+i*columns+j))/2 - 1] ) / 2;
				}*/
				
				temp->red = r[num_pixels_block/2];
				temp->green = g[num_pixels_block/2];
				temp->blue = b[num_pixels_block/2];
				
			/*}
			
			else {
				temp = impimage->data + columns*i + j;
				PPMPixel *temp2 = filtered_image->data + columns*i + j;
	  			temp2->red = temp->red;
	  			temp2->green = temp->green;
	  			temp2->blue = temp->blue; 
			}*/
		}
	}
	par_end = omp_get_wtime();
	parallel_time = par_end-par_start;

	printf("MFLOPS = %f\n", (3*half_width*half_width + 10)*rows*columns / (1000000 * parallel_time) );

	return filtered_image;
}


int main(int argc, char* argv[]){
	if(argc<2)
		printf("Enter filename\n");
    
	char* filename=argv[1];

	PPMImage *image;
	clock_t start, end;

	image = readPPM(filename);


	start=clock();

	/* float start_omp=omp_get_wtime(); */
	// PPMImageGS * x = changeImage(image);
	/* float stop_omp=omp_get_wtime(); */
	// end=clock();

	// printf("Time: %0.10f\n", (end-start)/(double)CLOCKS_PER_SEC );
	/* printf("Time: %0.10f\n", (stop_omp-start_omp) ); */
	//  writePPMGS("lenags.ppm",x);

	// warping 
	PPMImage* filtered_image = filter(image);
	end=clock();
	printf("Time: %f, Fraction of parallelizable code(p) = %f\n", (end-start)/(double)CLOCKS_PER_SEC, ((end-start)/(double)CLOCKS_PER_SEC)/parallel_time);


	writePPM("filtered_lena_serial_v2.ppm",filtered_image);
	return 0;
}

