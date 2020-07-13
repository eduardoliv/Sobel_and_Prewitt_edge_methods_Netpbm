/**
 * @author Eduardo Oliveira;
 * @copyright INSTITUTO POLITÉCNICO DO CÁVADO E DO AVE - 2019/2020 - ENGENHARIA DE SISTEMAS INFORMÁTICOS - VISÃO POR COMPUTADOR
 * @email eduardo.oliveira@ieee.org; 
 * @create date 13-02-2020 12:00:36
 * @modify date 21-04-2020 12:36:00
 * @desc Minimal Image Library for Computer Vision - Sobel and Prewitt edge methods example for Netpbm images
 * @version 0.1.2
 */

#define _CRT_SECURE_NO_WARNINGS

#include "cvision.h"
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
int vc_gray_edge_sobel(IVC *src, IVC *dst, float th)
{
	// Local variavles
	unsigned char *datasrc = (unsigned char *)src->data;
	unsigned char *datadst = (unsigned char *)dst->data;
	int channels = src->channels;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->bytesperline;
	int x, y, i, posA, posB, posC, posD, posX, posE, posF, posG, posH, sumx, sumy, histmax, histthreshold;
	int hist[GRAYLEVELS] = {0};

	// Error check
	if ((src->width <= MINWIDTH) || (src->height <= MINHEIGHT))
		return 0;
	if ((dst->width <= MINWIDTH) || (dst->height <= MINHEIGHT))
		return 0;
	if ((src->channels != VC_CH_1) || (dst->channels != VC_CH_1))
		return 0;

	// Get the number of pixels of the image w*h
	int size = width * height;

	// Apply the operators in x and y axis (gradient), and calculate the magnitude of the vector
	for (y = 1; y < height - 1; y++)
	{
		for (x = 1; x < width - 1; x++)
		{
			posA = (y - 1) * bytesperline + (x - 1);
			posB = (y - 1) * bytesperline + x;
			posC = (y - 1) * bytesperline + (x + 1);
			posD = y * bytesperline + (x - 1);
			posX = y * bytesperline + x;
			posE = y * bytesperline + (x + 1);
			posF = (y + 1) * bytesperline + (x - 1);
			posG = (y + 1) * bytesperline + x;
			posH = (y + 1) * bytesperline + (x + 1);

			// Derivative of xx axis
			sumx = datasrc[posA] * -1;
			sumx += datasrc[posD] * -2;
			sumx += datasrc[posF] * -1;

			sumx += datasrc[posC] * 1;
			sumx += datasrc[posE] * 2;
			sumx += datasrc[posH] * 1;
			sumx /= 4.0f;

			// Derivative of yy axis
			sumy = datasrc[posA] * -1;
			sumy += datasrc[posB] * -2;
			sumy += datasrc[posC] * -1;

			sumy += datasrc[posF] * 1;
			sumy += datasrc[posG] * 2;
			sumy += datasrc[posH] * 1;
			sumy /= 4.0f;

			// Calculate the magnitude of the vector
			datadst[posX] = (unsigned char)sqrt((double)(sumx * sumx + sumy * sumy));
		}
	}

	// Compute a grey level histogram
	for (y = 1; y < height; y++)
		for (x = 1; x < width; x++)
			hist[datadst[y * bytesperline + x]]++;

	/** Find the threshold
	 * Threshold is defined by the intensity when we reach a desired percentage of pixels
	*/
	histmax = 0;
	for (i = 0; i < GRAYLEVELS; i++)
	{
		histmax += hist[i];

		// th = Sobel Threshold
		if (histmax >= (size * th)) break;
	}
	histthreshold = i;

	// Apply the threshold
	for (y = 1; y < height; y++)
		for (x = 1; x < width; x++)
		{
			posX = y * bytesperline + x;
			if (datadst[posX] >= histthreshold)
				datadst[posX] = SIZEOFUCHAR;
			else
				datadst[posX] = 0;
		}

	return 1;
}

