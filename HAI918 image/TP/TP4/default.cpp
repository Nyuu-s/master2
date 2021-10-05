#include "ImageBase.h"
#include <stdio.h>
#include<iostream>
#include<cmath>

enum colorSpace{ RBG_YCRCB, YCRCB_RGB};
enum Neighbors{ PREVIOUS = 2, CROSS = 4, SQUARE = 8};

void transformColorSpace(ImageBase &src, ImageBase &dest, colorSpace transformation ){
	

	switch(transformation)
	{
		case RBG_YCRCB:
			unsigned char Y, cr, cb, r ,g ,b; 
			for(int y = 0; y < src.getHeight(); ++y)
				for(int x = 0; x < src.getWidth(); ++x)
				{
					r = src[y*3][x*3];
					g = src[y*3][x*3+1];
					b = src[y*3][x*3+2];
					Y = 0.299 * r + 0.587*g + 0.114*b;
					cb = (b-Y) / (2-2*0.114*b)+128;
					cr = (r-Y) / (2-2*0.299*r)+128;
					
					
					dest[y*3][x*3] = cr;
					dest[y*3][x*3+1] = Y;
					dest[y*3][x*3+2] = cb;
				}
			
		 ;break;
		case YCRCB_RGB:
			/*unsigned char y, cr, cb, r ,g ,b; 
			for(int y = 0; y < src.getHeight(); ++y)
				for(int x = 0; x < src.getWidth(); ++x)
				{
					y = src[y*3][x*3];
					cb = src[y*3][x*3+1];
					cr = src[y*3][x*3+2];
					r = 0.299 * r + 0.587*g + 0.114*b;
					cb = (b-y) / (2-2*0.114*b)+128;
					cr = (r-y) / (2-2*0.299*r)+128;

					
					dest[y*3][x*3] = y;
					dest[y*3][x*3+1] = cb;
					dest[y*3][x*3+2] = cr;
				} */
		
		
		
		 ;break;
	}

};


double calcEQM(ImageBase &imIn, ImageBase &imIn2){

	double eqm_r = 0;
    double eqm_g = 0;
    double eqm_b = 0;

    for(int y = 0; y < imIn.getHeight(); y++) {
        for (int x = 0; x < imIn.getWidth(); x++) {
            eqm_r += pow(imIn[y][x]   - imIn2[y][x],   2);
            eqm_g += pow(imIn[y][x+1] - imIn2[y][x+1], 2);
            eqm_b += pow(imIn[y][x+2] - imIn2[y][x+2], 2);
        }
    }

    return (eqm_r + eqm_g + eqm_b) / (imIn.getTotalSize() * 3);
}
double calcPSNR(ImageBase &image1, ImageBase &image2){

	return (10 * log10(pow(255,2) / calcEQM(image1, image2) ));
}

void reduceBy(int reducer, ImageBase &imageOut, ImageBase imageIn){
	for(int y = 0; y < imageIn.getHeight(); ++y)
			for(int x = 0; x < imageIn.getWidth(); ++x)
			{

				if(y % reducer != 0 && x % reducer != 0){

					imageOut[y*3][x*3+0] =  imageIn[y*3][x*3+0];
					imageOut[y*3][x*3+1] =  imageIn[y*3][x*3+1];
					imageOut[y*3][x*3+2] = 	imageIn[y*3][x*3+2];		
				}
			}

}

void recomposeBy(Neighbors n, int reducer,  ImageBase imageIn, ImageBase &imageOut){
		
		
		for(int y = 0; y < imageIn.getHeight(); ++y)
			for(int x = 0; x < imageIn.getWidth(); ++x)
			{

				if(!(y % reducer != 0 && x % reducer != 0)){
					switch (n)
					{
					case PREVIOUS:
									imageOut[y*3][x*3+0] = (imageIn[y*3][x*3] + imageIn[y*3][x*3+3]) / PREVIOUS;
									imageOut[y*3][x*3+1] = (imageIn[y*3][x*3+1] +  imageIn[y*3][x*3+4]) /PREVIOUS;
									imageOut[y*3][x*3+2] = (imageIn[y*3][x*3+2] +  imageIn[y*3][x*3+5]) /PREVIOUS;
						break;

					case CROSS:
						
									imageOut[y*3][x*3+0] = (imageIn[y*3][x*3] + imageIn[y*3][x*3+3] + imageIn[y*3][x*3-3] + imageIn[y*3][x*3+3]) / CROSS;
									imageOut[y*3][x*3+1] = (imageIn[y*3][x*3+1] +  imageIn[y*3][x*3+4]) /CROSS
									imageOut[y*3][x*3+2] = (imageIn[y*3][x*3+2] +  imageIn[y*3][x*3+5]) /CROSS;
						break;

					case SQUARE:
						/* code */
						break;
					
					default:
						break;
					}

					imageOut[y*3][x*3+0] =  imageIn[y*3][x*3+0];
					imageOut[y*3][x*3+2] = imageIn[y*3][x*3+2];		
				}
			}
}


int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	
  
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
		
	///////////////////////////////////////// Exemple de création d'une image couleur

	//espace RGB

	reduceBy(2, imOut, imIn);
	recomposeBy()

		else {

				imOut[y*3][x*3+0] = (imIn[y*3][x*3] + imIn[y*3][x*3+3]) / 2;
				imOut[y*3][x*3+2] = (imIn[y*3][x*3+2] +  imIn[y*3][x*3+4]) /2 ;
			}
			
			imOut[y*3][x*3+1] = imIn[y*3][x*3+1]; // B
		}

		std::cout << calcPSNR(imIn, imOut);

		imOut.save(cNomImgEcrite);
		
	
		//espace  YCRCB


	ImageBase imYCrCb(imIn.getHeight(), imIn.getWidth(), imIn.getColor());

	transformColorSpace(imIn, imYCrCb, RBG_YCRCB);

	imYCrCb.save("outputYCrCb.ppm");


	/*///////////////////////////////////////// Exemple de création d'une image en niveau de gris
	ImageBase imG(50, 100, false);

	for(int y = 0; y < imG.getHeight(); ++y)
		for(int x = 0; x < imG.getWidth(); ++x)
			imG[y][x] = 50;

	imG.save("imG.pgm");




	ImageBase imC2, imG2;
	
	///////////////////////////////////////// Exemple lecture image couleur
	imC2.load("imC.ppm");
	///////////////////////////////////////// Exemple lecture image en niveau de gris
	imG2.load("imG.pgm");
	
	

	///////////////////////////////////////// Exemple de récupération d'un plan de l'image
	ImageBase *R = imC2.getPlan(ImageBase::PLAN_R);
	R->save("R.pgm");
	delete R;
	*/


	return 0;
}
