#include <cmath>
#include <iostream>
#include <vector>

#include "ImageClasse.hpp"
#include "ImageCouleur.hpp"
#include "ImageDouble.hpp"
#include "ImageNdg.hpp"

int main(void)
{
    try
    {
        CImageNdg cells{"img/amas.bmp"};

        cells = cells.seuillage();

		cells.sauvegarde("seuillage");
		
		CImageClasse cellsClasse{cells, "V8"};

        CImageClasse voronoi = cellsClasse.voronoi();

        voronoi.sauvegarde("voronoi");

        /*
		CImageNdg cells{"img/cellules.bmp"};

        CImageClasse cellsClasse{cells.seuillage(), "V8"};

        cellsClasse.sauvegarde("classeCells");

        std::vector<SIGNATURE_Forme> sigs = cellsClasse.sigComposantesConnexes();

        cellsClasse.circleInEachComponent(sigs);

        cellsClasse.sauvegarde("classeCellsCircles");
        */
    }
    catch (const std::string & chaine)
    {
        std::cerr << chaine << std::endl;
    }
}