/**
 * @summary: Prewitt edge detection
 * @src: Receives the source image pointer
 * @dst: Receives the destination image pointer
 * @th: receives the edging threshold [0.001, 1.00]
 * @return: true if the operation succeeds, false if not
*/
int vc_gray_edge_prewitt(IVC *src, IVC *dst, float th)
{
	// Local variavles
	unsigned char *datasrc = (unsigned char *)src->data;
	unsigned char *datadst = (unsigned char *)dst->data;
	int channels = src->channels;
	int width = src->width;
	int height = src->height;
	int bytesperline = src->bytesperline;
	int x, y, i, posA, posB, posC, posD, posX, posE, posF, posG, posH, sumx, sumy, histmax, histthreshold;
	int hist[GRAYLEVELS] = {0};

	// Error check
	if ((src->width <= MINWIDTH) || (src->height <= MINHEIGHT))
		return 0;
	if ((dst->width <= MINWIDTH) || (dst->height <= MINHEIGHT))
		return 0;
	if ((src->channels != VC_CH_1) || (dst->channels != VC_CH_1))
		return 0;

	// Get the number of pixels of the image w*h
	int size = width * height;

	// Apply the operators in x and y axis (gradient), and calculate the magnitude of the vector
	for (y = 1; y < height - 1; y++)
	{
		for (x = 1; x < width - 1; x++)
		{
			posA = (y - 1) * bytesperline + (x - 1);
			posB = (y - 1) * bytesperline + x;
			posC = (y - 1) * bytesperline + (x + 1);
			posD = y * bytesperline + (x - 1);
			posX = y * bytesperline + x;
			posE = y * bytesperline + (x + 1);
			posF = (y + 1) * bytesperline + (x - 1);
			posG = (y + 1) * bytesperline + x;
			posH = (y + 1) * bytesperline + (x + 1);

			// Derivative of xx axis
			sumx = datasrc[posA] * -1;
			sumx += datasrc[posD] * -1;
			sumx += datasrc[posF] * -1;

			sumx += datasrc[posC] * +1;
			sumx += datasrc[posE] * +1;
			sumx += datasrc[posH] * +1;
			sumx /= 3.0f;

			// Derivative of yy axis
			sumy = datasrc[posA] * -1;
			sumy += datasrc[posB] * -1;
			sumy += datasrc[posC] * -1;

			sumy += datasrc[posF] * +1;
			sumy += datasrc[posG] * +1;
			sumy += datasrc[posH] * +1;
			sumy /= 3.0f;

			// Calculate the magnitude of the vector
			datadst[posX] = (unsigned char)sqrt((double)(sumx * sumx + sumy * sumy));
		}
	}

	// Compute a grey level histogram
	for (y = 1; y < height; y++)
		for (x = 1; x < width; x++)
			hist[datadst[y * bytesperline + x]]++;

	/** Find the threshold
	 * Threshold is defined by the intensity when we reach a desired percentage of pixels
	*/
	histmax = 0;
	for (i = 0; i < GRAYLEVELS; i++)
	{
		histmax += hist[i];

		// th = Prewitt Threshold
		if (histmax >= (size * th)) break;
	}
	histthreshold = i;

	// Apply the threshold
	for (y = 1; y < height; y++)
		for (x = 1; x < width; x++)
		{
			posX = y * bytesperline + x;
			if (datadst[posX] >= histthreshold)
				datadst[posX] = SIZEOFUCHAR;
			else
				datadst[posX] = 0;
		}

	return 1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Image Convertion
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @summary: Converts a rgb image to gray scale 
 * @src: Receives the source image pointer
 * @dst: Receives the destination image pointer
 * @return true if the operation succeeds, false if not
*/
int vc_rgb_to_gray(IVC *src, IVC *dst)
{
	unsigned char *datasrc = (unsigned char *)src->data;
	int bytesPerLine_src = src->width * src->channels;
	int channels_src = src->channels;
	unsigned char *datadst = (unsigned char *)dst->data;
	int bytesPerLine_dst = dst->width * dst->channels;
	int channels_dst = dst->channels;
	int width = src->width;
	int height = src->height;
	int x, y;
	long int pos_src, pos_dst;
	float rf, gf, bf;

	// Error check
	if ((src->width <= MINWIDTH) || (src->height <= MINHEIGHT))
		return 0;
	if ((src->width != dst->width) || (src->height != dst->height))
		return 0;
	if ((src->channels != VC_CH_3) || (dst->channels != VC_CH_1))
		return 0;

	// Convert image to gray scale
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos_src = y * bytesPerLine_src + x * channels_src;
			pos_dst = y * bytesPerLine_dst + x;

			rf = (float)datasrc[pos_src];
			gf = (float)datasrc[pos_src + 1];
			bf = (float)datasrc[pos_src + 2];

			datadst[pos_dst] = (unsigned char)((rf * 0.299) + (gf * 0.587) + (bf * 0.114));
		}
	}
	return 1;
}

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
IVC *vc_image_new(int width, int height, int channels, int levels)
{
	IVC *image = (IVC *)malloc(sizeof(IVC));

	if (!image) return NULL;
	if ((levels <= 0) || (levels > SIZEOFUCHAR)) return NULL;

	image->width = width;
	image->height = height;
	image->channels = channels;
	image->levels = levels;
	image->bytesperline = image->width * image->channels;
	image->data = (unsigned char *)malloc(image->width * image->height * image->channels * sizeof(char));

	if (!image->data) return vc_image_free(image);

	return image;
}

