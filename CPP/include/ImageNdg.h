// ajouter _declspec(dllexport) devant tout public pour permettre à la dll d'exporter ces méthodes 
// pour qu'elles puissent être utilisées par d'autres applications ou programmes

struct dimensionespacedehough
{
	int rhoMax;
	int thetaMax;
};

/*
struct POINT_POLAIRE
{
	int rho;
	int theta;

	std::string toString() const
	{
		return "rho: " + std::to_string(rho) + "\ttheta: " + std::to_string(theta) + "\n";
	}
};
*/

//
#pragma once
                                     //ces 3 instructions permettent d'empêcher les pbs de double inclusion
#ifndef _IMAGE_NDG_
#define _IMAGE_NDG_
//


// définition classe Image Ndg format bmp
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

///// gestion format BMP indépendamment de <windows.h>

#define MAGIC_NUMBER_BMP ('B'+('M'<<8))   //calcul d'une valeur numérique pour identifier les fichier de format BMP

typedef struct 
{                                      //ensemble de statistiques descriptive d'une image
	int		minNdg;
	int		maxNdg;
	int		medianeNdg;
	float	moyenneNdg;
	float	ecartTypeNdg;
} MOMENTS;

class CImageNdg                               //classe pour une image en niveau de gris
{

	///////////////////////////////////////
	private :                                               //données membres de la classe
	///////////////////////////////////////

		int              m_iHauteur;
		int              m_iLargeur;  						 //hauteur et largeur de l'image
		bool			 m_bBinaire;	                        //image binaire ou non
		string      m_sNom;                                     //nom de l'image
		unsigned char*   m_pucPixel;							 //pointeur vers les pixels de l'image

		unsigned char*   m_pucPalette;  					 //palette de l'image

	///////////////////////////////////////
	public : 
	///////////////////////////////////////

		// constructeurs
		_declspec(dllexport) CImageNdg(); // par défaut
		_declspec(dllexport) CImageNdg(int hauteur, int largeur, int val=-1); // si -1 alors non pixels non initialisés
		_declspec(dllexport) CImageNdg(const string nom); // fichier en entrée
		_declspec(dllexport) CImageNdg(const CImageNdg& im); // image en entrée, par copie référence d'une image

		// destructeur
		_declspec(dllexport) ~CImageNdg(); 

		// sauvegarde au format bmp
		_declspec(dllexport) void sauvegarde(const string file = ""); // sauvegarde data au format BMP

		// pouvoir accéder à un pixel par image(i)
		_declspec(dllexport) unsigned char& operator() (int i) const 
		{ 
		return m_pucPixel[i];
		}

		// pouvoir accéder à un pixel par image(i,j)
		_declspec(dllexport) unsigned char& operator() (int i, int j) const 
		{ 
		return m_pucPixel[i*m_iLargeur+j];
		}

		// opérateur copie image par imOut = imIn, sert à copier une image dans une autre
		_declspec(dllexport) CImageNdg& operator=(const CImageNdg& im);



		// get et set 

		_declspec(dllexport) int lireHauteur() const 
		{  
		return m_iHauteur;            //méthode pour lire la hauteur de l'image
		}

		_declspec(dllexport) int lireLargeur() const  
		{
		return m_iLargeur;      //méthode pour lire la largeur de l'image
		}

		_declspec(dllexport) bool lireBinaire() const 
		{
		return m_bBinaire;          //méthode pour lire si l'image est binaire ou non
		}

		_declspec(dllexport) string lireNom() const 
		{
		return m_sNom;         //méthode pour lire le nom de l'image
		}

		_declspec(dllexport) void ecrireHauteur(int hauteur)  
		{
		m_iHauteur = hauteur;        //méthode pour écrire la hauteur de l'image
		}

		_declspec(dllexport) void ecrireLargeur(int largeur) 
		{
		m_iLargeur = largeur;           //méthode pour écrire la largeur de l'image
		}

		_declspec(dllexport) void ecrireBinaire(bool type) 
		{ 
		m_bBinaire = type;             //méthode pour écrire si l'image est binaire ou non
		}

		_declspec(dllexport) void ecrireNom(std::string nom) 
		{
		m_sNom = nom;               //méthode pour écrire le nom de l'image
		}

