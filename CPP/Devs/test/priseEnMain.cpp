#include <iostream>
#include <cmath>

#include "ImageNdg.h"
#include "ImageCouleur.h"
#include "ImageDouble.h"



int main(void)
{
	int choix = 10;

	switch (choix)
	{
	case 1:                                                                                   //pour une image en NDG
	{// Ndg
		try {
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//1.1  Ok

			//1.2
			CImageNdg img("chro.bmp");  //lecture image via constructeur par copie avec nom du fichier
			//////////////////////////

			//1.3
			unsigned char valeur = img(0, 0); //acces au pixel 0,0
			cout << static_cast<int>(valeur) << endl; //acces au pixel 0,0

			//1.4
			img.choixPalette("rouge"); //choix de la palette rouge
			img.choixPalette("verte"); //choix de la palette verte
			img.choixPalette("bleue"); //choix de la palette bleue
			img.choixPalette("binaire"); //choix de la palette binaire
			img.sauvegarde("binaire");
			img.ecrireNom("imagebinairemacbeth.bmp");
			//img.choixPalette("rouge").sauvegarde("macbethR.bmp");

			//1.5

			CImageNdg img2("macbeth.bmp");

			img2.transformation("complement").seuillage("otsu");//transformation complement, seuillage otsu, sauvegarde
			img2.sauvegarde("macbethotsu.bmp");
			

			//1.6  Ok

			//1.7
			MOMENTS moments = img.signatures(); //calcul des moments
			cout << "Moyenne : " << moments.moyenneNdg << endl; //affichage moyenne
			cout << "Ecart type : " << moments.ecartTypeNdg << endl; //affichage ecart type
			cout << "Mediane : " << moments.medianeNdg << endl; //affichage mediane
			//surcharge=optimisation

		   //1.8
			img.transformation("complement").seuillage("moyenne").sauvegarde("macbethMoyenne.bmp"); //transformation complement, seuillage moyenne, sauvegarde

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			/*
			CImageNdg img("chro.bmp");

			//img.choixPalette("verte");

			//int last = img.lireNbPixels() - 1;
			//int haut = img.lireHauteur() - 1;
			//int larg = img.lireLargeur() - 1;
			//std::cout << (int)img(last) << " " << (int)img(haut, larg) << std::endl;

			//img.sauvegarde("vert");

			std::cout << img.signatures().ecartTypeNdg << std::endl;

			//img.transformation("complement").seuillage("otsu").sauvegarde();
			img.seuillage("mediane").sauvegarde();

			std::vector<unsigned long> h = img.histogramme(true);
			*/



		}
		catch (const std::string& chaine) { // si erreur lecture image
			std::cerr << chaine << std::endl;
		}
		system("pause");
	}
	break;


	case 2:                                                                                    //pour une image en couleur
	{ // Couleur
		try
		{
			//2.1

			//cas d'une image un plan: les 3 plans sont identiques et possede la meme valeur pour un pixel

			/*
			CImageCouleur img("macbeth.bmp");
			cout << (int)img(0, 0)[0];  //le [0] permet acces au plan rouge
			cout << (int)img(0, 0)[1];  //le [1] permet acces au plan vert
			cout << (int)img(0, 0)[2];  //le [2] permet acces au plan bleu
			*/


			//2.2
			/*
			img.plan(0).sauvegarde("imageplanrouge.bmp"); //sauvegarde du plan rouge
			img.plan(1).sauvegarde("imageplanvert.bmp"); //sauvegarde du plan vert
			img.plan(2).sauvegarde("imageplanbleu.bmp"); //sauvegarde du plan bleu

			//img.plan(3).sauvegarde("lum"); //sauvegarde a un tiers, un tiers , un tiers
			//img.plan(3, 0.2126, 0.7152, 0.0722).sauvegarde("lum2");  // 0 plan rouge, 1 plan verre, 2 plan bleu, 3 plan luminance


			//2.3
			img.conversion().plan(0).sauvegarde(); //conversion en hsv et on prend le plan h


			//2.4
			CImageCouleur img2("macbeth.bmp");
			img2.transformation("expansion").sauvegarde("macbethexpansion.bmp"); //transformation expansion, sauvegarde
			img2.transformation("egalisation").sauvegarde("macbethegalisation.bmp"); //transformation egalisation, sauvegarde

			img2.conversion().transformation("expansion").sauvegarde("macbethexpansionhsv.bmp"); //conversion hsv, transformation expansion, sauvegarde
			*/

			//Seance 3

			//    1.     Prise en main "ImageDouble"
			//    premier point : chargement image trombinoscope

			CImageCouleur img("trombinoscope.bmp");
			auto imgndg = img.conversion().plan(3).seuillage();  //conversion hsv, on prend le plan de saturation, on seuil otsu, on sauvegarde
			imgndg.sauvegarde("trombiplandelum");

			//    second point: chargement via le constructeur 

			CImageNdg imgndg2;
			CImageDouble imgdouble(imgndg, "normalise");
			imgndg2 = imgdouble.toNdg("default");
			imgndg2.sauvegarde("exo2");




			//chaque pixel porte l'écart type local de son voisinage

		}
		catch (const std::string& chaine)
		{ // si erreur lecture image
			std::cerr << chaine << std::endl;
		}

		system("pause");
	}
	break;


	case 3:
	{                                                                                          //pour un lot d'images couleur et ndg
		int nbImage = 5;
		for (int i = 1; i <= nbImage; i++)
		{

			std::string RGB("objet" + std::to_string(i) + ".bmp");
			std::string BW("objet" + std::to_string(i) + "GT.bmp");

			CImageCouleur img(RGB);
			CImageNdg mask(BW);
 
			auto imgsat = img.conversion().plan(1);
			imgsat=imgsat.seuillage("otsu");  //conversion hsv, on prend le plan de saturation, on seuil otsu, on sauvegarde
			imgsat.sauvegarde("objet" + std::to_string(i) + "saturationotsu.bmp");



			for (int i = 0; i < 4; i++)
			{
				CImageNdg mask2 = mask.seuillage("otsu");
				mask2.sauvegarde("objet" + std::to_string(i) + "otsu.bmp");

				bool isBinary = true;
				for (int i = 0; i < mask2.lireNbPixels(); i++)
				{
					if (mask(i) != 0 && mask(i) != 255)
					{
						isBinary = false;
					}

					cout << "isBinary: " << isBinary << endl;
				}
			}

				
			//mask= mask.seuillage("otsu");

			//mask.seuillage("manuel", 1, 1).sauvegarde();
			
			
			
			double card_numerateur;
			double card_denominateur;
			double card;

			card_numerateur = imgsat.operation(mask,"et").compterPixelsNonNuls();
			card_denominateur= mask.compterPixelsNonNuls();
			card= card_numerateur / card_denominateur;
			

			cout<< "indicateur de performance image " <<i<< ":" <<  card << endl;
			
		

			//img.sauvegarde();
			//mask.sauvegarde();



			//créer une image du plan de saturation seuillée par otsu
			//récupérer une image vérité terrain
		}
	}
	break;

	case 4:
	{

		CImageCouleur img("text1.bmp");
		double ecartType = 0.0;
		double moyenne = 0.0;

		int N = 15;
		int nbbord = N / 2;

		for (int i = 0; i < img.lireHauteur(); i++)
			for (int j = 0; i < img.lireLargeur(); j++)
			{
				//gestion des bords
				/*
				int dk =max(0, i - nbBords);
				int fk = min(i+nbBords, img.lireHauteur() - 1);
				int dl = max(0, j - nbBords);
				int fl= min(j+nbBords, img.lireLargeur() - 1);
				*/

				//boucles à remplacer avec usage des images intégrales
				double somme = 0, somme2 = 0;
				double nb = 0;

			}
	}
	break;

	case 5:
	{
		//Image intégrale et premiers moments statistiques

		CImageNdg img("text1.bmp");
		MOMENTS mmt = img.signatures();

		std::cout << mmt.ecartTypeNdg << std::endl;
		std::cout << mmt.moyenneNdg << std::endl;

		CImageDouble img2(img, "integrale1");
		CImageDouble img3(img, "integrale2");


		float moyenne = (float)(img2(img2.lireNbPixels() - 1) / float(img2.lireNbPixels()));
		float ecartType = (float)sqrt(img3(img3.lireNbPixels() - 1) / float(img3.lireNbPixels()) - moyenne * moyenne);

		std::cout << moyenne << std::endl;
		std::cout << ecartType << std::endl;

		//ecarts-types locaux et images intégrales

	}
	break;


	case 6:
	{
		// Créez une instance de CImageNdg avec votre image
		CImageNdg image("objet4GT.bmp");

		// Calculez l'histogramme sans enregistrer dans un fichier CSV
		std::vector<unsigned long> histogramData = image.histogramme(false);

		// Affichez l'histogramme dans la console
		for (int i = 0; i < histogramData.size(); ++i) 
		{
			std::cout << "Niveau de gris " << i << ": " << histogramData[i] << std::endl;
		}
	}
	break;

	case 7:
	{
		CImageNdg chro("chro.bmp");
		auto img1=chro.seuillage("otsu");
		img1.sauvegarde("chro_seuillage.bmp");

		
		//auto img2 = img1.morphologie("erosion", "V4");
		//img2.sauvegarde("chro_erosion.bmp");

		//auto img3 = img2.operation(img1, "-");
		//img3.choixPalette("grise").transformation("expansion");
		

		//img3.sauvegarde("partie1.bmp");

	}
	break;


	case 8:
	{
		CImageCouleur img("trombinoscope.bmp");


		auto img1 = img.conversion();
		img1.sauvegarde("HSV.bmp");

		auto img2 = img1.plan(0).seuillage("manuel", 0, 35);//on modifie les valeurs de seuil donnés dans l'énoncé pour rentrer sur [0,255]
		img2.sauvegarde("HSV-H.bmp");

		auto img3=img1.plan(1).seuillage("manuel", 59, 173);//on modifie les valeurs de seuil donnés dans l'énoncé pour rentrer sur [0,255]
		img3.sauvegarde("HSV-S.bmp");

		auto img4=img1.plan(2).seuillage("manuel", 80, 199);//on modifie les valeurs de seuil donnés dans l'énoncé pour rentrer sur [0,255]
		img4.sauvegarde("HSV-Vsansseuillage.bmp");

		//dilatation puis erosion pour supprimer les petits trous

		//on reconstruit l'image hsv à partir des 3 plans, dont les 2 premiers sont seuillés
		CImageNdg imgresultat = img3.operation(img2, "et");
		imgresultat = imgresultat.operation(img2, "et");
		imgresultat=imgresultat.operation(img4, "et");

		//dilatation puis erosion pour supprimer les petits trous
		imgresultat=imgresultat.morphologie("dilatation", "V8");
		imgresultat.sauvegarde("apresdilatation.bmp");
		imgresultat=imgresultat.morphologie("erosion", "V8");
		imgresultat.sauvegarde("apreserosion.bmp");
		imgresultat.sauvegarde("HSV-peau.bmp");
		//resultat: certaine parties droite du visage sont coupées et surtout, ne fonctionne pas pour les peaux noires

	}

	case 9:
	{
		CImageNdg imgacquise("imacquise.bmp");
		CImageNdg imgveriteterrain("imacquise2.bmp");
		double resultatdeHamming = 0;

		auto img1 = imgacquise.seuillage("otsu");
		img1.sauvegarde("imgacquiseotsu.bmp");

		auto img2 = imgveriteterrain.seuillage("otsu");
		img2.sauvegarde("imgveriteotsu.bmp");

		resultatdeHamming = img1.Hammingdistance(img2);
		
		cout << "Le resultat de la distance de Hamming est: " << resultatdeHamming << endl;

	}

	case 10:
	{
		CImageNdg img("imacquise.bmp");
		auto img1 = img.seuillage("otsu");

		CImageNdg img2("imacquise.bmp");
		auto img3 = img2.seuillage("otsu");

		double score;

		score = img1.score(img3,"iou");
		
		cout << "Le score de l'indice de iou est: " << score << endl;
	}

	}
	
}
