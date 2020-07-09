# Sobel_and_Prewitt_edging_methods_Netpbm
Minimal Image Library for Computer Vision - Sobel and Prewitt edging methods example for Netpbm images

## Usage
* Open Linux terminal, navigate to the application folder and run ./edging \[inputname] \[outputname] \[edge_detection] \[threshold]
    * \[inputname]> Is the origin Netpbm image name and extension. Must be in the same folder as the executable.
    * \[outputname]> Is the destination Netpbm image name and extension. For a correct use, save the image with the .pgm extension.
    * \[edge_detection]> The edging method, must be \"sobel\" or \"prewitt\".
    * \[threshold]> The threshold to consider. Must be between \[0.001, 1.00\].
    
## Compilation
* Compile via Linux make command
    * Use \<make\> to create the executable
    * Use \<make clean\> to clean the object files
    
## Dependencies
* To compile, you need the make command
    * make: sudo apt-get install make

## Release History
* 0.0.1
    * Create README.md
 
## Meta
> Eduardo Oliveira - eduardo.oliveira@ieee.org;