		_declspec(dllexport) int lireNbPixels() const 
		{ 
		return m_iHauteur*m_iLargeur;            //méthode pour lire le nombre de pixels de l'image
		}

		_declspec(dllexport) double compterPixelsNonNuls() const
		{
			int count = 0;
			for (int i = 0; i < this->lireHauteur(); ++i) 
			{
				for (int j = 0; j < this->lireLargeur(); ++j) 
				{
					if (this->operator()(i, j) != 0)
					{ // (*this)(i, j) accède à la valeur du pixel
						++count;
					}
				}
			}
			return (double)count;
		}

		_declspec(dllexport) CImageNdg& choixPalette(std::string name = "grise")      //configure la palette de couleur de l'image
			                                   //retourne l'image avec la palette de couleur configurée
			                                   //prend en paramètre le nom de la palette de couleur
		{
			if (name.compare("rouge") == 0)                //attention codé en BGR
			{
				for (int indice=0;indice<256;indice ++)   //configuration d'une palette de 256 nuances de rouge
				{
					this->m_pucPalette[indice*4]   = 0;
					this->m_pucPalette[indice*4+1] = 0;
					this->m_pucPalette[indice*4+2] = (unsigned char)(indice);
					this->m_pucPalette[indice*4+3] = 0;
				}
			}
			else
				if (name.compare("verte") == 0) 
				{
					for (int indice=0;indice<256;indice ++) 
					{
						this->m_pucPalette[indice*4]   = 0;
						this->m_pucPalette[indice*4+1] = (unsigned char)(indice);
						this->m_pucPalette[indice*4+2] = 0;
						this->m_pucPalette[indice*4+3] = 0;
					}
				}
				else
					if (name.compare("bleue") == 0) 
					{
						for (int indice=0;indice<256;indice ++) 
						{
							this->m_pucPalette[indice*4]   = (unsigned char)(indice);
							this->m_pucPalette[indice*4+1] = 0;
							this->m_pucPalette[indice*4+2] = 0;
							this->m_pucPalette[indice*4+3] = 0;
						}
					}
					else
						if (name.compare("binaire") == 0) 
						{
							// fond toujours à 0
							this->m_pucPalette[0] = 0; this->m_pucPalette[1] = 0; this->m_pucPalette[2] = 0; this->m_pucPalette[3] = 0;

							// 8 couleurs de base
							// ensuite périodicité, de sorte que l'objet 1 a le même label que l'objet 9 par exemple
							this->m_pucPalette[4]  = 255; this->m_pucPalette[5] = 0;    this->m_pucPalette[6] = 0;    this->m_pucPalette[7] = 0; //B
							this->m_pucPalette[8]  = 0;   this->m_pucPalette[9] = 255;  this->m_pucPalette[10] = 0;   this->m_pucPalette[11] = 0; //G
							this->m_pucPalette[12] = 0;   this->m_pucPalette[13] = 0;   this->m_pucPalette[14] = 255; this->m_pucPalette[15] = 0;  //R
							this->m_pucPalette[16] = 255; this->m_pucPalette[17] = 255; this->m_pucPalette[18] = 0;   this->m_pucPalette[19] = 0;	//cyan
							this->m_pucPalette[20] = 0;   this->m_pucPalette[21] = 255; this->m_pucPalette[22] = 255; this->m_pucPalette[23] = 0; //JAUNE
							this->m_pucPalette[24] = 255; this->m_pucPalette[25] = 0;   this->m_pucPalette[26] = 255; this->m_pucPalette[27] = 0; //MAGENTA
							this->m_pucPalette[28] = 0;   this->m_pucPalette[29] = 128; this->m_pucPalette[30] = 255; this->m_pucPalette[31] = 0;	//ORANGE
							this->m_pucPalette[32] = 128; this->m_pucPalette[33] = 255;   this->m_pucPalette[34] = 128; this->m_pucPalette[35] = 0;	//VERT POMME

							for (int indice=9;indice<256;indice ++) 
							{
								this->m_pucPalette[indice*4]   = this->m_pucPalette[indice*4-32];
								this->m_pucPalette[indice*4+1] = this->m_pucPalette[indice*4+1-32];;
								this->m_pucPalette[indice*4+2] = this->m_pucPalette[indice*4+2-32];;
								this->m_pucPalette[indice*4+3] = 0;
							}
						}
						else // palette gris
							for (int indice=0;indice<256;indice ++)                      //configuration d'une palette de 256 nuances de gris, chaque composante rgb est identique
							{
								this->m_pucPalette[indice*4]   = (unsigned char)(indice);
								this->m_pucPalette[indice*4+1] = (unsigned char)(indice);
								this->m_pucPalette[indice*4+2] = (unsigned char)(indice);
								this->m_pucPalette[indice*4+3] = 0;
							}
			return *this;   //retourne l'image avec la palette de couleur configurée
		}
		
