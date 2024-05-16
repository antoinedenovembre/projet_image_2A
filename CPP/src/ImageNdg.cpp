#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <math.h>

#include "ImageNdg.h"
#include "ImageDouble.h"


// constructeurs et destructeur
CImageNdg::CImageNdg() 
{

	this->m_iHauteur  = 0;
	this->m_iLargeur  = 0;
	this->m_bBinaire  = false;       // Image Ndg par d�faut non binaire, binaire apr�s seuillage
	this->m_sNom      = "vide";      // pas de nom par d�faut
	
	this->m_pucPixel  = NULL;        // pas de pixels par d�faut
	this->m_pucPalette = NULL;       // pas de palette par d�faut
}

CImageNdg::CImageNdg(int hauteur, int largeur, int valeur) 
{

	this->m_iHauteur = hauteur;
	this->m_iLargeur = largeur;
	this->m_bBinaire	= false; // Image Ndg par d�faut, binaire apr�s seuillage
	this->m_sNom      = "inconnu";

	this->m_pucPixel = new unsigned char[hauteur*largeur];        // allocation dynamique des pixels 
	this->m_pucPalette = new unsigned char[256*4];	
	choixPalette("grise"); // palette grise par d�faut, choix utilisateur 
	if (valeur != -1) 
		for (int i=0;i<this->lireNbPixels();i++)
			this->m_pucPixel[i] = valeur;
}

CImageNdg::CImageNdg(const std::string name) 
{

	BITMAPFILEHEADER header;
	BITMAPINFOHEADER infoHeader;
	
	std::ifstream f(name.c_str(),std::ios::in | std::ios::binary); 
		if (f.is_open()) {
			f.read((char*)&header.bfType,2);
			f.read((char*)&header.bfSize, 4);
			f.read((char*)&header.bfReserved1, 2);
			f.read((char*)&header.bfReserved2, 2);
			f.read((char*)&header.bfOffBits, 4);
			if (header.bfType != MAGIC_NUMBER_BMP) 
				throw std::string("ouverture format BMP impossible ..."); 
			else {
				f.read((char*)&infoHeader.biSize, 4);
				f.read((char*)&infoHeader.biWidth, 4);
				f.read((char*)&infoHeader.biHeight, 4);
				f.read((char*)&infoHeader.biPlanes, 2);
				f.read((char*)&infoHeader.biBitCount, 2);
				f.read((char*)&infoHeader.biCompression, 4);
				f.read((char*)&infoHeader.biSizeImage, 4);
				f.read((char*)&infoHeader.biXPelsPerMeter, 4);
				f.read((char*)&infoHeader.biYPelsPerMeter, 4);
				f.read((char*)&infoHeader.biClrUsed, 4);
				f.read((char*)&infoHeader.biClrImportant, 4);
				if (infoHeader.biCompression > 0) 
					throw std::string("Format compresse non supporte...");
				else {
					if (infoHeader.biBitCount == 8) {
						this->m_iHauteur = infoHeader.biHeight;
						this->m_iLargeur = infoHeader.biWidth;
						this->m_bBinaire = false;
						this->m_sNom.assign(name.begin(),name.end()-4);
						this->m_pucPalette = new unsigned char[256*4];	
						this->m_pucPixel = new unsigned char[infoHeader.biHeight * infoHeader.biWidth];

						// g�rer multiple de 32 bits via z�ros �ventuels ignor�s
						int complement = (((this->m_iLargeur-1)/4) + 1)*4 - this->m_iLargeur;
						for (int indice=0;indice<4*256;indice++) 
							f.read((char*)&this->m_pucPalette[indice],sizeof(char));

						for (int i= this->m_iHauteur-1; i >= 0; i--) {
							for (int j=0; j<this->m_iLargeur; j++) 
								f.read((char*)&this->m_pucPixel[i*this->m_iLargeur+j],sizeof(char));

							char inutile;
							for (int k=0; k< complement; k++)
								f.read((char*)&inutile,sizeof(char));
						}
					}	
					else 
					{
						// cas d'une image couleur
						this->m_iHauteur = infoHeader.biHeight;
						this->m_iLargeur = infoHeader.biWidth;
						this->m_bBinaire = false;
						this->m_sNom.assign(name.begin(),name.end()-4);
						this->m_pucPalette = new unsigned char[256*4];	
						this->choixPalette("grise"); // palette grise par d�faut
						this->m_pucPixel = new unsigned char[infoHeader.biHeight * infoHeader.biWidth];

						// extraction plan luminance
						int complement = (((this->m_iLargeur*3-1)/4) + 1)*4 - this->m_iLargeur*3;
						for (int i= this->m_iHauteur-1; i >= 0; i--) {
							for (int j=0;j<this->m_iLargeur*3;j+=3) {
								unsigned char rouge,vert,bleu;
								f.read((char*)&rouge,sizeof(char));
								f.read((char*)&vert,sizeof(char)); 
								f.read((char*)&bleu,sizeof(char));
								this->m_pucPixel[i*this->m_iLargeur+j/3]=(unsigned char)(((int)rouge+(int)vert+(int)bleu)/3);
							}	

							char inutile;
							for (int k=0; k< complement; k++)
								f.read((char*)&inutile,sizeof(char));
						}
					}
				}
			}
			f.close();
		}
		else
			throw std::string("ERREUR : Image absente (ou pas ici en tout cas) !");
}

