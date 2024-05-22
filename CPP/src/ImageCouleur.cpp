#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <windows.h>

#include "ImageCouleur.h"

// constructeurs et destructeur
CImageCouleur::CImageCouleur() 
{

	this->m_iHauteur  = 0;
	this->m_iLargeur  = 0;
	this->m_sNom      = "vide";
	this->m_pucData   = NULL;
	this->m_ppucPixel = NULL;
}

CImageCouleur::CImageCouleur(int hauteur, int largeur, int valR, int valV, int valB) {

	this->m_iHauteur = hauteur;   // initialisation des attributs
	this->m_iLargeur = largeur;		
	this->m_sNom     = "inconnu";   

	this->m_pucData = new unsigned char[hauteur*largeur*3];     //allocation de la mémoire pour les données de l'image
	this->m_ppucPixel = new unsigned char*[hauteur*largeur];    //allocation de la mémoire pour les pixels de l'image
	for (int i=0;i<hauteur*largeur;i++)
		this->m_ppucPixel[i] = &this->m_pucData[3*i];    //chaque pointeur du tableau de pointeurs pointe vers le début d'un triplet RGB

	if (valR != -1) 
		for (int i=0;i<this->lireNbPixels();i++)
			this->m_ppucPixel[i][0] = valR;
	if (valV != -1) 
		for (int i=0;i<this->lireNbPixels();i++)
			this->m_ppucPixel[i][1] = valV;
	if (valB != -1) 
		for (int i=0;i<this->lireNbPixels();i++)
			this->m_ppucPixel[i][2] = valB;
}

