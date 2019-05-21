#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

/*linux framebuffer default supports u32 [b g r a]*/

int main(int argc,char* argv[])
 {
     int fbfd = 0;
     struct fb_var_screeninfo vinfo;
     struct fb_fix_screeninfo finfo;
     long int screensize = 0;
     char *fbp = 0;
     int x = 0, y = 0;
     long int location = 0;
     int startx=0, starty=0;     
     int width, height; 

	 if (argc < 2)
	 {
		 perror("Error ! ./fb_show <file_bgra>\n");
         exit(1);
	 }

     // Open the file for reading and writing
     fbfd = open("/dev/fb0", O_RDWR);
     if (fbfd == -1) {
         perror("Error: cannot open framebuffer device");
         exit(1);
     }
     printf("The framebuffer device was opened successfully.\n");

     // Get fixed screen information
     if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
         perror("Error reading fixed information");
         exit(2);
     }

     // Get variable screen information
     if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
         perror("Error reading variable information");
         exit(3);
     }

	 /* Refresh buffer manually */
	 vinfo.activate |= FB_ACTIVATE_NOW | FB_ACTIVATE_FORCE;
	 if(0 > ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
	   perror("Error Failed to refresh\n");
	   exit(4);
	 }

     printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

     // Figure out the size of the screen in bytes
     screensize = vinfo.yres * finfo.line_length;
     printf("screensize %ld\n", screensize);


     // Map the device to memory
     fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
                        fbfd, 0);
     if ((int)fbp == -1) {
         perror("Error: failed to map framebuffer device to memory");
         exit(4);
     }
     printf("The framebuffer device was mapped to memory successfully.\n");

     startx = 0; starty = 0;       // Where we are going to put the pixel
     width = 200;
     height = 100;

	 #if 1
	 FILE *fp;
	 fp = fopen((const char*)argv[1],"rb");
	 if (fp  == NULL)
	 {
         printf("Error: failed to open %s\n",argv[1]);
         exit(5);			
	 }
	 
	 fseek(fp,0,SEEK_END); 
	 int len =  ftell(fp); 
	 fseek(fp,0,SEEK_SET); 
	 fread(fbp,sizeof(char),len,fp);
	 fclose(fp);
	 #endif
	 
	 #if 0
     // Figure out where in memory to put the pixel
     for (y = starty; y < height + starty; y++)
         for (x = startx; x < width + startx; x++) {

             location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;
         
             //printf("%ld \n", location);    

             if (vinfo.bits_per_pixel == 32) {
                 *(fbp + location) = 10;        // Some blue
                 *(fbp + location + 1) = 15+(x-startx)/2;     // A little green
                 *(fbp + location + 2) = 200-(y-starty)/5;    // A lot of red
                 *(fbp + location + 3) = 0;      // No transparency
             } else  { //assume 16bpp
                 int b = 10;
                 int g = (x-startx)/6;     // A little green
                 int r = 31-(y-starty)/16;    // A lot of red
                 unsigned short int t = r<<11 | g << 5 | b;
                 *((unsigned short int*)(fbp + location)) = t;
             }

         }
	 #endif
	 
     munmap(fbp, screensize);
     close(fbfd);
     getchar();   
	 
     return 0;
 }