CImageNdg::CImageNdg(const CImageNdg& im) 
{

	this->m_iHauteur = im.lireHauteur();
	this->m_iLargeur = im.lireLargeur();
	this->m_bBinaire = im.lireBinaire(); 
	this->m_sNom     = im.lireNom();
	this->m_pucPixel = NULL; 
	this->m_pucPalette = NULL;

	if (im.m_pucPalette != NULL) {	
		this->m_pucPalette = new unsigned char[256*4];	// allocation dynamique de la palette
		memcpy(this->m_pucPalette,im.m_pucPalette,4*256); // copie de la palette
	}
	if (im.m_pucPixel != NULL) {
		this->m_pucPixel = new unsigned char[im.lireHauteur() * im.lireLargeur()];// allocation dynamique des pixels
		memcpy(this->m_pucPixel,im.m_pucPixel,im.lireNbPixels()); // copie des pixels
	}
}

CImageNdg::~CImageNdg() 
{
	if (this->m_pucPixel)             //lib�ration m�moire des pixels
	{
		delete[] this->m_pucPixel;
		this->m_pucPixel = NULL;
	}

	if (this->m_pucPalette)          //lib�ration m�moire de la palette
	{
		delete[] this->m_pucPalette;
		this->m_pucPalette = NULL;
	}
}

void CImageNdg::sauvegarde(const std::string file) 
{
	BITMAPFILEHEADER header;        //prepare l'entete du fichier bmp
	BITMAPINFOHEADER infoHeader;

	if (this->m_pucPixel) {          //si on a des donnees a sauvegarder
		std::string nomFichier = "res/";         //dossier de sauvegarde
		
		if (file.empty())
			nomFichier += this->lireNom() + ".bmp";        //nom par defaut
		else
			nomFichier += file + ".bmp";                    //nom choisi

		std::ofstream f(nomFichier.c_str(),std::ios::binary);      //ouverture du fichier en ecriture binaire
		if (f.is_open()) {

			int complement = (((this->m_iLargeur-1)/4) + 1)*4 - this->m_iLargeur;

			header.bfType = MAGIC_NUMBER_BMP;            //ecriture des entetes
			f.write((char*)&header.bfType, 2);
			header.bfOffBits = 14 * sizeof(char) + 40 * sizeof(char) + 4 * 256 * sizeof(char); // palette
			header.bfSize = header.bfOffBits + (complement + lireLargeur())*lireHauteur()*sizeof(char);
			f.write((char*)&header.bfSize, 4);
			header.bfReserved1 = 0;
			f.write((char*)&header.bfReserved1, 2);
			header.bfReserved2 = 0;
			f.write((char*)&header.bfReserved2, 2);
			f.write((char*)&header.bfOffBits, 4);

			infoHeader.biSize = 40*sizeof(char);
			f.write((char*)&infoHeader.biSize, 4);
			infoHeader.biWidth = this->m_iLargeur;
			f.write((char*)&infoHeader.biWidth, 4);
			infoHeader.biHeight = this->m_iHauteur;
			f.write((char*)&infoHeader.biHeight, 4);
			infoHeader.biPlanes = 1;
			f.write((char*)&infoHeader.biPlanes, 2);
			infoHeader.biBitCount = 8;
			f.write((char*)&infoHeader.biBitCount, 2);
			infoHeader.biCompression = 0; // pas de compression
			f.write((char*)&infoHeader.biCompression, 4);
			infoHeader.biSizeImage = this->lireNbPixels();
			f.write((char*)&infoHeader.biSizeImage, 4);
			infoHeader.biXPelsPerMeter = 0;
			f.write((char*)&infoHeader.biXPelsPerMeter, 4);
			infoHeader.biYPelsPerMeter = 0;
			f.write((char*)&infoHeader.biYPelsPerMeter, 4);
			infoHeader.biClrUsed = 256;
			f.write((char*)&infoHeader.biClrUsed, 4);
			infoHeader.biClrImportant = 0;
			f.write((char*)&infoHeader.biClrImportant, 4);

			// on remplit la palette                         //ecriture de la palette
			for (int indice=0;indice<4*256;indice ++) 
				f.write((char*)&this->m_pucPalette[indice],sizeof(char)); 

			for (int i= this->m_iHauteur-1; i >= 0; i--) {  //ecriture des pixels et gestion du padding
				for (int j=0;j<m_iLargeur;j++) 
					f.write((char*)&this->m_pucPixel[i*m_iLargeur+j],sizeof(char));
					
				// g�rer multiple de 32 bits
				char inutile;
				for (int k=0; k< complement; k++)
					f.write((char*)&inutile,sizeof(char)); 
				}
		f.close();                         //fermeture du fichier
		}
		else
			throw std::string("Impossible de creer le fichier de sauvegarde !"); //gestion des exceptions
	}
	else
		throw std::string("Pas de donnee a sauvegarder !");
}

