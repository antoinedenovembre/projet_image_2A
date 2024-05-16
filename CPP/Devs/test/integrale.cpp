#include <iostream>
#include <cmath>
#include <ctime>

#include "ImageNdg.h"
#include "ImageDouble.h"

void main(void)
{
	try
	{	
		CImageNdg img("text1.bmp"); // text2.bmp

		// moments
		
		MOMENTS mts = img.signatures();
		std::cout << "moyenne : " << mts.moyenneNdg << " ecart-type : " << mts.ecartTypeNdg << std::endl;

		CImageDouble imgIntX(img, "integrale1");
		CImageDouble imgIntX2(img, "integrale2");

		float moy = imgIntX(img.lireNbPixels() - 1) / (float)img.lireNbPixels();
		std::cout << "moyenne : " << moy << std::endl;

		float std2 = sqrt(imgIntX2(img.lireNbPixels() - 1) / (float)img.lireNbPixels() - moy*moy);
		std::cout << "std : " << std2 << std::endl;

		// exploitation écarts-type locaux et nuées dynamiques
		CImageDouble sigLoc(img.lireHauteur(), img.lireLargeur());
		time_t avant, apres;

		CImageDouble imgInt1(img, "integrale1"); //somme des niveaux de gris
		CImageDouble imgInt2(img, "integrale2"); //somme des niveaux de gris au carré

		int N = 15;
		int nbBords = N / 2;

		time(&avant);
		// images intégrales
	
		for (int i = 0; i < img.lireHauteur(); i++)
			for (int j = 0; j < img.lireLargeur(); j++) 
			{
				// définition rectangle
				int Ai = std::max(0, i - nbBords - 1);
				int Aj = std::max(0, j - nbBords - 1);
				int Bi = std::max(0, i - nbBords - 1);
				int Bj = std::min(j + nbBords, img.lireLargeur() - 1);
				int Ci = std::min(i + nbBords, img.lireHauteur() - 1);
				int Cj = std::max(0, j - nbBords - 1);
				int Di = std::min(i + nbBords, img.lireHauteur() - 1);
				int Dj = std::min(j + nbBords, img.lireLargeur() - 1);
				// calcul sigma local
				double nb = ((double)Ci - Ai)*((double)Dj - Cj);
				double sommeX = (imgInt1(Di, Dj) - imgInt1(Ci, Cj) - imgInt1(Bi, Bj) + imgInt1(Ai, Aj)) / nb;
				double sommeX2 = (imgInt2(Di, Dj) - imgInt2(Ci, Cj) - imgInt2(Bi, Bj) + imgInt2(Ai, Aj)) / nb;
				sigLoc(i, j) = sqrt(sommeX2 - sommeX*sommeX);
			}

		time(&apres);
		double difference = difftime(apres, avant);
		printf("temps mis avec images integrales : %.2lf secondes.\n", difference);

		CImageNdg conv = sigLoc.toNdg();
		conv.transformation("expansion").sauvegarde("ecTypLocaux");

		CImageNdg seuil = conv.seuillage();
		seuil.sauvegarde("segmentationv2");
	}
	catch (const std::string& chaine) { // si erreur lecture image
		std::cerr << chaine << std::endl;
	}
}