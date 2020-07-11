/**
 * @author Eduardo Oliveira;
 * @copyright INSTITUTO POLITÉCNICO DO CÁVADO E DO AVE - 2019/2020 - ENGENHARIA DE SISTEMAS INFORMÁTICOS - VISÃO POR COMPUTADOR
 * @email eduardo.oliveira@ieee.org; 
 * @create date 13-02-2020 12:00:36
 * @modify date 21-04-2020 12:36:00
 * @desc Minimal Image Library for Computer Vision - Sobel and Prewitt edging methods example for Netpbm images
 * @version 0.1.2
 */

#define VC_DEBUG

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

#define MINWIDTH 0
#define MINHEIGHT 0

#define VC_CH_1 1
#define VC_CH_2 2
#define VC_CH_3 3

#define GRAYLEVELS 256

#define SIZEOFUCHAR 255

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// IMAGE STRUCTURE
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
	unsigned char *data;
	int width, height;
	int channels;	  // Binary/Gray = 1; RGB = 3
	int levels;		  // Binary = 1; Gray [1,255]; RGB [1,255]
	int bytesperline; // width * channels
} IVC;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// EDGE DETECTION
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @summary: Sobel edge detection
 * @src: Receives the source image pointer
 * @dst: Receives the destination image pointer
 * @th: receives the edging threshold [0.001, 1.00]
 * @return: true if the operation succeeds, false if not
*/
int vc_gray_edge_sobel(IVC *src, IVC *dst, float th);

/**
 * @summary: Prewitt edge detection
 * @src: Receives the source image pointer
 * @dst: Receives the destination image pointer
 * @th: receives the edging threshold
 * @return: true if the operation succeeds, false if not
*/
int vc_gray_edge_prewitt(IVC *src, IVC *dst, float th);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Image Convertion
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @summary: Converts a rgb image to gray scale 
 * @src: Receives the source image pointer
 * @dst: Receives the destination image pointer
 * @return true if the operation succeeds, false if not
*/
int vc_rgb_to_gray(IVC *src, IVC *dst);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Image Decomposition
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @summary: Decomposition of the red component of a rgb scale image to gray
 * @srcdst: Receives the souce/destination image pointer
 * @return true if the operation succeeds, false if not
*/
int vc_rgb_get_red_gray(IVC *srcdst);

/**
 * @summary: Decomposition of the green component of a rgb scale image to gray
 * @srcdst: Receives the souce/destination image pointer
 * @return true if the operation succeeds, false if not
*/
int vc_rgb_get_green_gray(IVC *srcdst);

/**
 * @summary: Decomposition of the blue component of a rgb scale image to gray
 * @srcdst: Receives the souce/destination image pointer
 * @return true if the operation succeeds, false if not
*/
int vc_rgb_get_blue_gray(IVC *srcdst);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Image Memory Alloc & Free
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @summary: Memory alloc for a image by parameters
 * @width: Receives the image width
 * @height: Receives the image height
 * @channels: Receives the number of image channels
 * @levels: Receives the image levels
 * @return pointer to the image structure
*/
IVC *vc_image_new(int width, int height, int channels, int levels);

/**
 * @summary: Image memory free
 * @image: Receives the image pointer
 * @return NULL if the image pointer was set free
*/
IVC *vc_image_free(IVC *image);

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Image Read and Write (PBM, PGM E PPM)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @summary: Read Image
 * @filename: Receives the file name and extension
 * @return Pointer to the struct or NULL
*/
IVC *vc_read_image(char *filename);

/**
 * @summary: Save Image
 * @filename: Receives the file name and extension
 * @image: Receives the pointer to the image in memory
 * @return True if success, or false if not
*/
int vc_write_image(char *filename, IVC *image);