CImageNdg& CImageNdg::operator=(const CImageNdg& im)                         //On affecte le contenu de l'image im � l'image courante
{

	if (&im == this)                          //v�rification d'une auto-affectation
		return *this;

	this->m_iHauteur = im.lireHauteur();      //copie des attributs simples depuis l'instance source
	this->m_iLargeur = im.lireLargeur();
	this->m_bBinaire = im.lireBinaire(); 
	this->m_sNom     = im.lireNom();

	if (this->m_pucPixel)                     //gestion de la m�moire pour les pixels
		delete[] this->m_pucPixel;
	this->m_pucPixel = new unsigned char[this->m_iHauteur * this->m_iLargeur];

	if (this->m_pucPalette)                  //gestion de la m�moire pour la palette
		delete[] this->m_pucPalette;
	this->m_pucPalette = new unsigned char[256*4];

	if (im.m_pucPalette != NULL)              //copie des donn�es de l'image source
		memcpy(this->m_pucPalette,im.m_pucPalette,4*256);
	if (im.m_pucPixel != NULL)                
		memcpy(this->m_pucPixel,im.m_pucPixel,im.lireNbPixels());

return *this;                             //retour de l'instance courante
}

// fonctionnalit�s histogramme 
std::vector<unsigned long> CImageNdg::histogramme(bool enregistrementCSV) 
{

	std::vector<unsigned long> h;

	h.resize(256,0);                            // initialisation � 0 ,redimensionnement du vecteur sur 256 �l�ments
	for (int i=0;i<this->lireNbPixels();i++) 
		h[this->operator()(i)] += 1L; 		 // comptage des pixels, calcul de l'histogramme

	if (enregistrementCSV)                    //ecriture de l'histogramme dans un fichier csv
	{
	 std::string fichier = "res/" + this->lireNom() + ".csv";
		std::ofstream f (fichier.c_str());

		if (!f.is_open())
			throw std::string("Impossible d'ouvrir le fichier en ecriture !");
		else {
			for (int i=0;i<(int)h.size();i++)
				f << h[i] << std::endl;
		}
		f.close();
	}

	return h;                           // retourne l'histogramme ainsi calcul�
}

// signatures globales
MOMENTS CImageNdg::signatures(const std::vector<unsigned long> h) 
{

	MOMENTS globales;        //initialisation de la structure
	
	// min                     //calcul du minimum d'intensit�(minNdg)
	int i=0;
	while ((i < (int)h.size()) && (h[i] == 0))
		i++;
	globales.minNdg = i;
		
	// max                   //calcul du maximum d'intensit�(maxNdg)
	i=h.size()-1;
	while ((i > 0) && (h[i] == 0))
		i--;
	globales.maxNdg = i;

	// mediane              //calcul de la m�diane d'intensit�(medianeNdg)
	int moitPop = this->lireNbPixels()/2;

	i=globales.minNdg;
	int somme = h[i];
	while (somme < moitPop) 
	{
		i += 1;
		if (i < (int)h.size())
			somme += h[i];
	}
	globales.medianeNdg = i;

	// moyenne et �cart-type
	float moy=0,sigma=0;
	for (i=globales.minNdg;i<=globales.maxNdg;i++) 
	{
		moy += ((float)h[i])*i;
		sigma += ((float)h[i])*i*i;
	}
	moy /= (float)this->lireNbPixels();
	sigma = sqrt(sigma/(float)this->lireNbPixels() - (moy*moy));
	globales.moyenneNdg = moy;
	globales.ecartTypeNdg = sigma;

	return globales;       //retour de l'objet MOMENTS
}

MOMENTS CImageNdg::signatures() 
{
	
	MOMENTS globales = { 0,0,0,0,0 };        // initialisation de la structure MOMENTS

	std::vector<unsigned long> hist;		// calcul de l'histogramme
	hist = this->histogramme();

	globales = this->signatures(hist);    // calcul des signatures globales

	return globales;              // retour de l'objet MOMENTS
}
//surcharge: pas necessaire de preparer un histogramme en amont, plus rapide

// op�rations ensemblistes images binaires
CImageNdg& CImageNdg::operation(const CImageNdg& im, const std::string methode) 
{

	if ((&im == this) || !(this->lireBinaire() && im.lireBinaire()))  //verification des prerequis
	{
		throw std::string("Operation logique uniquement possible entre 2 images binaires");
		return *this;
	}

	this->m_iHauteur = im.lireHauteur();    //configuration de l'image resultat
	this->m_iLargeur = im.lireLargeur();
	this->m_bBinaire = im.lireBinaire(); 
	this->choixPalette("binaire"); // images binaires -> palettes binaires
	this->m_sNom     = im.lireNom()+"Op";

	if (methode.compare("et") == 0) 
	{
		for (int i=0;i<this->lireNbPixels();i++)
			this->operator()(i) = this->operator()(i) && im(i);
	}
	else
		if (methode.compare("ou") == 0) 
		{
			for (int i=0;i<this->lireNbPixels();i++)
				this->operator()(i) = this->operator()(i) || im(i);
		}
		else
			if (methode.compare("-") == 0) 
			{
				for (int i = 0; i<this->lireNbPixels(); i++)
					this->operator()(i) = this->operator()(i) - im(i); // vigilance sur les images op�r�r�es !
			}

return *this;
}

double CImageNdg::score(const CImageNdg& im, const std::string methode)
{
	// implementation uniquement pour le score IoU
	if (methode.compare("iou") != 0)
	{
		throw std::string("IoU uniquement !");
	}

	// V�rification si les images sont binaires
	if (!this->lireBinaire() || !im.lireBinaire())
	{
		throw std::string("Attention, une des images n'est pas binaire");
	}

	// Utilisation de la m�thode 'operation' pour calculer l'intersection et l'union
	CImageNdg intersection = this->operation(im, "et");
	CImageNdg unionImg = this->operation(im, "ou");

	// Calcul des aires d'intersection et d'union
	double intersectionArea = intersection.compterPixelsNonNuls(); // Supposons que compterPixels() compte les pixels � 1
	double unionArea = unionImg.compterPixelsNonNuls();

	// Calcul du score IoU
	double iouScore = (unionArea == 0.0) ? 0.0 : intersectionArea / unionArea;

	// Cr�ation d'une nouvelle image pour stocker le r�sultat
	//CImageNdg* resultImage = new CImageNdg(this->lireHauteur(), this->lireLargeur(), iouScore);

	// Retour de l'image r�sultat
	//return *resultImage;
}

