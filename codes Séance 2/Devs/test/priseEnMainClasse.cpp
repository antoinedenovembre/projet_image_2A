#include <iostream>
#include <cmath>
#include <ctime> // pour srand

#include "ImageNdg.h"
#include "ImageCouleur.h"
#include "ImageDouble.h"
#include "ImageClasse.h" 


using namespace std;

// images segmentée

int main(void) 
{
	try
	{
		/*
		string name_img("cellules.bmp");  // image à segmenter
		CImageNdg img(name_img);
		CImageNdg bin = img.seuillage("otsu");

		CImageClasse lab(bin, "V8"); // segmentation par croissance de région
		lab.sauvegarde();

		vector<SIGNATURE_Forme> data = lab.sigComposantesConnexes(true);
		lab.affichageMoyenne(img, false).sauvegarde("gris");

		CImageClasse lab2 = lab.filtrage("taille", 150, true);
		lab2.sauvegarde("filtre_taille_2");

		srand((unsigned)time(NULL));
		for (int i = 1; i <= 20; i++)
		{
			CImageClasse ND(img,2);
			ND.sauvegarde("ND"+std::to_string(i));
			CImageCouleur aff1=ND.affichageMoyenne(img, false);
			aff1.sauvegarde("NDm"+std::to_string(i));
		}
		*/

		//CImageNdg ndgImage("fibres1.bmp");

		//CImageNdg resultHoughtransfo = ndgImage.transformeedehough(135, true);

		//resultHoughtransfo.sauvegarde();

		CImageNdg chro("cellules.bmp");
		CImageClasse chrotraitee(chro, "V8");

		std::vector<SIGNATURE_Forme> signatures = chrotraitee.sigComposantesConnexes(true);



	}

	catch (const std::string& chaine) 
	{
		std::cerr << chaine << std::endl;
	}


}