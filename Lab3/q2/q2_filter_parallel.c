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

/*
	function to perform partition of array for quick sort
*/	
int partition(double *arr, int left, int right) {
	double pivot = arr[right];
	int i = left-1;
	double temp;
	int j;
	
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

/*
	quick sort
*/
void quick_sort(double *arr, int left, int right) {
	if(right <= left) {
		return;
	}		
	int index = partition(arr, left, right);
	quick_sort(arr, left, index-1);
	quick_sort(arr, index+1, right);
}

/* 
	function to perform the median filtering of given image
	input: image and its half_width
	output: filtered image
*/
PPMImage *filter(PPMImage *impimage, int half_width)
{
	int i,j, ri, rj;

	// total block/mask/stencil size for given half-width
	int num_pixels_block = (2*half_width+1)*(2*half_width+1);
	
	int rows = impimage->x;
	int columns = impimage->y;
	
	//image 2 declaration
	PPMImage *filtered_image = (PPMImage*) malloc(sizeof(PPMImage));
  	filtered_image->x = rows;
  	filtered_image->y = columns;
  	filtered_image->data = (PPMPixel *) malloc(rows*columns*sizeof(PPMPixel));
  	
	// arrays storing the rgb components of all pixels in the stencil
  	double r[num_pixels_block],g[num_pixels_block],b[num_pixels_block];
  	
  	int idx,idx2;

	// counter which finds out total number of pixels actually present in the stencil
  	int neighbourCount;
  	
  	PPMPixel *temp;

	// loop through whole image
	// NOTE: Here we are collapsing only the two outer loops. We cannot collapse the inner loops since the iterating variables are dependent
	# pragma omp parallel for collapse(2) \
    shared (rows,columns,impimage,filtered_image) \
    private (i,j,neighbourCount,ri,rj,idx,temp,r,g,b,idx2)
	for (i=0;i<rows;i++)
	{
		for(j=0;j<columns;j++)
		{
			idx2= columns*i + j;
			
			neighbourCount = 0;

			// traversing through the whole stencil
			for(ri = i-half_width; ri <= i+half_width; ri++) {
				for(rj = j-half_width; rj<=j+half_width; rj++) {
					
					// if the pixel is in the image then only read its value
					if ( ri >= 0 && ri < rows && rj >= 0 && rj < columns) {
						idx = ri*columns + rj;
						temp = impimage->data + idx;
						
						r[neighbourCount] = temp->red;
						g[neighbourCount] = temp->green;
						b[neighbourCount] = temp->blue;
						neighbourCount++;
					}
				}
			}
		
			// sort the r, g, b arrays
			quick_sort(r, 0, neighbourCount-1);
			quick_sort(g, 0, neighbourCount-1);
			quick_sort(b, 0, neighbourCount-1);
			temp = filtered_image->data + idx2;
			
			// get the median value
			if(neighbourCount % 2 == 1) {
				temp->red = r[neighbourCount/2];
				temp->green = g[neighbourCount/2];
				temp->blue = b[neighbourCount/2];
			}
			else {
				temp->red = ( r[neighbourCount/2] + r[neighbourCount/2 - 1] ) / 2;
				temp->green = ( g[neighbourCount/2] + g[neighbourCount/2 - 1] ) / 2;
				temp->blue = ( b[neighbourCount/2] + b[neighbourCount/2 - 1] ) / 2;
			}
		}
	}

	return filtered_image;
}


int main(int argc, char* argv[]){
	if(argc<3)
		printf("Enter filename\n");
    
	char* filename=argv[1];

	// taking the half-width as input
	int half_width = atoi(argv[2]);

	PPMImage *image;
	float start, end;

	image = readPPM(filename);

	start=omp_get_wtime();
	PPMImage* filtered_image = filter(image, half_width);
	end=omp_get_wtime();

	printf("Parallel Time: %f\n", (end-start));

	writePPM("filtered_image_parallel.ppm",filtered_image);
	return 0;
}