// seuillage
CImageNdg CImageNdg::seuillage(const std::string methode, int seuilBas, int seuilHaut, double sigma)
{
	
	if (!this->m_bBinaire)    //v�rification d'une image binaire
	{
		CImageNdg out(this->lireHauteur(),this->lireLargeur());    //initialisation de l'image resultat
		out.choixPalette("binaire"); // palette binaire par d�faut
		out.m_bBinaire = true;

		// cr�ation lut pour optimisation calcul   pour optimiser le calcul du seuillage
		std::vector<int> lut;
		lut.resize(256);

		// recherche valeur seuil
		// cas "manuel" 
		if (methode.compare("manuel") == 0)
		{
			out.m_sNom = this->lireNom() + "SeMa";
		}
		else 
			if (methode.compare("otsu") == 0)
			{
				out.m_sNom = this->lireNom() + "SeAu";
				// recherche seuil via Otsu
				std::vector<unsigned long> hist = this->histogramme();
				std::vector<unsigned long> histC; // histogramme cumul�
				histC.resize(256, 0);
				histC[0] = hist[0];
				for (int i = 1; i < (int)hist.size(); i++)
					histC[i] = histC[i - 1] + hist[i];

				MOMENTS globales = this->signatures(hist);
				int min = globales.minNdg,
					max = globales.maxNdg;

				// f(s)
				std::vector<double> tab;
				tab.resize(256, 0);

				double M1, M2, w1;

				// initialisation
				M1 = min;
				seuilBas = min;
				seuilHaut = 255;

				w1 = (double)histC[min] / (double)(this->lireNbPixels());
				M2 = 0;
				for (int i = min + 1; i <= max; i++)
					M2 += (double)hist[i] * i;
				M2 /= (double)(histC[max] - hist[min]);
				tab[min] = w1*(1 - w1)*(M1 - M2)*(M1 - M2);

				for (int i = min + 1; i < max; i++) {
					M1 = ((double)histC[i - 1] * M1 + (double)hist[i] * i) / histC[i];
					M2 = ((double)(histC[255] - histC[i - 1])*M2 - hist[i] * i) / (double)(histC[255] - histC[i]);
					w1 = (double)histC[i] / (double)(this->lireNbPixels());
					tab[i] = w1*(1 - w1)*(M1 - M2)*(M1 - M2);
					if (tab[i] > tab[seuilBas])
						seuilBas = i;
				}
			}
			else 
			{
				// gestion des seuils valant "moyenne" et "mediane"
				if (methode.compare("moyenne")==0)    //utiliser la moyenne des intensit�s de l'image comme seuil
				{
					out.m_sNom = this->lireNom() + "SeMo";
					seuilBas = (int)this->signatures().moyenneNdg;
					seuilHaut = 255;
				}

				else 
					if (methode.compare("mediane") == 0)	//utiliser la m�diane des intensit�s de l'image comme seuil
						{
							out.m_sNom = this->lireNom() + "SeMe";
							seuilBas = (int)this->signatures().medianeNdg;
							seuilHaut = 255;
						}

				else 
					if (methode.compare("ksigma") == 0)
						{
							out.m_sNom = this->lireNom() + "SeKS";

							// Calculer la moyenne et l'�cart-type de l'image
							MOMENTS stats = this->signatures();
							double moyenne = stats.moyenneNdg;
							double ecartType = stats.ecartTypeNdg;

							// Utiliser le param�tre sigma optionnel pour d�terminer les seuils
							// Si sigma n'est pas fourni, utiliser une valeur par d�faut, par exemple 1
							double k = (sigma > 0) ? sigma : 1.0;

							seuilBas = static_cast<int>(moyenne - k * ecartType);
							seuilHaut = static_cast<int>(moyenne + k * ecartType);

							// Assurer que les seuils restent dans les limites de 0 � 255
							seuilBas = std::max(0, seuilBas);
							seuilHaut = std::min(255, seuilHaut);
						}

			}
 

		// g�n�ration lut
		for (int i = 0; i < seuilBas; i++)
			lut[i] =  0; 
		for (int i = seuilBas; i <= seuilHaut; i++)
			lut[i] = 1;
		for (int i = seuilHaut+1; i <= 255; i++)
			lut[i] = 0;

		// cr�ation image seuill�e
		std::cout << "Seuillage des pixels entre " << seuilBas << " et " << seuilHaut << std::endl;
		for (int i=0; i < out.lireNbPixels(); i++) 
			out(i) = lut[this->operator ()(i)]; 

		return out;
		}
	else {
		throw std::string("Seuillage image binaire impossible");
		return (*this);
	}
}

