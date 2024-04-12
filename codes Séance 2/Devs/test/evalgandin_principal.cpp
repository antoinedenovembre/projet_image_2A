#include <iostream>
#include <cmath>

#include "ImageNdg.h"
#include "ImageCouleur.h"
#include "ImageDouble.h"


int main(void)
{
	int choix = 1;

	switch (choix)
	{

	//exercice 1
	case 1:
	{
		try
		{
			CImageNdg chro("chro.bmp");
			auto img1 = chro.seuillage("otsu");
			img1.sauvegarde("chro_seuillage.bmp");


			auto img2 = img1.morphologie("erosion", "V4");
			img2.sauvegarde("chro_erosion.bmp");

			auto img3 = img2.operation(img1, "-");
			img3.choixPalette("grise").transformation("expansion");


			img3.sauvegarde("partie1.bmp");

		}
		catch (const std::string& chaine)
		{ // si erreur lecture image
			std::cerr << chaine << std::endl;
		}
		system("pause");
	}
	break;

	//exercice 2
	case 2:
	{
		try
		{
			CImageCouleur img("trombinoscope.bmp");


			auto img1 = img.conversion();
			img1.sauvegarde("HSV.bmp");

			auto img2 = img1.plan(0).seuillage("manuel", 0, 35);//on modifie les valeurs de seuil donnés dans l'énoncé pour rentrer sur [0,255]
			img2.sauvegarde("HSV-H.bmp");

			auto img3 = img1.plan(1).seuillage("manuel", 59, 173);//on modifie les valeurs de seuil donnés dans l'énoncé pour rentrer sur [0,255]
			img3.sauvegarde("HSV-S.bmp");

			auto img4 = img1.plan(2).seuillage("manuel", 80, 199);//on modifie les valeurs de seuil donnés dans l'énoncé pour rentrer sur [0,255]
			img4.sauvegarde("HSV-Vsansseuillage.bmp");

			//dilatation puis erosion pour supprimer les petits trous

			//on reconstruit l'image hsv à partir des 3 plans, dont les 2 premiers sont seuillés
			CImageNdg imgresultat = img3.operation(img2, "et");
			imgresultat = imgresultat.operation(img2, "et");
			imgresultat = imgresultat.operation(img4, "et");

			//dilatation puis erosion pour supprimer les petits trous
			//imgresultat = imgresultat.morphologie("dilatation", "V8");
			//imgresultat.sauvegarde("apresdilatation.bmp");
			//imgresultat = imgresultat.morphologie("erosion", "V8");
			//imgresultat.sauvegarde("apreserosion.bmp");
			imgresultat.sauvegarde("HSV-peau2.bmp");
			//resultat: certaine parties droite du visage sont coupées et surtout, ne fonctionne pas pour les peaux noires
			
		}
		catch (const std::string& chaine)
		{ // si erreur lecture image
			std::cerr << chaine << std::endl;
		}

		system("pause");
	}
	break;







	}
}