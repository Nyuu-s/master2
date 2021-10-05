#include "ImageBase.h"
#include <stdio.h>
#include <cmath>
#include <vector>
#include<iostream>

ImageBase imIn;
ImageBase imOut;

typedef struct couleur {
    int r;
    int g;
    int b;
} couleur;

struct {
    std::vector<couleur> palette;
    std::vector<int> n;
} colorMoyenne;

std::vector<couleur> palette;




int getDistance(int index, int x, int y){
	return sqrt(pow(imIn[y*3][x*3] - colorMoyenne.palette[index].r, 2) +
    			pow(imIn[y*3][x*3+1] - colorMoyenne.palette[index].g, 2) +
    			pow(imIn[y*3][x*3+2] - colorMoyenne.palette[index].b, 2)
				);
}

void Kmean()
{
	
	int dmin = INFINITY;
	for(int y = 0; y < imIn.getHeight(); ++y){
		for(int x = 0; x < imIn.getWidth(); ++x)
		{
			for(int i=0; i< colorMoyenne.palette.size(); i++){

				int d = getDistance(i, x, y);
				if(d < dmin)
				{
					
					imOut[y*3][x*3] = 	colorMoyenne.palette[i].r;
                	imOut[y*3][x*3+1] = colorMoyenne.palette[i].g;
                	imOut[y*3][x*3+2] = colorMoyenne.palette[i].b;
                    
                    colorMoyenne.palette[i].r += (int)imIn[y*3][x*3];
                    colorMoyenne.palette[i].g += (int)imIn[y*3][x*3+1];
                    colorMoyenne.palette[i].b += (int)imIn[y*3][x*3+2];
                    colorMoyenne.n[i]++;
				}
			}

			for(int i=0; i< colorMoyenne.palette.size(); i++){
				colorMoyenne.palette[i].r /= colorMoyenne.n[i];
				colorMoyenne.palette[i].g /= colorMoyenne.n[i];
				colorMoyenne.palette[i].b /= colorMoyenne.n[i];

				//imOut[y*3][x*3] = 	colorMoyenne.palette[i].r;
                //imOut[y*3][x*3+1] = colorMoyenne.palette[i].g;
               // imOut[y*3][x*3+2] = colorMoyenne.palette[i].b;
			}
		}
	}
}

void initPaletteRandom(int n,int  h, int w, ImageBase* imIn) {

	palette.resize(n);
    colorMoyenne.palette.resize(n);
    colorMoyenne.n.resize(n);
    
    srand(time(NULL));
	
    for (int i = 0; i < n; i++) {
    	palette[i].r = rand() % h;
       	palette[i].g = rand() % h;
        palette[i].b = rand() % h;
	}
	
}

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	
  
	if (argc != 2) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	
	
	
	//ImageBase imIn, imOut;

	imIn.load(cNomImgLue);


	int h = imIn.getHeight();
	int w = imIn.getWidth();
		

	
	
	///////////////////////////////////////// Exemple de création d'une image couleur
	
	int nR, nB, nG;
	int CCR1, CCG1, CCB1, CCR2, CCG2, CCB2; // Class Coulor Red 1 etc....
   CCR1 = 73;
   CCG1 = 22;
   CCB1 = 52;

   CCR2 = 47;
   CCG2 = 55;
   CCB2 = 13;


 //ImageBase im1(imIn.getHeight(), imIn.getWidth(), imIn.getColor());

 ImageBase im2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());


	int n,m = 0;
	int moyCR1 = 0; 
	int moyCG1 = 0;
	int moyCB1 = 0;

	int moyCR2 = 0; 
	int moyCG2 = 0;
	int moyCB2 = 0;
	int d1;
	int d2;
	

while((moyCB1 != CCB1 && moyCG1 != CCG1 && moyCR1 != CCR1) ){


	for(int y = 0; y < im2.getHeight(); ++y)
		for(int x = 0; x < im2.getWidth(); ++x)
		{
			nR = imIn[y*3][x*3+0]; // R
			nG = imIn[y*3][x*3+1]; // G
			nB = imIn[y*3][x*3+2]; // B

			
      		d1 = sqrt( ((nR - CCR1) * (nR - CCR1)) + ( (nG - CCG1)*(nG - CCG1) ) + ( (nB - CCB1) * (nB - CCB1)) );
      		d2 = sqrt( ((nR - CCR2) * (nR - CCR2)) + ( (nG - CCG2)*(nG - CCG2) ) + ( (nB - CCB2) * (nB - CCB2)) );


			if(d1 < d2){

				
				//im1[y*3][x*3+0] = CCR1;
				//im1[y*3][x*3+1] = CCG1;
				//im1[y*3][x*3+2] = CCB1;

				moyCR1 += nR;
				moyCG1 += nG;
				moyCB1 += nB;
				n++;
			}	
			else
			{

				//im1[y*3][x*3+0] = CCR2;
				//im1[y*3][x*3+1] = CCG2;
				//im1[y*3][x*3+2] = CCB2;

				moyCR2 += nR;
				moyCG2 += nG;
				moyCB2 += nB;
				
				m++;

			}

		} 
		moyCB1, moyCG1, moyCR1 /= n;
		moyCB2, moyCG2, moyCR2 /= m;
		
		CCR1 = moyCR1;
		CCR2 = moyCR2;
		CCG1 = moyCG1;
		CCG2 = moyCG2;
		CCB1 = moyCB1;
		CCB2 = moyCB2;
		n = 0;
		m = 0;
		moyCB1,moyCB2,moyCG1,moyCG2,moyCR1,moyCR2 = 0;
		


}
	//im1.save("image1.ppm");


		for(int y = 0; y < im2.getHeight(); ++y)
			for(int x = 0; x < im2.getWidth(); ++x)
		{
			
			
			nR = imIn[y*3][x*3+0]; // R
			nG = imIn[y*3][x*3+1]; // G
			nB = imIn[y*3][x*3+2]; // B

			
      		d1 = sqrt( ((nR - CCR1) * (nR - CCR1)) + ( (nG - CCG1)*(nG - CCG1) ) + ( (nB - CCB1) * (nB - CCB1)) );
      		d2 = sqrt( ((nR - CCR2) * (nR - CCR2)) + ( (nG - CCG2)*(nG - CCG2) ) + ( (nB - CCB2) * (nB - CCB2)) );

			if(d1<d2){

				im2[y*3][x*3+0] = CCR1;
				im2[y*3][x*3+1] = CCG1;
				im2[y*3][x*3+2] = CCB1;
			}
			else{

				im2[y*3][x*3+0] = moyCR2;
				im2[y*3][x*3+1] = moyCG2;
				im2[y*3][x*3+2] = moyCB2;
			}


		}


	im2.save("image2.ppm");
		

	
	couleur a = {0,0,0};
	palette.push_back(a);
	colorMoyenne.palette.push_back(a);
	colorMoyenne.n.push_back(0);
	//initPaletteRandom(256, h, w, &imIn);
	Kmean();

	imOut.save("image256.ppm");





		

	//ImageBase imC2, imG2;
	
	///////////////////////////////////////// Exemple lecture image couleur
//	imC2.load("imC.ppm");
	///////////////////////////////////////// Exemple lecture image en niveau de gris
//	imG2.load("imG.pgm");
	
	

	///////////////////////////////////////// Exemple de récupération d'un plan de l'image
/*	ImageBase *R = imC2.getPlan(ImageBase::PLAN_R);
	R->save("R.pgm");
	delete R;
*/	


	return 0;
}	
