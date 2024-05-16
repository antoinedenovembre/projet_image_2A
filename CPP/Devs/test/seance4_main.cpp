#include <iostream>

#include "ImageNdg.h"
#include "ImageCouleur.h"
#include "ImageDouble.h"

	// contours via usage du vecteur gradient

	void main(void) 
	{
		try 
		{

			std::string name_img("cellules.bmp");
			CImageNdg img(name_img);

			CImageDouble imgD(img, "normalise");
			CImageDouble gradient = imgD.vecteurGradient("norme");
			CImageDouble angle = imgD.vecteurGradient("angle");

			CImageNdg test = gradient.toNdg("expansion");
			test.sauvegarde("normeGradient");

			CImageNdg test2 = angle.toNdg("expansion");
			test2.sauvegarde("angleGradient");

			CImageNdg seuil = test.seuillage("otsu");
			seuil.sauvegarde("seuilNormeGradientOtsu"); // contours trop épais et fausse détection (même si faible)

			// voir quels voisins regarder équivalent V8 

			CImageNdg maxiLocaux2(imgD.lireHauteur(), imgD.lireLargeur(), 0); // 0 = noir
			maxiLocaux2.choixPalette("binaire");

			for (int i = 1; i < gradient.lireHauteur() - 1; i++)
				for (int j = 1; j < gradient.lireLargeur() - 1; j++)
				{


					// secteur 1
					if (((angle(i, j) >= 0) && (angle(i, j) <= 22.5)) || ((angle(i, j) <= 0) && (angle(i, j) >= -22.5)))
						if ((gradient(i, j) >= gradient(i - 1, j)) && (gradient(i, j) >= gradient(i + 1, j)))
							maxiLocaux2(i, j) = 1;
					if (((angle(i, j) >= 157.5) && (angle(i, j) <= 180)) || ((angle(i, j) <= -157.5) && (angle(i, j) >= -180)))
						if ((gradient(i, j) >= gradient(i - 1, j)) && (gradient(i, j) >= gradient(i + 1, j)))
							maxiLocaux2(i, j) = 1;


					// secteur 2
					if (((angle(i, j) >= 67.5)) && ((angle(i, j) <= 112.5)))
						if ((gradient(i, j) >= gradient(i, j - 1)) && (gradient(i, j) >= gradient(i, j + 1)))
							maxiLocaux2(i, j) = 2;
					if (((angle(i, j) <= -67.5)) && ((angle(i, j) >= -112.5)))
						if ((gradient(i, j) >= gradient(i, j - 1)) && (gradient(i, j) >= gradient(i, j + 1)))
							maxiLocaux2(i, j) = 2;


					// secteur 3
					if (((angle(i, j) > 22.5)) && ((angle(i, j) < 67.5)))
						if ((gradient(i, j) >= gradient(i - 1, j - 1)) && (gradient(i, j) >= gradient(i + 1, j + 1)))
							maxiLocaux2(i, j) = 3;
					if (((angle(i, j) < -112.5)) && ((angle(i, j) > -157.5)))
						if ((gradient(i, j) >= gradient(i - 1, j - 1)) && (gradient(i, j) >= gradient(i + 1, j + 1)))
							maxiLocaux2(i, j) = 3;


					// secteur 4
					if (((angle(i, j) > 112.5)) && ((angle(i, j) < 157.5)))
						if ((gradient(i, j) >= gradient(i - 1, j + 1)) && (gradient(i, j) >= gradient(i + 1, j - 1)))
							maxiLocaux2(i, j) = 5;
					if (((angle(i, j) < -22.5)) && ((angle(i, j) > -67.5)))
						if ((gradient(i, j) >= gradient(i - 1, j + 1)) && (gradient(i, j) >= gradient(i + 1, j - 1)))
							maxiLocaux2(i, j) = 5;
				}

			maxiLocaux2.sauvegarde("maxNormeGradientDirDiag"); // strict ? Seuillage par hystérésis pour affiner, puis resterait à combler les "trous"

			// combinaison  ET entre images binaires
			CImageNdg seuilDirect = maxiLocaux2.seuillage("manuel", 1, 255); // gestion des directions...

			CImageNdg essai = seuilDirect.operation(seuil, "et");
			essai.sauvegarde("sansHysteresis");

			// visualisation via masquage
			CImageCouleur visu(img, essai, 255, 255, 0);
			visu.sauvegarde("contoursAffines");

		}
		catch (const std::string& chaine) 
		{
			std::cerr << chaine << std::endl;
		}
			
	}


	// points d'intérêt Harris

	void main(void) 
	{
		try {
			// détecteurs coins Harris
			std::string name_img("p1.bmp");
			CImageNdg img(name_img);

			int taille = 3;
			double sigma = 1;

			CImageDouble out(img.lireHauteur(), img.lireLargeur());
			out.ecrireNom(img.lireNom() + "Ha");

			// Sobel lignes et colonnes
			CImageDouble Ix(img.lireHauteur() + 2, img.lireLargeur() + 2);
			CImageDouble Iy(img.lireHauteur() + 2, img.lireLargeur() + 2);
			CImageDouble Ixy(img.lireHauteur() + 2, img.lireLargeur() + 2);

			// pour éviter tests sur les bords
			CImageDouble agrandie(img.lireHauteur() + 2, img.lireLargeur() + 2);

			// gestion des bords et des coins
			int pix;
			agrandie(0, 0) = img(0, 0);
			agrandie(0, agrandie.lireLargeur() - 1) = img(0, img.lireLargeur() - 1);
			for (pix = 1; pix < agrandie.lireLargeur() - 1; pix++) {
				agrandie(0, pix) = img(0, pix - 1);
				agrandie(agrandie.lireHauteur() - 1, pix) = img(img.lireHauteur() - 1, pix - 1);
			}
			agrandie(agrandie.lireHauteur() - 1, 0) = img(img.lireHauteur() - 1, 0);
			agrandie(agrandie.lireHauteur() - 1, agrandie.lireLargeur() - 1) = img(img.lireHauteur() - 1, img.lireLargeur() - 1);
			for (pix = 1; pix < agrandie.lireHauteur() - 1; pix++) {
				agrandie(pix, 0) = img(pix - 1, 0);
				agrandie(pix, agrandie.lireLargeur() - 1) = img(pix - 1, img.lireLargeur() - 1);
			}

			// gestion du coeur
			for (int i = 0; i < img.lireHauteur(); i++)
				for (int j = 0; j < img.lireLargeur(); j++) {
					agrandie(i + 1, j + 1) = img(i, j);
				}

			// passage des noyaux

			for (int i = 1; i < agrandie.lireHauteur() - 1; i++)
				for (int j = 1; j < agrandie.lireLargeur() - 1; j++)
				{
					Ix(i, j) = agrandie(i + 1, j) - agrandie(i - 1, j);
					Iy(i, j) = agrandie(i, j + 1) - agrandie(i, j - 1);
				}

			for (int i = 0; i < Ix.lireNbPixels(); i++)
			{
				Ixy(i) = Ix(i) * Iy(i);
				Ix(i) *= Ix(i);
				Iy(i) *= Iy(i);
			}

			Ix = Ix.filtrage("gaussien", taille, sigma);
			Iy = Iy.filtrage("gaussien", taille, sigma);
			Ixy = Ixy.filtrage("gaussien", taille, sigma);

			double k = 0.01;

			double Rmin = DBL_MAX, Rmax = DBL_MIN;
			CImageDouble R(img.lireHauteur() + 2, img.lireLargeur() + 2);

			for (int i = 1; i < agrandie.lireHauteur() - 1; i++)
				for (int j = 1; j < agrandie.lireLargeur() - 1; j++)
				{
					double A = Ix(i, j);
					double B = Ixy(i, j);
					double C = Iy(i, j);
					double det = A * C - B * B;
					double trace = A + C;
					R(i, j) = det - k * (trace * trace);
					if (R(i, j) > Rmax)
						Rmax = R(i, j);
					if (R(i, j) < Rmin)
						Rmin = R(i, j);
				}

			out.ecrireMin(Rmin);
			out.ecrireMax(Rmax);

			// recherche maxima locaux 
			for (int i = 1; i < agrandie.lireHauteur() - 1; i++)
				for (int j = 1; j < agrandie.lireLargeur() - 1; j++)
					if ((R(i, j) > R(i - 1, j - 1)) && (R(i, j) > R(i - 1, j)) && (R(i, j) > R(i - 1, j + 1)) && (R(i, j) > R(i, j - 1)) && (R(i, j) > R(i, j + 1)) && (R(i, j) > R(i + 1, j - 1)) && (R(i, j) > R(i + 1, j)) && (R(i, j) > R(i + 1, j + 1)))
						out(i - 1, j - 1) = R(i, j);

			// seuillage à 10%
			CImageNdg coins(img.lireHauteur(), img.lireLargeur(), 0);
			for (int i = 0; i < img.lireNbPixels(); i++)
				if (out(i) >= 0.1 * Rmax)
					coins(i) = 1;


			// visualisation via masquage
			CImageCouleur visu(img, coins, 255, 0, 0);
			visu.sauvegarde("coins");
		}
		catch (const std::string& chaine) 
		{
			std::cerr << chaine << std::endl;
		}

	}