		_declspec(dllexport) CImageNdg& choixPalette(std::vector<int> map)  //ajuste la palette de couleur d'un objet cimageNdg à partir de données
		{                                                  // couleurs données par tableau de 256 couleurs RGB)
			                                              //l'entrée contient une liste de 256*3 valeurs RGB
			for (int indice=0;indice<256;indice ++)      //chaque itération est destinée à configurer une entrée de couleur dans la palette m_pucPalette.
			{
				this->m_pucPalette[indice*4]   = (unsigned char)map[indice*3+2];
				this->m_pucPalette[indice*4+1] = (unsigned char)map[indice*3+1];
				this->m_pucPalette[indice*4+2] = (unsigned char)map[indice*3];
				this->m_pucPalette[indice*4+3] = 0;
			}
			return *this;
		}

		_declspec(dllexport) std::vector<int> lirePalette() const 
		{                                                            // palette image sortie au format tableau de 256 couleurs RGB
			                                                         // palette image sortie au format tableau de 256 couleurs RGB
			std::vector<int> palette;
			palette.resize(256*3);
			for (int indice=0;indice<256;indice ++) {
				palette[indice*3+2] = this->m_pucPalette[indice*4];
				palette[indice*3+1] = this->m_pucPalette[indice*4+1];
				palette[indice*3] = this->m_pucPalette[indice*4+2];
			}
			return palette;
		}

		// opérations sur images
		// histogramme
		_declspec(dllexport) std::vector<unsigned long> histogramme(bool enregistrementCSV = false); 

		// signatures
		// méthode avec histogramme préalablement calculé
		_declspec(dllexport) MOMENTS signatures(const std::vector<unsigned long> h);
		// méthode sans histo préalablement calculé
		_declspec(dllexport) MOMENTS signatures();

		// opérations ensemblistes pour images binaires
		// im1 = im1 operation im2;
		// options : ""et", "ou", "-"
		_declspec(dllexport) CImageNdg operation(const CImageNdg& im, const std::string methode = "et");

		// score comparaison images binaire SEG/verite terrain
		// im1 = im1 operation im2;
		// options : "iou": intersection over union
		_declspec(dllexport) double score(CImageNdg& im, const std::string methode = "iou");

		_declspec(dllexport) CImageNdg seuillage2(const std::string& methode, int& seuilBas, int& seuilHaut);

		// seuillage
		// options : "manuel", "otsu"
		_declspec(dllexport) CImageNdg seuillage(const std::string methode = "otsu", int seuilBas = 128, int seuilHaut = 255, double sigma = 1.0); // seuillage automatique Otsu par défaut, sinon "manuel" et choix des seuils Bas et Haut, ou bien ksigma

		// transformation
		// options : "complement", "expansion", "egalisation"
		_declspec(dllexport) CImageNdg transformation(const std::string methode = "complement"); 

		// morphologie
		// méthode options : "erosion", "dilatation"
		// élément structurant options : "V4" ou "V8"
		_declspec(dllexport) CImageNdg morphologie(const std::string methode = "dilatation", const std::string eltStructurant = "V8", const int nbIteration = 1);

		_declspec(dllexport) CImageNdg nonMaximaSuppression(const CImageNdg& angleImage);

		_declspec(dllexport) CImageNdg filtrage(const std::string& methode, int Ni, int Nj);
		
		_declspec(dllexport) double Hammingdistance(const CImageNdg& imveriteterrain); // distance de Hamming entre 2 images binaires

		_declspec(dllexport) CImageNdg sobel();

		_declspec(dllexport) CImageNdg invert();

		_declspec(dllexport) CImageNdg process();
};

#endif _IMAGE_NDG_