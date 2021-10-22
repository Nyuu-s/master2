#include "ImageBase.h"
#include <stdio.h>
#include<iostream>
<<<<<<< HEAD
#include <cstdlib>
=======
>>>>>>> 4c887c5cfe9d09b32b02873555bcf1ebb11f67b8
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

int getSequence(unsigned int key, int h, int w, ImageBase &output){
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

void insertMessage(ImageBase& imIn,ImageBase& imMSG,  ImageBase& imOut, int k){
	if(k > 7){
		k = 7;
	}
	
	for (int i = 0; i < imIn.getHeight(); i++)
	{
		for (int j = 0; j < imIn.getWidth(); j++)
		{
			if(!(i == 0 || j == 0)){ // for xor image

				
				int b = pow(2,k);
				int c = 255 - b;
				int a = imMSG[i][j] & b;
				switch (k)
				{
				case 0:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & 1) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + 1;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}
					break;
				case 1:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}
					break;
				case 2:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}
					break;
				case 3:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & b;
						}
					break;
				case 4:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}
					break;
				case 5:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}
					break;
				case 6:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}
					break;
				default:
						
																//if bit from message == 1 	
						if(a == 1){
							if((imIn[i][j] & b) != 1){ 			// check if current lsb is already 1 else add 1 to number
								imOut[i][j] = imIn[i][j] + b;
							}
							else{
								imOut[i][j] = imIn[i][j];
							}
						}
						else									//if bit from message == 0 take pixel value & 254 to force lsb to be 0	
						{
							imOut[i][j] = imIn[i][j] & c;
						}

					break;
				}
			}
			else
			{
				imOut[i][j] = imIn[i][j];
			}

				
		}
		
		/* code */
	}
	
}

<<<<<<< HEAD
unsigned int predictPixel(int i, int j, ImageBase& imIn)
{
	unsigned int left = imIn[i][j-1];
	unsigned int up = imIn[i-1][j];	
	unsigned int upLeft = imIn[i-1][j-1];

	return (left + up + upLeft) / 3;
}

 unsigned int InvertedMSB( unsigned int k)
{
	int b = (k & 128);
	if(b != 0){
		k = k - 128;
	}
	else{
		k = k + 128;
	}
	
	
	
	return k;
	
}

unsigned int InvertedmaskMSB( unsigned int k)
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
			//if((i == 0 || j == 0)){
				imOut[i][j] = imIn[i][j];
			//}
		}

	imOut.save("TESTINTERMEDIAIRE");

	for(int i=1; i< imIn.getHeight(); i++){
		for(int j=1; j< imIn.getWidth(); j++){

			unsigned int p_i = imIn[i][j];
			unsigned int inv_p_i = InvertedmaskMSB(imIn[i][j]);
			unsigned int pred_i = predictPixel(i, j, imOut);
			int a = pred_i - p_i;
			int b = pred_i - inv_p_i;
			std::cout << pred_i << " " << inv_p_i << " " << p_i << std::endl;
			
			if( (std::abs(a) < (std::abs(b)))  ){
				imOut[i][j] = p_i;
			}
			else
			{
				imOut[i][j] = inv_p_i;
			}

		}
	}
}


=======
>>>>>>> 4c887c5cfe9d09b32b02873555bcf1ebb11f67b8
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
	planBinaire(1, ImOut, imgBinary);
	imgBinary.save("PlanBinaire.ppm");


	ImageBase ImInserted(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	ImageBase ImRand2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	ImageBase ImInsertedDechiffree(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
<<<<<<< HEAD
	ImageBase ImInsertedDechiffree2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());

	XorCrypt(imIn, ImRand, ImOut);

	getSequence(38, imIn.getHeight(), imIn.getHeight(), ImRand2	);
=======
	getSequence(38, imIn.getHeight(), imIn.getHeight(), 	);
>>>>>>> 4c887c5cfe9d09b32b02873555bcf1ebb11f67b8
	int k = 7; //bits range from 0 to 7, k will be set a 7 if it is greater than 7;
	insertMessage(ImOut, ImRand2, ImInserted, k);
	ImInserted.save("testInsertChiffree");
	ImInserted.HistoSave(ImInserted.Histo(), "ImageMarquee.dat");

	std::cout <<  "PSNR apres insertion au bit de rang  : " << k+1  << "\n --> " << calcPSNR(imIn, ImInserted) << std::endl;

<<<<<<< HEAD

	


	XorCrypt(ImInserted, ImRand, ImInsertedDechiffree);


	ImInsertedDechiffree.save("imageMarqueeDechifree.pgm");

	reconstructImage(ImInsertedDechiffree, ImInsertedDechiffree2);

	ImInsertedDechiffree2.save("reconstrctuionPreictive.pgm");

=======
	XorCrypt(ImInserted, ImRand, ImInsertedDechiffree);
	

	ImInsertedDechiffree.save("imageMarqueeDechifree.pgm");

>>>>>>> 4c887c5cfe9d09b32b02873555bcf1ebb11f67b8
	return 0;
}