// transformation
CImageNdg CImageNdg::transformation(const std::string methode) 
{

	CImageNdg out(this->lireHauteur(),this->lireLargeur());     // initialisation de l'image resultat

	std::vector<int> map = this->lirePalette();                 // conservation de la palette
	out.choixPalette(map); // conservation de la palette 
	out.m_bBinaire = this->m_bBinaire; // conservation du type

	if (methode.compare("complement") == 0)                   // gestion du cas complement
	{
		out.m_sNom = this->lireNom() + "TComp";              // nommage de l'image resultat
		// ndg -> 255-ndg
		// cr�ation lut pour optimisation calcul     : mappage de chaque niveau de gris � son compl�ment (255-niveau)
		std::vector<int> lut;
		lut.resize(256);

		//
		//for (int i = 0; i < 256; i++)
		//	lut[i] = (int)(255 - i);
		if (!this->lireBinaire())
			for (int i = 0; i < 256; i++)
				lut[i] = (int)(255 - i);


		else      //pour les images binaires, la LUT convertit 0 en 1 et tous les autres niveaux en 0
		{
			lut[0] = 1;
			for (int i = 1; i < 256; i++)
				lut[i] = 0;
		}
		
		for (int i = 0; i < out.lireNbPixels(); i++) //chaque pixel de l'image est maj grace � la lut
			out(i) = lut[this->operator()(i)];
	}
	else
		if (methode.compare("expansion") == 0) 
		{
			out.m_sNom = this->lireNom() + "TExp";     // nommage de l'image resultat
			int min = 255, max = 0; 
			for (int i = 0; i < this->lireNbPixels(); i++) {  // recherche min et max image
				if (this->operator()(i) > max)
					max = this->operator()(i);
				if (this->operator()(i) < min)
					min = this->operator()(i);
			}

			double a = 255 / (double)(max - min);
			double b = -a*min;

			std::vector<int> lut;   // cr�ation lut pour expansion lin�aire des niveaux de gris en fonction de min et max
			lut.resize(256);

			for (int i = 0; i < 256; i++) //maj de chaque pixel de l'image en fonction de la lut
				lut[i] = (int)(a*i + b);
			for (int i = 0; i < out.lireNbPixels(); i++)
				out(i) = lut[this->operator()(i)];
		}
		else
			if (methode.compare("egalisation") == 0) 
			{
				out.m_sNom = this->lireNom() + "TEga";
				std::vector<unsigned long> h = this->histogramme(); // calcul de l'histogramme
				std::vector<unsigned long> hC = h;  // histogramme cumul�
				for (int i = 1; i<(int)h.size(); i++)
					hC[i] = hC[i - 1] + h[i]; // calcul de l'histogramme cumul�

				// recherche min et max non nuls de l'histogramme
				int min = 0, max = 255;
				int i = 0;
				while (h[i] == 0)
					i++;
				min = i;
				i = 255;
				while (h[i] == 0)
					i--;
				max = i;

				std::vector<int> lut;// cr�ation lut pour r�partition uniforme des niveaux de gris entre min et max
				lut.resize(256);

				for (int i = min; i <= max; i++)   //maj de chaque pixel de l'image en fonction de la lut
					lut[i] = (int)(((double)hC[i] / (double)this->lireNbPixels())*(double)255);

				for (int i = 0; i < out.lireNbPixels(); i++)
					out(i) = lut[this->operator()(i)]; //maj de chaque pixel de l'image en fonction de la lut
			}

	return out;
}

