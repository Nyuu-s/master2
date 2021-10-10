#include "ImageBase.h"
#include <stdio.h>
#include<iostream>
#include<cmath>
#include<fstream>


enum colorSpace{ RBG_YCRCB, YCRCB_RGB};

void transformColorSpace(ImageBase &src, ImageBase &dest, colorSpace transformation ){
	
	double Y, cr, cb, r ,g ,b; 
	switch(transformation)
	{
		case RBG_YCRCB:
			
			for(int y = 0; y < src.getHeight(); ++y)
				for(int x = 0; x < src.getWidth(); ++x)
				{
					r = src[y*3][x*3];
					g = src[y*3][x*3+1];
					b = src[y*3][x*3+2];

					// Y = ( 16 + (((65.738 * r) /256) + ((129.057*g)/256) + ((25.064*b/256))));
					// cb = (128 - (((-37.945 * r)/256) - ((74.494*g)/256) + ((112.439*b)/256)));
					// cr = (128 + (((112.439 *r)/256) - ((94.154 * g)/256) - ((18.285 * b)/256)));
					
					// Y =(int) (16 + (0.257*r + 0.0504*g + 0.098*b));
					// cb = (int)(128+(-0.148*r + -0.291*g + 0.439*b));
					// cr = (int)(128+(0.439*r + -0.368*g + -0.071*b));

					
					Y = 0.257 *r + 0.504*g + 0.098*b;
					cb = -0.148*r - 0.291*g + 0.439*b+128;
					cr = 0.439*r -0.368*g -0.071*b +128;

					
					// cr = ((cr + 512) / 1024.0) * 256;

					// cb = ((cb + 512) / 1024.0) * 256;

					

					// Y = fmax(0, fmin(255, Y));
					cr = fmax(0, fmin(255, cr));

					cb = fmax(0, fmin(255, cb));

				
					
					dest[y*3][x*3] = cr;
					dest[y*3][x*3+1] = Y;
					dest[y*3][x*3+2] = cb;
				}
			
		 ;break;
		case YCRCB_RGB:
			 
			for(int y = 0; y < src.getHeight(); ++y)
				for(int x = 0; x < src.getWidth(); ++x)
				{
					cr = src[y*3][x*3];
					Y =  src[y*3][x*3+1];
					cb = src[y*3][x*3+2];
	
			
					// r = (int)(1.164 * ( y-16) + 1.596*(cr-128));
					// g = (int)(1.164*(y-16) + -0.813 * (cb -128) + -0.391*(cr-128));
					// b = (int)(1.164*(y-16) + 2.018 * (cb-128));

					// r = (y + 1.402 * (cr-128)) ;
					// g = (y - 0.34414 * (cb -128) - 0.71414 * (cr -128)) ;
					// b = (y + 1.772 * (cb-128));

					r = (int)( (((298.082 * Y)/ 256) + ((408.583*cr)/256) - 222.921 ) );
					g = (int) ((((298.082 * Y)/ 256) - ((100.291 * cb)/256) - ((208.120*cr)/256) )+ 135.576); 
					b = (int) ((((298.082 * Y)/ 256) + ((516.412 * cb) / 256)) - 276.836);

					//std::cout << r << "  " << g << " " << b;
					r =  fmax(0, fmin(255, r));
					g =  fmax(0, fmin(255, g));
					b =  fmax(0, fmin(255, b));
					
					

					dest[y*3][x*3] 	 = r;
					dest[y*3][x*3+1] = g;
					dest[y*3][x*3+2] = b;
				} 
		
		
		
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


int wavelet(ImageBase &imageIn, ImageBase &imageOut, int iterationMax, int it, float Q){

		if(it > iterationMax){
			imageOut.copy(imageIn);
			
			return it;
		}

		
		//std::cout << it << "\n";
		int width = imageIn.getWidth();
		int height = imageIn.getHeight();
		int width_by2 = imageIn.getWidth()/2;
		int height_by2 = imageIn.getHeight()/2; 

	
	//p1+p2+p3+4 / 4 upperleft
	//p1-p2+p3-p4 / 2 upperright
	//p1+p2-p3-p4 /2 lowerleft
	//p1-p2-p3+p4 lowerright
		
		ImageBase imgUpperLeft(height_by2, width_by2, imageIn.getColor());
		ImageBase imgToComplete(imageIn.getHeight(), imageIn.getWidth(), imageIn.getColor());

		for(int i = 0; i < width; i+=2){			//upper left BF
			for(int j = 0; j < height; j+=2){
				int p1 = imageIn[i][j];
				int p2 = imageIn[i][j+1];
				int p3 = imageIn[i+1][j];
				int p4 = imageIn[i+1][j+1];
				int t;
				
				imgUpperLeft[i/2][j/2] = (p1+p2+p3+p4)/4 ; //upper left


				t = (fmax((p1+p2-p3-p4)/(Q/2), -128)) +128;
				imgToComplete[height_by2 + (i/2)][j/2] = t; //lower left


				
				t = (fmax((p1-p2+p3-p4)/(Q/2), -128)) +128;
				imgToComplete[i/2][width_by2 + (j/2)] = t; // upper right




				//t = (((p1-p2-p3+p4) + 512) /1024.0) *256;

				t = (fmax((p1-p2-p3+p4)/Q, -128) +128);
				imgToComplete[height_by2 + (i/2)][width_by2 + (j/2)] = t;//lower right
			}
		}

	ImageBase imgTempOutput(imageIn.getHeight(), imageIn.getWidth(), imageIn.getColor());

	wavelet(imgUpperLeft,imgTempOutput,iterationMax, ++it, Q-iterationMax);

	for (int i = 0; i < imgTempOutput.getHeight(); i++)
	{
		for (int j = 0; j < imgTempOutput.getWidth(); j++)
		{
			imgToComplete[i][j] = imgTempOutput[i][j];	
		}
	}
	
	imageOut.copy(imgToComplete);
		
	return it;

}

int unQuantization(ImageBase &imageIn, ImageBase &imageOut, int iterationMax, int it, float Q){
	if(it > iterationMax){
			imageOut.copy(imageIn);
			
			return it;
		}

		
		//std::cout << it << "\n";
		int width = imageIn.getWidth();
		int height = imageIn.getHeight();
		int width_by2 = imageIn.getWidth()/2;
		int height_by2 = imageIn.getHeight()/2; 

	
	//p1+p2+p3+4 / 4 upperleft
	//p1-p2+p3-p4 / 2 upperright
	//p1+p2-p3-p4 /2 lowerleft
	//p1-p2-p3+p4 lowerright
		
		ImageBase imgUpperLeft(height_by2, width_by2, imageIn.getColor());
		ImageBase imgToComplete(imageIn.getHeight(), imageIn.getWidth(), imageIn.getColor());

		for(int i = 0; i < width; i+=2){			//upper left BF
			for(int j = 0; j < height; j+=2){
				int p1 = imageIn[i][j];
				int p2 = imageIn[i][j+1];
				int p3 = imageIn[i+1][j];
				int p4 = imageIn[i+1][j+1];
				int t;
				
				imgUpperLeft[i/2][j/2] = imageIn[i/2][j/2]; //upper left


				t = imageIn[height_by2 + (i/2)][j/2] * (Q/2);
				t = t;

				
				std::cout << t << std::endl;
				imgToComplete[height_by2 + (i/2)][j/2] = t = fmax(t, -127) +128;; //lower left


				
				t = imageIn[i/2][width_by2 + (j/2)] *  (Q / 2);
				imgToComplete[i/2][width_by2 + (j/2)] = fmax(-128, t) + 128; // upper right




				//t = (((p1-p2-p3+p4) + 512) /1024.0) *256;

				t = imageIn[height_by2 + (i/2)][width_by2 + (j/2)] * Q;
				imgToComplete[height_by2 + (i/2)][width_by2 + (j/2)] = fmax(t, -128) +128 ;//lower right
			}
		}

	ImageBase imgTempOutput(imageIn.getHeight(), imageIn.getWidth(), imageIn.getColor());

	unQuantization(imgUpperLeft,imgTempOutput,iterationMax, ++it, Q/2);

	for (int i = 0; i < imgTempOutput.getHeight(); i++)
	{
		for (int j = 0; j < imgTempOutput.getWidth(); j++)
		{
			imgToComplete[i][j] = imgTempOutput[i][j];	
		}
	}
	
	imageOut.copy(imgToComplete);
		
	return it;
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

		
		
	
		//espace  YCRCB


	ImageBase imYCrCb(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	ImageBase imOutput(imIn.getHeight(), imIn.getWidth(), imIn.getColor());


	transformColorSpace(imIn, imYCrCb, RBG_YCRCB);
	imYCrCb.save("test");


	ImageBase Y(imIn.getHeight(), imIn.getWidth(), 	false);
	ImageBase Cr(imIn.getHeight(), imIn.getWidth(), false);
	ImageBase Cb(imIn.getHeight(), imIn.getWidth(), false);
			
	Cr.copy(*imYCrCb.getPlan(ImageBase::PLAN_R));
	Y.copy (*imYCrCb.getPlan(ImageBase::PLAN_G));
	Cb.copy(*imYCrCb.getPlan(ImageBase::PLAN_B));

	
	ImageBase t1(imIn.getHeight(), imIn.getWidth(), false);
	ImageBase t2(imIn.getHeight(), imIn.getWidth(), false);
	ImageBase t3(imIn.getHeight(), imIn.getWidth(), false);

	int iteationMax = 4;
	int n = 1;
	int Q = 16;

	wavelet(Y,  t1 , iteationMax, n, Q);
	unQuantization(t1, Y, iteationMax ,n, Q);
	std::cout << "Finished wavelet of Y ... \n";
	Q = 18;
	wavelet(Cr, t2 , iteationMax, n, Q);

	std::cout << "Finished wavelet of Cr ... \n";
	wavelet(Cb, t3 , iteationMax, n, Q);

	std::cout << "Finished wavelet of Cb ... \n";

//debug --
	std::cout << "Saving wavelets Y Cr Cb apart \n";
	Y.save("Y");
	t2.save("Cr");
	t3.save("Cb");

//--


	std::cout << imYCrCb.getHeight() << " " << t1.getHeight() <<"\n";
	for (unsigned int i = 0; i < imYCrCb.getHeight(); i++)
	{
		for (int j = 0; j < imYCrCb.getWidth(); j++)
		{
			imYCrCb[i*3][j*3] 	= t1[i][j];
			imYCrCb[i*3][j*3+1] = t2[i][j];
			imYCrCb[i*3][j*3+2] = t3[i][j];
		}
		
	}
	

	imYCrCb.save(cNomImgEcrite);
	






	//filtre passe bas : moyenne 2 pixel
	//filtre passe haut: difference entre 2 pixel voisin





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