CImageCouleur::CImageCouleur(const std::string name) 
{
	BITMAPFILEHEADER header;
	BITMAPINFOHEADER infoHeader;


	std::ifstream f(name.c_str(),std::ios::in | std::ios::binary); // transformation d'une string en chaîne de type C
	if (f.is_open()) {
			f.read((char*)&header.bfType, 2);
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
				throw std::string("Format compresse non supporté...");
			else {
				if (infoHeader.biBitCount == 24) {
					this->m_iHauteur = infoHeader.biHeight;
					this->m_iLargeur = infoHeader.biWidth;
					this->m_sNom.assign(name.begin(),name.end()-4);
					this->m_pucData = new unsigned char[infoHeader.biHeight*infoHeader.biWidth*3];
					this->m_ppucPixel = new unsigned char*[infoHeader.biHeight*infoHeader.biWidth];
					for (int i=0;i<(int)(infoHeader.biHeight*infoHeader.biWidth);i++)
						this->m_ppucPixel[i] = &this->m_pucData[3*i];

					// gérer multiple de 32 bits via zéros éventuels ignorés
					int complement = (((this->m_iLargeur*3-1)/4) + 1)*4 - this->m_iLargeur*3;

					for (int i= m_iHauteur-1; i >= 0; i--) {
						for (int j=0;j<m_iLargeur;j++) {
							f.read((char*)&this->m_ppucPixel[i*m_iLargeur+j][2],sizeof(char));
							f.read((char*)&this->m_ppucPixel[i*m_iLargeur+j][1],sizeof(char)); 
							f.read((char*)&this->m_ppucPixel[i*m_iLargeur+j][0],sizeof(char));
					}	

					char inutile;
					for (int k=0; k< complement; k++)
						f.read((char*)&inutile,sizeof(char));
					}
				}
				else {
					// cas d'une image en niveaux de gris
					this->m_iHauteur = infoHeader.biHeight;
					this->m_iLargeur = infoHeader.biWidth;
					this->m_sNom.assign(name.begin(),name.end()-4);
					this->m_pucData = new unsigned char[infoHeader.biHeight*infoHeader.biWidth*3];
					this->m_ppucPixel = new unsigned char*[infoHeader.biHeight*infoHeader.biWidth];
					for (int i=0;i<(int)(infoHeader.biHeight*infoHeader.biWidth);i++)
						this->m_ppucPixel[i] = &this->m_pucData[3*i];

					// lecture palette
					unsigned char* palette=NULL;
					palette = new unsigned char[256*4];
					for (int indice=0;indice<4*256;indice++) 
						f.read((char*)&palette[indice],sizeof(char));
					
					// gérer multiple de 32 bits via zéros éventuels ignorés
					int complement = (((this->m_iLargeur-1)/4) + 1)*4 - this->m_iLargeur;
					// passage du gris vers la couleur par duplication des valeurs
					for (int i= m_iHauteur-1; i >= 0; i--) {
						for (int j=0;j<m_iLargeur;j++) {
							unsigned char temp;
							f.read((char*)&temp,sizeof(char));
							this->m_ppucPixel[i*m_iLargeur+j][0]=palette[4*temp+2];
							this->m_ppucPixel[i*m_iLargeur+j][1]=palette[4*temp+1];
							this->m_ppucPixel[i*m_iLargeur+j][2]=palette[4*temp];
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

CImageCouleur::CImageCouleur(const CImageCouleur& im) 
{

	this->m_iHauteur = im.lireHauteur();
	this->m_iLargeur = im.lireLargeur();
	this->m_sNom     = im.lireNom()+"Copie";
	this->m_pucData = NULL;
	this->m_ppucPixel = NULL;

	if (im.m_pucData != NULL) 
	{
		this->m_pucData = new unsigned char[im.lireHauteur()*im.lireLargeur()*3];
		this->m_ppucPixel = new unsigned char*[im.lireHauteur()*im.lireLargeur()];
		for (int i=0;i<im.lireHauteur()*im.lireLargeur();i++)
			this->m_ppucPixel[i] = &this->m_pucData[3*i];
		
		memcpy(this->m_pucData,im.m_pucData,im.lireNbPixels()*3);
		}
}

CImageCouleur::CImageCouleur(const CImageNdg& im) 
{

	this->m_iHauteur = im.lireHauteur();     // initialisation des attributs
	this->m_iLargeur = im.lireLargeur();	// initialisation des attributs
	this->m_sNom = im.lireNom()+"RGB";    // initialisation des attributs
	this->m_pucData = NULL;      
	this->m_ppucPixel = NULL;

	if (im.lireNbPixels() > 0) 
	{
		this->m_pucData = new unsigned char[im.lireHauteur()*im.lireLargeur() * 3];//allocation de la mémoire pour stocker les données des pixels en couleur (données RGB pour chaque pixel)
		this->m_ppucPixel = new unsigned char*[im.lireHauteur()*im.lireLargeur()]; // stockage des pointeurs vers chaque pixel
		for (int i = 0; i<im.lireHauteur()*im.lireLargeur(); i++)
			this->m_ppucPixel[i] = &this->m_pucData[3 * i]; //chaque pointeur du tableau de pointeurs pointe vers le début d'un triplet RGB

		for (int i = 0; i < im.lireNbPixels(); i++)
			this->operator()(i)[0] = this->operator()(i)[1] = this->operator()(i)[2] = im(i);//chaque pixel en ndg est dupliqué pour chaque plan RGB
																							//chaque pixel a des composantes R,G et B identiques: image en echelle de gris mais stockée dns un format couleur
	}
}

CImageCouleur::CImageCouleur(const CImageNdg& pR, const CImageNdg& pG, const CImageNdg& pB) 
{

	this->m_iHauteur = pR.lireHauteur();    // initialisation des attributs
	this->m_iLargeur = pR.lireLargeur();	// initialisation des attributs
	this->m_sNom = pR.lireNom() + "RGB";   // initialisation des attributs
	this->m_pucData = NULL; // initialisation des attributs
	this->m_ppucPixel = NULL; // initialisation des attributs

	if (pR.lireNbPixels() > 0) // si l'image est non vide
	{
		this->m_pucData = new unsigned char[pR.lireHauteur()*pR.lireLargeur() * 3];//allocation de la mémoire pour stocker les données des pixels en couleur (données RGB pour chaque pixel)
		this->m_ppucPixel = new unsigned char*[pR.lireHauteur()*pR.lireLargeur()];// stockage des pointeurs vers chaque pixel
		for (int i = 0; i<pR.lireHauteur()*pR.lireLargeur(); i++)
			this->m_ppucPixel[i] = &this->m_pucData[3 * i]; //chaque pointeur du tableau de pointeurs pointe vers le début d'un triplet RGB

		for (int i = 0; i < pR.lireNbPixels(); i++)
		{
			this->operator()(i)[0] = pR(i); 
			this->operator()(i)[1] = pG(i);
			this->operator()(i)[2] = pB(i);
		}
	}
}

// masquage avec image binaire (exemple des contours)
CImageCouleur::CImageCouleur(const CImageNdg& im, const CImageNdg& mask, int R, int G, int B)      //mask:masque binaire
{
	this->m_iHauteur = im.lireHauteur();         // initialisation des attributs
	this->m_iLargeur = im.lireLargeur();
	this->m_sNom = im.lireNom() + "Mask";
	this->m_pucData = NULL;
	this->m_ppucPixel = NULL;

	if (im.lireNbPixels() > 0)     // si l'image est non vide
	{
		this->m_pucData = new unsigned char[im.lireHauteur()*im.lireLargeur() * 3];   //allocation de la mémoire pour stocker les données des pixels en couleur (données RGB pour chaque pixel)
		this->m_ppucPixel = new unsigned char*[im.lireHauteur()*im.lireLargeur()];	// stockage des pointeurs vers chaque pixel
		for (int i = 0; i<im.lireHauteur()*im.lireLargeur(); i++)
			this->m_ppucPixel[i] = &this->m_pucData[3 * i]; //chaque pointeur du tableau de pointeurs pointe vers le début d'un triplet RGB

		for (int i = 0; i < im.lireNbPixels(); i++)//parcourt de tous les pixels de l'image
			if (mask(i) == 0) //si le pixel est noir
			{
				this->operator()(i)[0] = im(i);  //conservation de la valeur de gris du pixel original
				this->operator()(i)[1] = im(i);
				this->operator()(i)[2] = im(i);
			}
			else  //zone à masquer
			{
				this->operator()(i)[0] = R; //pixel coloré avec les valeurs RGB choisies
				this->operator()(i)[1] = G; 
				this->operator()(i)[2] = B;
			}
	}
}


// masquage avec image binaire (exemple des contours)
CImageCouleur::CImageCouleur(const CImageCouleur& im, const CImageNdg& mask, int R, int G, int B)
{
	this->m_iHauteur = im.lireHauteur();
	this->m_iLargeur = im.lireLargeur();
	this->m_sNom = im.lireNom() + "Mask";
	this->m_pucData = NULL;
	this->m_ppucPixel = NULL;

	if (im.lireNbPixels() > 0) {
		this->m_pucData = new unsigned char[im.lireHauteur()*im.lireLargeur() * 3];
		this->m_ppucPixel = new unsigned char*[im.lireHauteur()*im.lireLargeur()];
		for (int i = 0; i<im.lireHauteur()*im.lireLargeur(); i++)
			this->m_ppucPixel[i] = &this->m_pucData[3 * i];

		for (int i = 0; i < im.lireNbPixels(); i++)
			if (mask(i) == 0)
			{
				this->operator()(i)[0] = im(i)[0];
				this->operator()(i)[1] = im(i)[1];
				this->operator()(i)[2] = im(i)[2];
			}
			else
			{
				this->operator()(i)[0] = R;
				this->operator()(i)[1] = G;
				this->operator()(i)[2] = B;
			}
	}
}


CImageCouleur::~CImageCouleur() 
{

	if (this->m_ppucPixel) {
		delete[] this->m_ppucPixel;   // libération de la mémoire
		this->m_ppucPixel = NULL;    // pointeur sur NULL
	}
	if (this->m_pucData) {
		delete[] this->m_pucData;   // libération de la mémoire
		this->m_pucData = NULL;	// pointeur sur NULL
	}
}

void CImageCouleur::sauvegarde(const std::string file) {

	BITMAPFILEHEADER header;
	BITMAPINFOHEADER infoHeader;

	if (this->m_ppucPixel) {   // si l'image n'est pas vide
		std::string nomFichier = "res/ "; // force sauvegarde dans répertoire res (doit exister)

		if (file.empty())
			nomFichier += this->lireNom() + ".bmp"; 
		else
			nomFichier += file + ".bmp";

		std::ofstream f(nomFichier.c_str(),std::ios::binary);  //ouverture du fichier en mode binaire pour écrire dedans
		if (f.is_open()) {
			int complement = (((this->m_iLargeur*3-1)/4) + 1)*4 - this->m_iLargeur*3;

			header.bfType = MAGIC_NUMBER_BMP; //calcul et écriture des différentzs champs des entêtes bmp , définit le type du fichier à BM
			f.write((char*)&header.bfType, 2); //écriture des 2 premiers octets du fichier , type du fichier= BMP
			header.bfOffBits = 14 * sizeof(char) + 40 * sizeof(char);//offset de démarrage des données de l'image, 14 octets pour l'entête et 40 pour l'infoHeader
			header.bfSize = header.bfOffBits + (complement + lireLargeur())*lireHauteur()*sizeof(char);//taille totale du fichier
			f.write((char*)&header.bfSize, 4);//taille de l'entête, écriture de la taille du fichier dans le fichier
			header.bfReserved1 = 0;
			f.write((char*)&header.bfReserved1, 2);//écriture des champs réservés
			header.bfReserved2 = 0;
			f.write((char*)&header.bfReserved2, 2);//écriture des champs réservés
			f.write((char*)&header.bfOffBits, 4);  //ecriture de la taille de l'offset dans le fichier	


			//définition et écriture des informations de l'image
			infoHeader.biSize = 40 * sizeof(char); //taille de l'infoHeader
			f.write((char*)&infoHeader.biSize, 4);
			infoHeader.biWidth = this->m_iLargeur;
			f.write((char*)&infoHeader.biWidth, 4);
			infoHeader.biHeight = this->m_iHauteur;
			f.write((char*)&infoHeader.biHeight, 4);
			infoHeader.biPlanes = 3;
			f.write((char*)&infoHeader.biPlanes, 2);
			infoHeader.biBitCount = 24;
			f.write((char*)&infoHeader.biBitCount, 2);
			infoHeader.biCompression = 0; // pas de compression
			f.write((char*)&infoHeader.biCompression, 4);
			infoHeader.biSizeImage = this->lireNbPixels()*3;
			f.write((char*)&infoHeader.biSizeImage, 4);
			infoHeader.biXPelsPerMeter = 0;
			f.write((char*)&infoHeader.biXPelsPerMeter, 4);
			infoHeader.biYPelsPerMeter = 0;
			f.write((char*)&infoHeader.biYPelsPerMeter, 4);
			infoHeader.biClrUsed = 0;
			f.write((char*)&infoHeader.biClrUsed, 4);
			infoHeader.biClrImportant = 0;
			f.write((char*)&infoHeader.biClrImportant, 4);

			for (int i= this->lireHauteur()-1; i >= 0; i--) { //m_ppucPixel: tableau 2d stockant les données des pixels de l'image
				for (int j=0;j<this->lireLargeur();j++) {
					f.write((char*)&this->m_ppucPixel[i*this->lireLargeur()+j][2],sizeof(char)); //attention ordre d'écriture BGR
					f.write((char*)&this->m_ppucPixel[i*this->lireLargeur()+j][1],sizeof(char)); 
					f.write((char*)&this->m_ppucPixel[i*this->lireLargeur()+j][0],sizeof(char));
				}	
				// gérer multiple de 32 bits
				char inutile;
				for (int k=0; k< complement; k++)
					f.write((char*)&inutile,sizeof(char)); //chaque ligne de données de l'image doit être multiple de 32 bits
			}
		f.close();
		}
		else
			throw std::string("Impossible de creer le fichier de sauvegarde !");
	}
	else
		throw std::string("Pas de donnee a sauvegarder !");
}

CImageCouleur& CImageCouleur::operator=(const CImageCouleur& im) 
{

	if (&im == this)            //vérification d'auto-affectation
		return *this;

	this->m_iHauteur = im.lireHauteur();        //copie des propriétés simples
	this->m_iLargeur = im.lireLargeur();
	this->m_sNom     = im.lireNom();

	if (this->m_pucData)    //nettoyage de la mémoire existante si déjà allouée
		delete[] this->m_pucData;
	if (this->m_ppucPixel) 
		delete[] this->m_ppucPixel;

	this->m_pucData = new unsigned char[im.lireHauteur()*im.lireLargeur()*3]; //allocation de la mémoire pour stocker les données des pixels en couleur (données RGB pour chaque pixel)
	this->m_ppucPixel = new unsigned char*[im.lireHauteur()*im.lireLargeur()];
	for (int i=0;i<im.lireHauteur()*im.lireLargeur();i++) //initialisation du tableau de pixels
		this->m_ppucPixel[i] = &this->m_pucData[3*i];

	memcpy(this->m_pucData,im.m_pucData,im.lireNbPixels()*3); //copie des données des pixels

return *this; //retour de l'objet courant
}

// histogramme  couleur, plan par plan
// organisé en vecteur progressif à savoir 3*i -> R ou H,3*i+1 -> G ou S et 3*i+2 -> B ou V
std::vector<unsigned long> CImageCouleur::histogramme(bool enregistrementCSV) {
	std::vector<unsigned long> h;

	h.resize(3*256); // 3 plans 

	for (int i=0;i<this->lireNbPixels();i++) { 
		h[3*this->operator()(i)[0]] += 1L; //valeur de chaque composante RGB incrémentée pour alimenter l'histogramme
		h[3*this->operator()(i)[1]+1] += 1L;
		h[3*this->operator()(i)[2]+2] += 1L;
	}
	if (enregistrementCSV) {       //enregistrement optionnel de l'histogramme dans un fichier csv
		std::string fichier = "res/" + this->lireNom() + ".csv";
		std::ofstream f (fichier.c_str());

		if (!f.is_open())
			std::cout << "Impossible d'ouvrir le fichier en ecriture !" << std::endl;
		else 
		{           //ecriture des données de l'histogramme dans le fichier csv
			for (int i=0;i<256;i++)
				f << h[3*i] << " ; " << h[3*i+1] << " ; " << h[3*i+2] << " ; " << std::endl;
		}
		f.close();
	}

	return h;                 //retour de l'histogramme
}

// gestion des plans
CImageNdg CImageCouleur::plan(int choix, double poidsRouge, double poidsVert, double poidsBleu) { // 0 -> R ou H, 1 -> V ou S, 2 -> B ou V et 3 -> luminance d'où les poids fct de l'illuminant
	CImageNdg out(this->lireHauteur(),this->lireLargeur());   //création d'une image en ndg pour la sortie
	out.ecrireNom(this->lireNom() + std::to_string(choix));   //modification du nom de l'image, i.e on lui ajoute le numéro du plan choisi
	out.choixPalette("grise"); // par défaut	
	out.ecrireBinaire(false);  // par défaut

	switch(choix)  //choix du plan
	{
	case 0 :                                                 //extraction du canal rouge
		for (int i=0;i<this->lireNbPixels();i++)		     //parcours de tous les pixels de l'image
			out(i) = this->operator()(i)[0];                 //copie de la valeur de la composante rouge du pixel dans l'image en ndg
		break;
	case 1 :
		for (int i=0;i<this->lireNbPixels();i++)             //extraction du canal vert
			out(i) = this->operator()(i)[1];                 //copie de la valeur de la composante verte du pixel dans l'image en ndg
		break;
	case 2 : 
		for (int i=0;i<this->lireNbPixels();i++)             //extraction du canal bleu
			out(i) = this->operator()(i)[2];                 //copie de la valeur de la composante bleue du pixel dans l'image en ndg
		break;
	case 3:                                                //calcul de la luminance
		for (int i=0;i<this->lireNbPixels();i++)
			out(i) = (unsigned char)(poidsRouge*(double)this->operator()(i)[0] + poidsVert*(double)this->operator()(i)[1] + poidsBleu*(double)this->operator()(i)[2]); //application de la formule de calcul de la luminance avec les poids choisis
	}
	return out;           //retour de l'image en ndg
}

// mise à jour d'un plan particulier défini par une image en Ndg et 0,1 ou 2
CImageCouleur& CImageCouleur::miseAJourPlan(int choix, const CImageNdg& plan) 
{

	for (int i=0;i<this->lireNbPixels();i++)
		this->operator()(i)[choix] = plan(i); //accès au pixel i du plan choisi et copie de la valeur du pixel de l'image en ndg

		return *this; //retour de l'objet courant
}

// conversion espace HSV sur [0-255] pour chaque plan
CImageCouleur CImageCouleur::conversion(const std::string methode) const 
{

	CImageCouleur out(this->lireHauteur(),this->lireLargeur(),0,0,0); //création d'une image en couleur pour la sortie,initialisation de toutes ses composantes de couleur (R,G et B) à 0
	out.ecrireNom(this->lireNom() + "HSV"); //modification du nom de l'image, i.e on lui ajoute HSV

	if (methode.compare("HSV") == 0)   //si on est effectivement dans le cas d'une conversion RGB->HSV
	{
		unsigned char rgb_min, rgb_max;	//initialisation des variables

		for (int i=0;i<this->lireNbPixels();i++) //parcours de tous les pixels de l'image originale
		{
			rgb_min = MIN3(this->operator()(i)[0], this->operator()(i)[1], this->operator()(i)[2]); //valeur minimale des composantes RGB du pixel i
			rgb_max = MAX3(this->operator()(i)[0], this->operator()(i)[1], this->operator()(i)[2]); //valeur maximale des composantes RGB du pixel i

			//cette composante dominante détermine la région du cercle chromatique dans laquelle se trouve la couleur du pixel i
			//la teinte dans l'espace HSV est un angle sur le cercle chromatique, mais ici elle est représentée sur [0-255] pour correspondre au format de couleur numérique standard

			if (rgb_max != rgb_min)
			{
				if (rgb_max == this->operator()(i)[0]) //si la composante dominante est le rouge
					//la teinte sera quelque part entre 0 et 85 sur [0-255] (0° et 60° sur le cercle chromatique) (rouge->jaune)
				{
					out(i)[0] = 0 + 43*(this->operator()(i)[1] - this->operator()(i)[2])/(rgb_max - rgb_min); //calcul de la teinte sur [0-255]
				}
				else 
					if (rgb_max == this->operator()(i)[1]) //si la composante dominante est le vert
						//la teinte sera quelque part entre 85 et 170 sur [0-255] (60° et 120° sur le cercle chromatique) (jaune->cyan)
					{
						out(i)[0] = 85 + 43*(this->operator()(i)[2] - this->operator()(i)[0])/(rgb_max - rgb_min);//calcul de la teinte sur [0-255]
					}
					else   //si la composante dominante est le bleu,
						//la teinte sera quelque part entre 171 et 255 sur [0-255] (120° et 180° sur le cercle chromatique) (cyan->rouge)
					{
						out(i)[0] = 171 + 43*(this->operator()(i)[0] - this->operator()(i)[1])/(rgb_max - rgb_min);//calcul de la teinte sur [0-255]
					}
			}
			if (rgb_max != 0) //si la valeur maximale des composantes RGB du pixel i est non nulle
				out(i)[1] = rgb_max-rgb_min;   //calcul de la saturation sur [0-255]: différence entre la valeur maximale et la valeur minimale des composantes RGB du pixel i
			out(i)[2] = rgb_max;// value V sur [0-255]: valeur maximale des composantes RGB du pixel i
		}
	}
	return out;
}

// transformation
CImageCouleur CImageCouleur::transformation(const std::string methode) 
{

	CImageCouleur out(this->lireHauteur(), this->lireLargeur()); //création d'une image en couleur pour la sortie

	if (methode.compare("complement") == 0) //si on est effectivement dans le cas d'une transformation en complément
	{
		//on passe par une image en ndg pour appliquer la transformation

		out.m_sNom = this->lireNom() + "TComp";	//modification du nom de l'image, i.e on lui ajoute TransformationComplement
		CImageNdg planR = this->plan(0).transformation("complement"); //transformation en complément du plan rouge
		CImageNdg planG = this->plan(1).transformation("complement"); //transformation en complément du plan vert
		CImageNdg planB = this->plan(2).transformation("complement"); //transformation en complément du plan bleu
		out.miseAJourPlan(0, planR); //mise à jour du plan rouge de l'image de sortie
		out.miseAJourPlan(1, planG); //mise à jour du plan vert de l'image de sortie
		out.miseAJourPlan(2, planB); //mise à jour du plan bleu de l'image de sortie
	}
	else
		if (methode.compare("expansion") == 0) //si on est effectivement dans le cas d'une transformation par expansion
		{
			out.m_sNom = this->lireNom() + "TExp";//modification du nom de l'image, i.e on lui ajoute TransformationExpansion
			CImageNdg planR = this->plan(0).transformation("expansion");//transformation par expansion du plan rouge
			CImageNdg planG = this->plan(1).transformation("expansion");//transformation par expansion du plan vert
			CImageNdg planB = this->plan(2).transformation("expansion");//transformation par expansion du plan bleu
			out.miseAJourPlan(0, planR);//mise à jour du plan rouge de l'image de sortie
			out.miseAJourPlan(1, planG);//mise à jour du plan vert de l'image de sortie
			out.miseAJourPlan(2, planB);//mise à jour du plan bleu de l'image de sortie
		}
		else
			if (methode.compare("egalisation") == 0) 
			{
				out.m_sNom = this->lireNom() + "TEga";     //modification du nom de limage, i.e on lui ajoute TransformationEgalisation
				CImageNdg planR = this->plan(0).transformation("egalisation");   //transformation par égalisation du plan rouge
				CImageNdg planG = this->plan(1).transformation("egalisation");   //transformation par égalisation du plan vert
				CImageNdg planB = this->plan(2).transformation("egalisation");  //transformation par égalisation du plan bleu
				out.miseAJourPlan(0, planR); //mise à jour du plan rouge de l'image de sortie
				out.miseAJourPlan(1, planG); //mise à jour du plan vert de l'image de sortie
				out.miseAJourPlan(2, planB); //mise à jour du plan bleu de l'image de sortie
			}
	return out;
}