// morphologie
CImageNdg CImageNdg::morphologie(const std::string methode, const std::string eltStructurant) 
{

	CImageNdg out(this->lireHauteur(), this->lireLargeur()); // initialisation de l'image resultat

	out.choixPalette(this->lirePalette()); // conservation de la palette

	out.m_bBinaire = this->m_bBinaire; // conservation du type

	if (methode.compare("erosion") == 0) 
	{
		out.m_sNom = this->lireNom() + "MEr";    //image agrandie pour gestion des bords
		CImageNdg agrandie(this->lireHauteur() + 2, this->lireLargeur() + 2); //plus grande pour permettre �rosion aux bords

		// gestion des bords
		if (this->lireBinaire())  //si image binaire
		{
			int pix;

			for (pix = 0; pix<agrandie.lireLargeur(); pix++) //bord haut et bas
			{
				agrandie(0, pix) = 1;    //bord haut donc premi�re ligne tous les pixels � 1: blanc
				agrandie(this->lireHauteur() - 1, pix) = 1;  //bord bas donc derni�re ligne tous les pixels � 1: blanc
			}
			for (pix = 1; pix<agrandie.lireHauteur() - 1; pix++) //bord gauche et droit
			{
				agrandie(pix, 0) = 1;    //bord gauche donc premi�re colonne tous les pixels � 1: blanc
				agrandie(pix, this->lireLargeur() - 1) = 1;  //bord droit donc derni�re colonne tous les pixels � 1: blanc
			}
		}
		else {    //si image ndg
			int pix;

			for (pix = 0; pix<agrandie.lireLargeur(); pix++) {  //bord haut et bas
				agrandie(0, pix) = 255;   //bord haut donc premi�re ligne tous les pixels � 255: blanc
				agrandie(this->lireHauteur() - 1, pix) = 255;  //bord bas donc derni�re ligne tous les pixels � 255: blanc
			}
			for (pix = 1; pix<agrandie.lireHauteur() - 1; pix++) { //bord gauche et droit
				agrandie(pix, 0) = 255;   //bord gauche donc premi�re colonne tous les pixels � 255: blanc
				agrandie(pix, this->lireLargeur() - 1) = 255;  //bord droit donc derni�re colonne tous les pixels � 255: blanc
			}
		}

		// gestion du coeur
		for (int i = 0; i<this->lireHauteur(); i++)
			for (int j = 0; j<this->lireLargeur(); j++) {
				agrandie(i + 1, j + 1) = this->operator()(i, j);    //copie de l'image originale dans le coeur de l'image agrandie
			}

		if (eltStructurant.compare("V4") == 0) { //erosion avec elt structurant V4
			for (int i = 1; i<agrandie.lireHauteur() - 1; i++)
				for (int j = 1; j<agrandie.lireLargeur() - 1; j++) {
					int minH = std::min(agrandie(i, j - 1), agrandie(i, j + 1)); //valeur min des pixels voisins horizontaux
					int minV = std::min(agrandie(i - 1, j), agrandie(i + 1, j)); //valeur min des pixels voisins verticaux
					int minV4 = std::min(minH, minV); //valeur min des pixels voisins horizontaux et verticaux
					out(i - 1, j - 1) = std::min(minV4, (int)agrandie(i, j)); //valeur du pixel = min des pixels voisins et lui meme
				}
		}
		else {
			if (eltStructurant.compare("V8") == 0) {
				for (int i = 1; i<agrandie.lireHauteur() - 1; i++)  //parcour de l'image agrandie en excluant les bords
					for (int j = 1; j<agrandie.lireLargeur() - 1; j++) {    //parcour de l'image agrandie en excluant les bords
						int minH = std::min(agrandie(i, j - 1), agrandie(i, j + 1)); //valeur min des pixels voisins horizontaux
						int minV = std::min(agrandie(i - 1, j), agrandie(i + 1, j)); //valeur min des pixels voisins verticaux
						int minV4 = std::min(minH, minV); //valeur min des pixels voisins horizontaux et verticaux
						int minD1 = std::min(agrandie(i - 1, j - 1), agrandie(i + 1, j + 1)); //valeur min des pixels voisins diagonaux 1
						int minD2 = std::min(agrandie(i - 1, j + 1), agrandie(i + 1, j - 1)); //valeur min des pixels voisins diagonaux 2
						int minD = std::min(minD1, minD2); //valeur min des pixels voisins diagonaux
						int minV8 = std::min(minV4, minD); //valeur min des pixels voisins horizontaux, verticaux et diagonaux
						out(i - 1, j - 1) = std::min(minV8, (int)agrandie(i, j)); //valeur du pixel = min des pixels voisins et lui meme
					}
			}
		}
	}
	else {
		if (methode.compare("dilatation") == 0)          
		{
			out.m_sNom = this->lireNom() + "MDi";   //image agrandie pour gestion des bords
			CImageNdg agrandie(this->lireHauteur() + 2, this->lireLargeur() + 2); //image agrandie pour gestion des bords

			// gestion des bords
			int pix; 

			for (pix = 0; pix<agrandie.lireLargeur(); pix++) {
				agrandie(0, pix) = 0; //bord haut donc premi�re ligne tous les pixels � 0: noir
				agrandie(agrandie.lireHauteur() - 1, pix) = 0; //bord bas donc derni�re ligne tous les pixels � 0: noir
			}
			for (pix = 1; pix<agrandie.lireHauteur() - 1; pix++) {
				agrandie(pix, 0) = 0;  //bord gauche donc premi�re colonne tous les pixels � 0: noir
				agrandie(pix, agrandie.lireLargeur() - 1) = 0; //bord droit donc derni�re colonne tous les pixels � 0: noir
			}

			// gestion du coeur
			for (int i = 0; i<this->lireHauteur(); i++) 
				for (int j = 0; j<this->lireLargeur(); j++) {
					agrandie(i + 1, j + 1) = this->operator()(i, j);   //copie de l'image originale dans le coeur de l'image agrandie
				}

			if (eltStructurant.compare("V4") == 0) { //dilatation avec elt structurant V4
				for (int i = 1; i<agrandie.lireHauteur() - 1; i++) //parcour de l'image agrandie en excluant les bords
					for (int j = 1; j<agrandie.lireLargeur() - 1; j++) { //parcour de l'image agrandie en excluant les bords
						int maxH = std::max(agrandie(i, j - 1), agrandie(i, j + 1)); //valeur max des pixels voisins horizontaux
						int maxV = std::max(agrandie(i - 1, j), agrandie(i + 1, j)); //valeur max des pixels voisins verticaux
						int maxV4 = std::max(maxH, maxV); //valeur max des pixels voisins horizontaux et verticaux
						out(i - 1, j - 1) = std::max(maxV4, (int)agrandie(i, j)); //valeur du pixel = max des pixels voisins et lui meme
					}
			}
			else {
				if (eltStructurant.compare("V8") == 0) { //dilatation avec elt structurant V8
					for (int i = 1; i<agrandie.lireHauteur() - 1; i++) //parcour de l'image agrandie en excluant les bords
						for (int j = 1; j<agrandie.lireLargeur() - 1; j++) { //parcour de l'image agrandie en excluant les bords
							int maxH = std::max(agrandie(i, j - 1), agrandie(i, j + 1)); //valeur max des pixels voisins horizontaux
							int maxV = std::max(agrandie(i - 1, j), agrandie(i + 1, j)); //valeur max des pixels voisins verticaux
							int maxV4 = std::max(maxH, maxV); //valeur max des pixels voisins horizontaux et verticaux
							int maxD1 = std::max(agrandie(i - 1, j - 1), agrandie(i + 1, j + 1)); //valeur max des pixels voisins diagonaux 1
							int maxD2 = std::max(agrandie(i - 1, j + 1), agrandie(i + 1, j - 1)); //valeur max des pixels voisins diagonaux 2
							int maxD = std::max(maxD1, maxD2); //valeur max des pixels voisins diagonaux
							int maxV8 = std::max(maxV4, maxD); //valeur max des pixels voisins horizontaux, verticaux et diagonaux
							out(i - 1, j - 1) = std::max(maxV8, (int)agrandie(i, j)); //valeur du pixel = max des pixels voisins et lui meme
						}
				}
			}
		}
	}

	return out;

}

