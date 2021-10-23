#include "ImageBase.h"
#include <stdio.h>
#include<iostream>

#include <cstdlib>

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

int getSequence(unsigned int key, int h, int w, ImageBase &output){  // surcharge 1 bit par pixel (pour insertion)
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
			{
				
				output[i][j]  = rand() % 2;

			}
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

void insertMessage(ImageBase& imIn,ImageBase& imMSG,  ImageBase& imOut, int k){
	if(k > 7){
		k = 7;
	}
	
	for (int i = 0; i < imIn.getHeight(); i++)
	{
		for (int j = 0; j < imIn.getWidth(); j++)
		{
			if(!(i == 0 || j == 0)){ // for xor image

				
				int bit_rank = pow(2,k);
				int bit_diff = 255 - bit_rank;
				int mask = imMSG[i][j] & bit_rank;
				switch (k)
				{
				case 0:
						
																//if bit from message == 1 	
						if(mask == 1){
							if((imIn[i][j] & 1) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + 1;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}
					break;
				case 1:											// same as above for each bit
						
																
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}
					break;
				case 2:
						
																
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}
					break;
				case 3:
						
																	
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_rank;
						}
					break;
				case 4:
						
																	
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}
					break;
				case 5:
						
																
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}
					break;
				case 6:
						
																	
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}
					break;
				default:
						
																 	
						if(mask == 1){
							if((imIn[i][j] & bit_rank) != 1){ 			
								imOut[i][j] = imIn[i][j] + bit_rank;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else										
						{
							imOut[i][j] = imIn[i][j] & bit_diff;
						}

					break;
				}
			}
			else
			{
				imOut[i][j] = imIn[i][j];
			}

		}
		
	}
	
}


unsigned int predictPixel(int i, int j, ImageBase& imIn)
{
	unsigned int left = imIn[i][j-1];
	unsigned int up = imIn[i-1][j];	
	unsigned int upLeft = imIn[i-1][j-1];

	return (left + up + upLeft) / 3;
}

//fonction utilisé lors de debug
 unsigned int InvertedMSB( unsigned int k)
{
	int mask = (k & 128);
	if(mask != 0){
		k = k - 128;
	}
	else{
		k = k + 128;
	}
	return k;
	
}

unsigned int InvertedMaskMSB( unsigned int k)
{	
	unsigned mask = (1 << 7);
	unsigned int res;
	
	if(k & (mask)){
		mask = ~mask;
		res = k & mask;
		
	}
	else
	{
		res = k | mask;
	}
	return res;
	
}

void reconstructImage( ImageBase& imIn, ImageBase& imOut)
{

	for(int i=0; i<imIn.getHeight(); i++)
		for(int j=0; j<imIn.getWidth(); j++)
		{
			if((i == 0 || j == 0)){
				imOut[i][j] = imIn[i][j];
			}
		}

	

	for(int i=1; i< imIn.getHeight(); i++){
		for(int j=1; j< imIn.getWidth(); j++){

			unsigned int p_i = imIn[i][j];
			unsigned int inv_p_i = InvertedMaskMSB(imIn[i][j]);
			unsigned int pred_i = predictPixel(i, j, imOut);
			int distance_pi = pred_i - p_i;
			int distance_inv_pi = pred_i - inv_p_i;
			
			
			if( (std::abs(distance_pi) < (std::abs(distance_inv_pi)))  ){
				imOut[i][j] = p_i;
			}
			else
			{
				imOut[i][j] = inv_p_i;
			}

		}
	}
}

void pretraitement(ImageBase& imIn, ImageBase& imOut)
{


	for (int i = 0; i < imIn.getHeight(); i++)
	{
		for (int j = 0; j < imIn.getWidth(); j++)
		{

			unsigned int p_i = imIn[i][j];
			unsigned int inv_p_i = InvertedMaskMSB(imIn[i][j]);
			unsigned int pred_i = predictPixel(i, j, imOut);
			int distance_pi = pred_i - p_i;
			int distance_inv_pi = pred_i - inv_p_i;

			if( std::abs(distance_pi) >= abs(distance_inv_pi) ){
				if(p_i < 128){
					imOut[i][j] = pred_i - 63;
				}
				else
				{
					imOut[i][j] = pred_i + 63;
				}
			}
			else
			{
				imOut[i][j] = p_i;
			}
		}
		
	}
	
}



