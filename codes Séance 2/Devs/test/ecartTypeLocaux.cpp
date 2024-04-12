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

		// seuillage NG
		CImageNdg BW = img.seuillage("otsu");
		BW.sauvegarde("seuilNG");

		// écarts-types locaux sans images intégrales
		CImageNdg ecloc(img.lireHauteur(), img.lireLargeur(), 0);

		time_t avant, apres;

		time(&avant);

		int N = 15;
		int nbBords = N / 2;

		for (int i = 0; i < img.lireHauteur(); i++)
			for (int j = 0; j < img.lireLargeur(); j++) 
			{
				// gestion des bords
				int dk = std::max(0, i - nbBords);
				int fk = std::min(i + nbBords, img.lireHauteur() - 1);
				int dl = std::max(0, j - nbBords);
				int fl = std::min(j + nbBords, img.lireLargeur() - 1);

				/* boucles à remplacer avec usage des images intégrales */
				double somme = 0, somme2 = 0;
				double nb = 0;
				for (int k = dk; k <= fk; k++)
					for (int l = dl; l <= fl; l++) 
					{
						nb += 1;
						somme += (double)img(k, l);
						somme2 += (double)img(k, l) * (double)img(k, l);
					}
				somme /= nb;
				ecloc(i, j) = (int)(sqrt(somme2 / nb - (somme * somme)));
			}

		time(&apres);
		double difference = difftime(apres, avant);
		printf("temps mis calculs directs: %.2lf secondes.\n", difference);

		ecloc.transformation("expansion").sauvegarde("sigLoc");
		CImageNdg seuil2 = ecloc.seuillage();
		seuil2.sauvegarde("segmentationv1");
	}
	catch (const std::string& chaine) { // si erreur lecture image
		std::cerr << chaine << std::endl;
	}
}