CImageNdg CImageNdg::nonMaximaSuppression(const CImageNdg& angleImage)
{
	CImageNdg result(this->lireHauteur(), this->lireLargeur());
	result.m_sNom = this->lireNom() + "NMS";
	result.choixPalette(this->lirePalette());
	result.m_bBinaire = this->m_bBinaire;

	for (int i = 1; i < this->lireHauteur() - 1; i++)
	{
		for (int j = 1; j < this->lireLargeur() - 1; j++)
		{
			float angle = angleImage(i, j) * 180.0 / M_PI; // Convert radian to degree
			angle = fmod(angle + 360, 360);          // Ensure angle is within [0,360)

			// Determine the direction of the edge
			int q = 255, r = 255;
			if ((angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle < 202.5) || (angle >= 337.5 && angle <= 360))
				q = this->operator()(i, j + 1), r = this->operator()(i, j - 1);
			else if ((angle >= 22.5 && angle < 67.5) || (angle >= 202.5 && angle < 247.5))
				q = this->operator()(i + 1, j - 1), r = this->operator()(i - 1, j + 1);
			else if ((angle >= 67.5 && angle < 112.5) || (angle >= 247.5 && angle < 292.5))
				q = this->operator()(i + 1, j), r = this->operator()(i - 1, j);
			else if ((angle >= 112.5 && angle < 157.5) || (angle >= 292.5 && angle < 337.5))
				q = this->operator()(i - 1, j - 1), r = this->operator()(i + 1, j + 1);

			// Suppress non-maxima
			if (this->operator()(i, j) >= q && this->operator()(i, j) >= r)
				result(i, j) = this->operator()(i, j);
			else
				result(i, j) = 0;
		}
	}

	return result;
}

CImageNdg CImageNdg::filtrage(const std::string& methode, int Ni, int Nj)
{

	CImageNdg out(this->lireHauteur(), this->lireLargeur());
	out.m_sNom = this->lireNom() + "F";
	out.choixPalette(this->lirePalette()); // conservation de la palette
	out.m_bBinaire = this->m_bBinaire;     // conservation du type

	if (methode.compare("moyennage") == 0)
	{
		int nbBordsi = Ni / 2;
		int nbBordsj = Nj / 2;

		for (int i = 0; i < this->lireHauteur(); i++)
			for (int j = 0; j < this->lireLargeur(); j++)
			{
				// gestion des bords
				int dk = std::max(0, i - nbBordsi);
				int fk = std::min(i + nbBordsi, this->lireHauteur() - 1);
				int dl = std::max(0, j - nbBordsj);
				int fl = std::min(j + nbBordsj, this->lireLargeur() - 1);

				float somme = 0;
				float moy = 0;
				for (int k = dk; k <= fk; k++)
					for (int l = dl; l <= fl; l++)
					{
						moy += (float)this->operator()(k, l);
						somme += 1;
					}
				out(i, j) = (int)(moy / somme);
			}
	}
	else if (methode.compare("median") == 0)
	{
		int nbBordsi = Ni / 2;
		int nbBordsj = Nj / 2;

		std::vector<int> voisinage;

		for (int i = 0; i < this->lireHauteur(); i++)
			for (int j = 0; j < this->lireLargeur(); j++)
			{
				// gestion des bords
				int dk = std::max(0, i - nbBordsi);
				int fk = std::min(i + nbBordsi, this->lireHauteur() - 1);
				int dl = std::max(0, j - nbBordsj);
				int fl = std::min(j + nbBordsj, this->lireLargeur() - 1);

				voisinage.resize((fk - dk + 1) * (fl - dl + 1));
				int indMed = (fk - dk + 1) * (fl - dl + 1) / 2;

				// empilement
				int indice = 0;
				for (int k = dk; k <= fk; k++)
					for (int l = dl; l <= fl; l++)
					{
						voisinage.at(indice) = (int)this->operator()(k, l);
						indice++;
					}

				// tri croissant
				std::sort(voisinage.begin(), voisinage.end());

				out(i, j) = voisinage.at(indMed);

				voisinage.clear();
			}
	}
	else if (methode.compare("gaussien") == 0)
	{
		int nbBordsi = Ni / 2;
		int nbBordsj = Nj / 2;

		std::vector<double> noyau;
		noyau.resize(Ni * Nj);

		double somme = 0;
		for (int i = 0; i < Ni; i++)
			for (int j = 0; j < Nj; j++)
			{
				noyau.at(i * Nj + j) =
					exp(-((i - nbBordsi) * (i - nbBordsi) + (j - nbBordsj) * (j - nbBordsj)) / (2 * 1 * 1));
				somme += noyau.at(i * Nj + j);
			}

		for (int i = 0; i < Ni; i++)
			for (int j = 0; j < Nj; j++)
				noyau.at(i * Nj + j) /= somme;

		for (int i = 0; i < this->lireHauteur(); i++)
			for (int j = 0; j < this->lireLargeur(); j++)
			{
				// gestion des bords
				int dk = std::max(0, i - nbBordsi);
				int fk = std::min(i + nbBordsi, this->lireHauteur() - 1);
				int dl = std::max(0, j - nbBordsj);
				int fl = std::min(j + nbBordsj, this->lireLargeur() - 1);

				double somme = 0;
				double moy = 0;
				for (int k = dk; k <= fk; k++)
					for (int l = dl; l <= fl; l++)
					{
						moy += (double)this->operator()(k, l) * noyau.at((k - dk) * Nj + (l - dl));
						somme += noyau.at((k - dk) * Nj + (l - dl));
					}
				out(i, j) = (int)(moy / somme);
			}
	}
	else if (methode.compare("canny") == 0)
	{
		CImageDouble imgDouble(*this);
		CImageDouble imgDoubleFiltre = imgDouble.filtrage("gaussien", Ni, Nj);
		CImageDouble imgDoubleGradient = imgDoubleFiltre.vecteurGradient("norme");
		CImageDouble imgDoubleGradientAngle = imgDoubleFiltre.vecteurGradient("angle");

		CImageNdg imgNdgGradient = imgDoubleGradient.toNdg();
		CImageNdg imgNdgGradientAngle = imgDoubleGradientAngle.toNdg();

		CImageNdg imgNdgGradientNonMaxSuppr = imgNdgGradient.nonMaximaSuppression(imgNdgGradientAngle);
		out = imgNdgGradientNonMaxSuppr.seuillage("manuel", 50, 100);
	}

	return out;
}