int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	
  
	if (argc != 2) 
	{
		printf("Usage: ImageIn.pgm  \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	
	
	
	
	//ImageBase imIn;
	ImageBase imIn;
	imIn.load(cNomImgLue);
	
	ImageBase ImRandom(				imIn.getHeight(), imIn.getWidth(), imIn.getColor()); //#  Images aléatoires
	ImageBase ImRandom2(			imIn.getHeight(), imIn.getWidth(), imIn.getColor()); //#

	ImageBase ImChiffree(			imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image chiffrée
	ImageBase ImChiffree2(			imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image chifrée avec une autre clé
	ImageBase ImChiffree3(			imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image chiffrée pour la partie reconstruction
	ImageBase ImDechiffree(			imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image déchiffrée

	ImageBase ImInserted(			imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image apres insertion d'un message LSB
	ImageBase ImInserted2(			imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image apres insertion d'un message MSB
	ImageBase ImInsertedDechiffree(	imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image déchiffrée apres insertion
	ImageBase ImReconstructed(		imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image reconstruite avec prédiction
	ImageBase ImPretraitement(		imIn.getHeight(), imIn.getWidth(), imIn.getColor());// Image avec source prétraité

	ImageBase ImBinaryPlane(		imIn.getWidth(), imIn.getWidth(), imIn.getColor());// Image d'un plan binaire


	// Chiffrement Dechiffrement 
	getSequence(255, imIn.getHeight(), imIn.getHeight(), imIn.getColor(), ImRandom);
	XorCrypt(imIn, ImRandom, ImChiffree);
	XorCrypt(ImChiffree, ImRandom, ImDechiffree);

	// Chiffrement avec une autre clé
	getSequence(38, imIn.getHeight(), imIn.getHeight(), imIn.getColor(), ImRandom);
	XorCrypt(imIn, ImRandom, ImChiffree2);

	//plans binaires k[0-7]
	planBinaire(1, ImChiffree, ImBinaryPlane);

	//Pretraitement de l'image avant insertion, a commenté pour essayer sans prétraitement
	pretraitement(imIn, ImPretraitement);
	XorCrypt(ImPretraitement, ImRandom, ImChiffree3);

	//Pretraitement de l'image avant insertion, a décommenté pour essayer sans prétraitement
	//XorCrypt(imIn, ImRandom, ImChiffree);

	//k[0-7]
	//Insertion dans l'image source (plan LSB)
	int k = 0;
	getSequence(38, imIn.getHeight(), imIn.getHeight(), ImRandom2	);
	insertMessage(imIn, ImRandom2, ImInserted, k);

	//insertion dans image chiffree
	k = 7;
	insertMessage(ImChiffree3, ImRandom2, ImInserted2, k);
	XorCrypt(ImInserted2, ImRandom, ImInsertedDechiffree);
	reconstructImage(ImInsertedDechiffree, ImReconstructed);

	ImChiffree.save("ImageChiffree.pgm");
	ImDechiffree.save("ImageDechiffree.pgm");
	ImBinaryPlane.save("PlanBinaire.ppm");
	ImInserted.save("ImageInsertionLSB.pgm");
	ImInserted2.save("ImageInsertionChiffree.pgm");
	ImInserted2.HistoSave(ImInserted2.Histo(), "ImageMarquee.dat");
	ImInsertedDechiffree.save("ImageInsertionDechifree.pgm");
	ImReconstructed.save("ImageReconstrctuionPredictive.pgm");
	// histogramme a affiché avec gnuplot de l'image source et chiffré
	imIn.HistoSave(imIn.Histo(), "ImageClaire.dat");
	ImChiffree.HistoSave(ImChiffree.Histo(), "ImageChirffree .dat");

	std::cout <<  "PSNR des deux images : " << calcPSNR(ImChiffree, ImChiffree2) << std::endl;
	std::cout <<  "PSNR des images source et déchiffée : " << calcPSNR(imIn, ImDechiffree) << std::endl;
	std::cout << Entropy(imIn) << "  " << Entropy(ImChiffree) << std::endl;
	std::cout <<  "PSNR apres insertion au bit de rang  : " << k+1  << "\n --> " << calcPSNR(imIn, ImInserted2) << std::endl;
	std::cout <<  "PSNR apres reconstruction  : "  << "\n --> " << calcPSNR(imIn, ImReconstructed) << std::endl;

	return 0;
}