/**
 * @summary: Image memory free
 * @image: Receives the image pointer
 * @return NULL if the image pointer was set free
*/
IVC *vc_image_free(IVC *image)
{
	if (image != NULL)
	{
		if (image->data != NULL)
			free(image->data);

		free(image);
	}

	return image;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Image Read and Write (PBM, PGM E PPM)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

char *netpbm_get_token(FILE *file, char *tok, int len)
{
	char *t;
	int c;

	for (;;)
	{
		while (isspace(c = getc(file)))
			;
		if (c != '#')
			break;
		do
			c = getc(file);
		while ((c != '\n') && (c != EOF));
		if (c == EOF)
			break;
	}

	t = tok;

	if (c != EOF)
	{
		do
		{
			*t++ = c;
			c = getc(file);
		} while ((!isspace(c)) && (c != '#') && (c != EOF) && (t - tok < len - 1));

		if (c == '#')
			ungetc(c, file);
	}

	*t = 0;

	return tok;
}

long int unsigned_char_to_bit(unsigned char *datauchar, unsigned char *databit, int width, int height)
{
	int x, y;
	int countbits;
	long int pos, counttotalbytes;
	unsigned char *p = databit;

	*p = 0;
	countbits = 1;
	counttotalbytes = 0;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = width * y + x;

			if (countbits <= 8)
			{
				*p |= (datauchar[pos] == 0) << (8 - countbits);
				countbits++;
			}
			if ((countbits > 8) || (x == width - 1))
			{
				p++;
				*p = 0;
				countbits = 1;
				counttotalbytes++;
			}
		}
	}

	return counttotalbytes;
}

void bit_to_unsigned_char(unsigned char *databit, unsigned char *datauchar, int width, int height)
{
	int x, y;
	int countbits;
	long int pos;
	unsigned char *p = databit;

	countbits = 1;

	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pos = width * y + x;

			if (countbits <= 8)
			{
				datauchar[pos] = (*p & (1 << (8 - countbits))) ? 0 : 1;
				countbits++;
			}
			if ((countbits > 8) || (x == width - 1))
			{
				p++;
				countbits = 1;
			}
		}
	}
}

