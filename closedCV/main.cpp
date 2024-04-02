#include <iostream>
#include <cmath>
#include <ctime> // pour srand
#include <vector>

#include "ImageNdg.hpp"
#include "ImageCouleur.hpp"
#include "ImageDouble.hpp"
#include "ImageClasse.hpp" // segmentation (seuillage + etiquetage ou ND) et signatures

int main(void) 
{
	try
	{
		// CImageNdg tst{"data/test/In_1.bmp"};
		CImageNdg tst{"data/test/Sc_1.bmp"};

		CImageDouble imgDoubleSeuil(tst);
		CImageNdg imgContours = imgDoubleSeuil.vecteurGradient("norme").toNdg();
		imgContours = imgContours.seuillage();

		// imgContours = imgContours.dilatation();
	
		imgContours.sauvegarde("grad.bmp");
	}
	catch (const std::string& chaine) 
	{
		std::cerr << chaine << std::endl;
	}
}