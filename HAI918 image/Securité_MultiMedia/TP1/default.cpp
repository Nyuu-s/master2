#include "ImageBase.h"
#include <stdio.h>
#include<iostream>
#include<cmath>

enum colorSpace{ RBG_YCRCB, YCRCB_RGB};



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


int getSequence(unsigned int key, int h, int w, bool color, ImageBase &output){
	srand(key);

	switch (color)
	{
	case true: 
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				//std::cout << rand() << std::endl;
				output[i*3][j*3]  = rand() % 255;
				output[i*3][j*3+1] = rand() % 255;
				output[i*3][j*3+2] = rand() % 255;
			}
		break;

	case false: 
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				//std::cout << rand() << std::endl;
				output[i][j]  = rand() % 255;

			}
		break;
	default:
		break;
	}

	
	
	return 0;
}

void XorCrypt(ImageBase &ImgIn, ImageBase &ImgRand, ImageBase &output ){
	
	switch (ImgIn.getColor())
	{
	case true:
		for (int i = 0; i < ImgIn.getHeight(); i++)
		{
			for (int j = 0; j < ImgIn.getWidth(); j++)
			{
				output[i*3][j*3] 	= ImgIn[i*3][j*3] 	^ ImgRand[i*3][j*3];
				output[i*3][j*3+1] 	= ImgIn[i*3][j*3+1] ^ ImgRand[i*3][j*3 +1];
				output[i*3][j*3+2] 	= ImgIn[i*3][j*3+2] ^ ImgRand[i*3][j*3+2];
			}
			
		}
		break;
		case false:
			for (int i = 0; i < ImgIn.getHeight(); i++)
			{
				for (int j = 0; j < ImgIn.getWidth(); j++)
				{
					output[i][j] 	= ImgIn[i][j] 	^ ImgRand[i][j];

				}
				
			}
		break;
	
	default:
		break;
	}
	for (int i = 0; i < ImgIn.getHeight(); i++)
	{
		for (int j = 0; j < ImgIn.getWidth(); j++)
		{
			output[i][j] = ImgIn[i][j] ^ ImgRand[i][j];
		}
		
	}
	
}




double Entropy(ImageBase &imIn){
// 	somme = 0
// Pour i de 0 à 256   //Histogramme des niveaux de gris entre 0 et 256 donc
//    pi = histogramme[i] / taille_image
//    somme = somme -  pi*(log(pi)/log(2));
// retourner somme
	
	double sum = 0.0;
	double p_i = 0;
	Histogram hist = imIn.Histo();
	for (int i = 0; i < 256; i++)
	{
		p_i = hist.data[i] / (double) imIn.getTotalSize();
		if(p_i != 0){
			sum -= p_i * (log(p_i) / log(2));
		}
		
	}
	 return sum;
}

void planBinaire(int k, ImageBase &imIn, ImageBase &output){

	for (int i = 0; i < imIn.getHeight(); i++)
	{
		for (int j = 0; j < imIn.getWidth(); j++)
		{

			switch(k)
			{
				case 0: 	output[i][j] = imIn[i][j] & 1; 		break;
				case 1: 	output[i][j] = imIn[i][j] & 2; 		break;
				case 2: 	output[i][j] = imIn[i][j] & 4; 		break;
				case 3: 	output[i][j] = imIn[i][j] & 8; 		break;
				case 4: 	output[i][j] = imIn[i][j] & 16;		break;
				case 5: 	output[i][j] = imIn[i][j] & 32;		break;
				case 6: 	output[i][j] = imIn[i][j] & 64;		break;
				default: 	output[i][j] = imIn[i][j] & 128;	break;
			}
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
	
	ImageBase ImRand(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	ImageBase ImOut(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	ImageBase ImOutDecrypt(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	
	getSequence(255, imIn.getHeight(), imIn.getHeight(), imIn.getColor(), ImRand);
	XorCrypt(imIn, ImRand, ImOut);

	XorCrypt(ImOut, ImRand, ImOutDecrypt);


	ImageBase ImOut2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	getSequence(38, imIn.getHeight(), imIn.getHeight(), imIn.getColor(), ImRand);
	XorCrypt(imIn, ImRand, ImOut2);
	std::cout <<  "PSNR des deux images : " << calcPSNR(ImOut, ImOut2) << std::endl;



	std::cout <<  "PSNR des images source et déchiffée : " << calcPSNR(imIn, ImOutDecrypt) << std::endl;

	ImOut.save(cNomImgEcrite);
	ImOutDecrypt.save("output_decrypt.pgm");

	imIn.HistoSave(imIn.Histo(), "ImageClaire.dat");

	ImOut.HistoSave(ImOut.Histo(), "ImageChirffree .dat");
	std::cout << Entropy(imIn) << "  " << Entropy(ImOut) << std::endl;



	ImageBase imgBinary(imIn.getWidth(), imIn.getWidth(), imIn.getColor());
	planBinaire(4, imIn, imgBinary);
	imgBinary.save("PlanBinaire.ppm");


	return 0;
}