/**
 * @summary: Read Image
 * @filename: Receives the file name and extension
 * @return Pointer to the struct or NULL
*/
IVC *vc_read_image(char *filename)
{
	FILE *file = NULL;
	IVC *image = NULL;
	unsigned char *tmp;
	char tok[20];
	long int size, sizeofbinarydata;
	int width, height, channels;
	int levels = SIZEOFUCHAR;
	int v;

	if ((file = fopen(filename, "rb")) != NULL)
	{
		// Header reading
		netpbm_get_token(file, tok, sizeof(tok));

		if (strcmp(tok, "P4") == 0)
		{
			channels = VC_CH_1;
			levels = 1;
		} // If PBM (Binary [0,1])
		else if (strcmp(tok, "P5") == 0)
			channels = VC_CH_1; // If PGM (Gray [0,MAX(level,255)])
		else if (strcmp(tok, "P6") == 0)
			channels = VC_CH_3; // If PPM (RGB [0,MAX(level,255)])
		else
		{
#ifdef VC_DEBUG
			printf("ERROR -> vc_read_image():\n\tFile is not a valid PBM, PGM or PPM file.\n\tBad magic number!\n");
#endif

			fclose(file);
			return NULL;
		}

		if (levels == 1) // PBM
		{
			if (sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 ||
				sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tFile is not a valid PBM file.\n\tBad size!\n");
#endif

				fclose(file);
				return NULL;
			}

			// Image memory alloc
			image = vc_image_new(width, height, channels, levels);
			if (!image) return NULL;

			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height;
			tmp = (unsigned char *)malloc(sizeofbinarydata);
			if (!tmp) return 0;

#ifdef VC_DEBUG
			printf("\nchannels=%d w=%d h=%d levels=%d\n", image->channels, image->width, image->height, levels);
#endif

			if ((v = fread(tmp, sizeof(unsigned char), sizeofbinarydata, file)) != sizeofbinarydata)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tPremature EOF on file.\n");
#endif

				vc_image_free(image);
				fclose(file);
				free(tmp);
				return NULL;
			}

			bit_to_unsigned_char(tmp, image->data, image->width, image->height);

			free(tmp);
		}
		else // PGM or PPM
		{
			if (sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &width) != 1 ||
				sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &height) != 1 ||
				sscanf(netpbm_get_token(file, tok, sizeof(tok)), "%d", &levels) != 1 || levels <= 0 || levels > 255)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tFile is not a valid PGM or PPM file.\n\tBad size!\n");
#endif

				fclose(file);
				return NULL;
			}

			// Image memory alloc
			image = vc_image_new(width, height, channels, levels);
			if (!image) return NULL;

#ifdef VC_DEBUG
			printf("\nchannels=%d w=%d h=%d levels=%d\n", image->channels, image->width, image->height, levels);
#endif

			size = image->width * image->height * image->channels;

			if ((v = fread(image->data, sizeof(unsigned char), size, file)) != size)
			{
#ifdef VC_DEBUG
				printf("ERROR -> vc_read_image():\n\tPremature EOF on file.\n");
#endif

				vc_image_free(image);
				fclose(file);
				return NULL;
			}
		}

		fclose(file);
	}
	else
	{
#ifdef VC_DEBUG
		printf("ERROR -> vc_read_image():\n\tFile not found.\n");
#endif
	}

	return image;
}

/**
 * @summary: Save Image
 * @filename: Receives the file name and extension
 * @image: Receives the pointer to the image in memory
 * @return True if success, or false if not
*/
int vc_write_image(char *filename, IVC *image)
{
	FILE *file = NULL;
	unsigned char *tmp;
	long int totalbytes, sizeofbinarydata;

	if (!image) return 0;

	if ((file = fopen(filename, "wb")) != NULL)
	{
		if (image->levels == 1)
		{
			sizeofbinarydata = (image->width / 8 + ((image->width % 8) ? 1 : 0)) * image->height + 1;
			tmp = (unsigned char *)malloc(sizeofbinarydata);
			if (!tmp) return 0;

			fprintf(file, "%s %d %d\n", "P4", image->width, image->height);

			totalbytes = unsigned_char_to_bit(image->data, tmp, image->width, image->height);
			printf("Total = %ld\n", totalbytes);
			if (fwrite(tmp, sizeof(unsigned char), totalbytes, file) != totalbytes)
			{
#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
#endif
				fclose(file);
				free(tmp);
				return 0;
			}

			free(tmp);
		}
		else
		{
			fprintf(file, "%s %d %d 255\n", (image->channels == 1) ? "P5" : "P6", image->width, image->height);

			if (fwrite(image->data, image->bytesperline, image->height, file) != image->height)
			{
#ifdef VC_DEBUG
				fprintf(stderr, "ERROR -> vc_read_image():\n\tError writing PBM, PGM or PPM file.\n");
#endif
				fclose(file);
				return 0;
			}
		}
		fclose(file);
		return 1;
	}

	return 0;
}
