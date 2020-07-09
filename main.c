/**
 * @author Eduardo Oliveira;
 * @copyright INSTITUTO POLITÉCNICO DO CÁVADO E DO AVE - 2019/2020 - ENGENHARIA DE SISTEMAS INFORMÁTICOS - VISÃO POR COMPUTADOR
 * @email eduardo.oliveira@ieee.org; 
 * @create date 13-02-2020 12:00:36
 * @modify date 21-04-2020 12:36:00
 * @desc Minimal Image Library for Computer Vision - Sobel and Prewitt edging methods example for Netpbm images
 * @version 0.1.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "cvision.h"

/**
 * Sobel and Prewitt edging methods
*/
int main(int argc, char const *argv[])
{
    // Verify argument insertion
    if (!argv[1] || !argv[2] || !argv[3] || !argv[4])
    {
        fprintf(stderr, "Error! Wrong argument specification.    ./program @inputname @outputname @edge_detection @threshold[0.001, 1.00]");
        getchar();
        exit(1);
    }

    // Convert string to float
    float threshold = atof(argv[4]);

    // Verify argument insertion
    if (threshold <= 0.0f || threshold > 1.0f)
    {
        fprintf(stderr, "Error! Wrong threshold value. @threshold[0.001, 1.00]");
        getchar();
        exit(1);
    }

#pragma region Memory allocation and image reading
    /** 
     * Initialization
     */
    IVC *origin = NULL, *destination = NULL, *aux = NULL;

    // Read image
    origin = vc_read_image(argv[1]);

    // Create destination and aux images
    destination = vc_image_new(origin->width, origin->height, 1, origin->levels);
    aux = vc_image_new(origin->width, origin->height, 1, origin->levels);

    // Check memory alloc
    if (!origin || !destination || !aux)
    {
        fprintf(stderr, "Memory alloc error!\nPress any key...");
        getchar();
        exit(1);
    }
#pragma endregion

#pragma region Black and White
    if (origin->channels != 1 && vc_rgb_to_gray(origin, aux)  == 1)
        puts(">> Image converted to grayscale.");
    else if (origin->channels == 1)
        memcpy(aux, origin, origin->bytesperline * origin->height);
    else
    {
        fprintf(stderr, ">> Error! Image was not converted to grayscale.\nPress any key...");
        getchar();
        exit(1);
    }
#pragma endregion

#pragma region Sobel or Prewitt edging
    if (strcmp(argv[3], "sobel")  == 0)
    {
        if (vc_gray_edge_sobel(aux, destination, threshold) == 1)
            puts(">> Sobel edge applied.");
        else
        {
            fprintf(stderr, ">> Error! Sobel edge not applied.\nPress any key...");
            getchar();
            exit(1);
        }
    }
    else if (strcmp(argv[3], "prewitt") == 0)
    {
        if (vc_gray_edge_prewitt(aux, destination, threshold) == 1)
            puts(">> Prewitt edge applied.");
        else
        {
            fprintf(stderr, ">> Error! Prewitt edge not applied.\nPress any key...");
            getchar();
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, ">> Error! Wrong edge method. Please input \"sobel\" or \"prewitt\" on the @edge_detection specification.\n./program @inputname @outputname @edge_detection @threshold[0.001, 1.00]\nPress any key...");
        getchar();
        exit(1);
    }
#pragma endregion

#pragma region Save image to file
    // Save destination image
    if (vc_write_image(argv[2], destination) == 1)
        puts(">> Image saved.");
    else{
        fprintf(stderr, ">> Error! Image not saved!\nPress any key...");
        getchar();
        exit(1);
    }
#pragma endregion

#pragma region Memory free
    /** 
     * Free memory and exit.
     */
    vc_image_free(origin);
    vc_image_free(aux);
    vc_image_free(destination);
#pragma endregion

    printf("Press any key to exit...");
    getchar();

    return 0;
}