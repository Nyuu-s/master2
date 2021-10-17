#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>




int main(int argc, char **argv) {

	char cNomImgLue[250], cNomImgEcrite[250];
	int S;
  
	if (argc != 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

    imOut[0][0] = imIn[0][0];

	for(int x = 0; x < imIn.getHeight(); ++x)
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
            if(y != 0 && x != 0){
                int temp  = imIn[x][y-1] - imIn[x][y];
                if(temp < -128){
                    temp = -128;
                }
                else if (temp > 128 )
                {
                    temp = 128;
                }
                imOut[x][y] = temp + 128;
            }
            else if( y == 0){
                int temp = imIn[x-1][y] - imIn[x][y];
                if(temp < -128){
                    temp = -128;
                }
                else if (temp > 128 )
                {
                    temp = 128;
                }
                imOut[x][y] = temp +128;
            }
           
		}

    imOut.save(cNomImgEcrite);

    // ImageBase predi(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

    // predi[0][0] = imOut[0][0];
    // for(int x = 0; x < imIn.getHeight(); ++x)
	// 	for(int y = 0; y < imIn.getWidth(); ++y)
	// 	{

    //         if(y != 0 && x != 0){
    //             int temp  = imIn[x][y-1] + imOut[x][y-1];
    //             if(temp > 255){
    //                 temp = 255;
    //             }
                
    //             predi[x][y] = temp;
    //         }
    //         else if( y == 0){
    //             int temp = imIn[x-1][y] - imOut[x][y];
    //             if(temp > 255){
    //                 temp = 255;
    //             }
    //             predi[x][y] = temp;
    //         }          
	// 	}
		
	
	// predi.save("reconstruction.pgm");

		



	///////////////////////////////////////// Exemple de création d'une image en niveau de gris






}

