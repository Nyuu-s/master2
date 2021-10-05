// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"




int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite1[250], cNomImgEcrite2[250];
  int nH, nW, nTaille, nR, nG, nB;
  
  if (argc != 4) 
     {
       printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite1);
   sscanf (argv[3],"%s",cNomImgEcrite2);
   

   OCTET *ImgIn, *ImgOut1, *ImgOut2;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut1, OCTET, nTaille3);
   allocation_tableau(ImgOut2, OCTET, nTaille3);
   int CCR1, CCG1, CCB1, CCR2, CCG2, CCB2; // Class Coulor Red 1 etc....
   CCR1 = 73;
   CCG1 = 22;
   CCB1 = 52;

   CCR2 = 47;
   CCG2 = 55;
   CCB2 = 13;

  int moyCR1 = CCR1; 
  int moyCG1 = CCG1;
  int moyCB1 = CCB1;

  int moyCR2 = CCR2; 
  int moyCG2 = CCG2;
  int moyCB2 = CCB2;
  int n, m = 0; 

   char C1[nTaille3], C2[nTaille3]; // class for 2-means

   for (int i=0; i < nTaille3; i+=3)
     {

       nR = ImgIn[i];
       nG = ImgIn[i+1];
       nB = ImgIn[i+2];
      
      int d1 = sqrt( ((nR - CCR1) * (nR - CCR1)) + ( (nG - CCG1)*(nG - CCG1) ) + ( (nB - CCB1) * (nB - CCB1)) );

      int d2 = sqrt( ((nR - CCR2) * (nR - CCR2)) + ( (nG - CCG2)*(nG - CCG2) ) + ( (nB - CCB2) * (nB - CCB2)) );


      if(d1 < d2)
      {
        C1[i]   = CCR1;
        C1[i+1] = CCG1;
        C1[i+2] = CCB1;
        n++;
        moyCR1 += nR/n;
        moyCG1 += nG/n;
        moyCB1 += nB/n;
       
        ImgOut1[i]   = CCR1;
        ImgOut1[i+1] = CCG1;
        ImgOut1[i+2] = CCB1;

        ImgOut2[i]   = moyCR1;
        ImgOut2[i+1] = moyCG1;
        ImgOut2[i+2] = moyCB1;
      }
      else
      {
        ImgOut1[i]   = CCR2;
        ImgOut1[i+1] = CCG2;
        ImgOut1[i+2] = CCB2;

        C2[i]   = CCR2;
        C2[i+1] = CCG2;
        C2[i+2] = CCB2;

        m++;
        moyCR2 += nR / m ;
        moyCG2 += nG / m;
        moyCB2 += nB / m;

        ImgOut2[i]= moyCR2;
        ImgOut2[i+1] = moyCG2;
        ImgOut2[i+2] = moyCB2;       
      }

      //repeat until convergeance
          

  

     }




   ecrire_image_ppm(cNomImgEcrite1, ImgOut1,  nH, nW);
   ecrire_image_ppm(cNomImgEcrite2, ImgOut2,  nH, nW);
   free(ImgIn);
   return 1;
}