double CImageNdg::Hammingdistance(const CImageNdg& imveriteterrain) // distance de Hamming entre 2 images binaires
{
	// Acc�s aux m�thodes et membres de l'objet courant avec 'this->'
	if (!this->lireBinaire() || !imveriteterrain.lireBinaire()) // v�rification des images binaires
	{
		throw std::string("Une des images n'est pas binaire");
	}

	if (this->lireHauteur() != imveriteterrain.lireHauteur() || this->lireLargeur() != imveriteterrain.lireLargeur()) // v�rification des dimensions
	{
		throw std::string("Attention, les images n'ont pas les m�mes dimensions");
	}

	double hammingDistance = 0; // Initialisation de la distance de Hamming

	// Calcul de la distance de Hamming
	for (int i = 0; i < this->lireNbPixels(); i++)
	{
		if ((*this)(i) != imveriteterrain(i))  // Utilisation de (*this)(i) pour acc�der aux pixels de l'image courante
		{
			hammingDistance++;
		}
	}

	// Calcul et retour de la distance de Hamming normalis�e
	double normalizedHammingDistance = static_cast<double>(hammingDistance) / (this->lireHauteur() * this->lireLargeur());
	return normalizedHammingDistance;
}


CImageNdg CImageNdg::sobel()
{
	CImageNdg imgSobel(lireHauteur(), lireLargeur());

	// Initialize borders to zero
	for (int i = 0; i < lireHauteur(); i++)
	{
		imgSobel(i, 0) = 0;
		imgSobel(i, lireLargeur() - 1) = 0;
	}
	for (int j = 0; j < lireLargeur(); j++)
	{
		imgSobel(0, j) = 0;
		imgSobel(lireHauteur() - 1, j) = 0;
	}

	// Sobel operator
	int Gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };

	int Gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

	for (int i = 1; i < lireHauteur() - 1; i++)
	{
		for (int j = 1; j < lireLargeur() - 1; j++)
		{
			int sumX = 0;
			int sumY = 0;

			for (int k = -1; k <= 1; k++)
			{
				for (int l = -1; l <= 1; l++)
				{
					sumX += operator()(i + k, j + l) * Gx[k + 1][l + 1];
					sumY += operator()(i + k, j + l) * Gy[k + 1][l + 1];
				}
			}

			// Calculate the magnitude of gradients
			int sum = static_cast<int>(sqrt(sumX * sumX + sumY * sumY));
			// Clamp the value to the 0-255 range
			imgSobel(i, j) = std::min(std::max(sum, 0), 255);
		}
	}

	return imgSobel;
}

CImageNdg CImageNdg::invert()
{
	CImageNdg imgInvert(lireHauteur(), lireLargeur());

	for (int i = 0; i < lireHauteur(); i++)
	{
		for (int j = 0; j < lireLargeur(); j++)
		{
			imgInvert(i, j) = 255 - operator()(i, j);
		}
	}

	return imgInvert;
}



CImageNdg CImageNdg::process()
{
	CImageNdg tmp = *this;

	std::cout << "Processing image " << tmp.lireNom() << std::endl;

	// Invert the image if its name starts with "In"
	if (tmp.lireNom().find("In") == 0)
	{
		tmp = tmp.invert();
	}

	// First step, we apply a gaussian filter to the image
	CImageNdg imgFiltered = tmp.filtrage("median", 5, 5);

	// Contours detection, sobel operator
	CImageNdg imgSobel = imgFiltered.sobel();

	// Thresholding
	CImageNdg imgThresholded = imgSobel.seuillage("otsu");

	return imgThresholded;
}