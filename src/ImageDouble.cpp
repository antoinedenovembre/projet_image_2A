#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <limits>
#include <stack>
#include <algorithm>

#include "ImageDouble.h"

#define PI 3.14159265358979323846

// constructeurs et destructeur
CImageDouble::CImageDouble() 
{

	this->m_iHauteur  = 0;
	this->m_iLargeur  = 0;
	this->m_sNom      = "vide";
	this->m_vMin      = 0;
	this->m_vMax      = 0;
	this->m_pucPixel  = NULL;
}

CImageDouble::CImageDouble(int hauteur, int largeur) 
{

	this->m_iHauteur = hauteur;
	this->m_iLargeur = largeur;
	this->m_sNom     = "inconnu";
	this->m_vMin     = 0;
	this->m_vMax     = 0;

	this->m_pucPixel = new double[hauteur*largeur];
	for (int i=0;i<hauteur*largeur;i++)
		this->m_pucPixel[i] = 0;
}

CImageDouble::CImageDouble(const CImageDouble& im) 
{

	this->m_iHauteur = im.lireHauteur();
	this->m_iLargeur = im.lireLargeur();
	this->m_sNom = im.lireNom();
	this->m_vMax = im.lireMax();
	this->m_vMin = im.lireMin();
	this->m_pucPixel = NULL;

	if (im.m_pucPixel != NULL) {
		this->m_pucPixel = new double[im.lireNbPixels()];
		memcpy(this->m_pucPixel, im.m_pucPixel, im.lireNbPixels()*sizeof(double));
	}
}

CImageDouble::~CImageDouble() {

	if (this->m_pucPixel) {
		delete[] this->m_pucPixel;
		this->m_pucPixel = NULL;
	}
}

CImageDouble::CImageDouble(const CImageNdg& im, const std::string& methode) {

	this->m_iHauteur = im.lireHauteur();
	this->m_iLargeur = im.lireLargeur();

	this->m_pucPixel = new double[im.lireNbPixels()];
	if (methode.compare("normalise") == 0) {
		this->m_sNom = im.lireNom() + "DN";
		this->m_vMin = 0;
		this->m_vMax = 1;
		for (int i = 0; i < this->lireNbPixels(); i++)
			this->operator()(i) = (double)im(i) / 255;
	}
	else
		if (methode.compare("cast") == 0) {
			this->m_sNom = im.lireNom() + "DC";
			this->m_vMin = 255;
			this->m_vMax = 0;
			for (int i = 0; i < this->lireNbPixels(); i++)
			{
				this->operator()(i) = (double)im(i);
				if (this->operator()(i) > this->m_vMax)
					this->m_vMax = this->operator()(i);
				if (this->operator()(i) < this->m_vMin)
					this->m_vMin = this->operator()(i);
			}
		}
		else
			if (methode.compare("integrale1") == 0) 
			{
				this->m_sNom = im.lireNom() + "DI1";

				CImageDouble s(im.lireHauteur(), im.lireLargeur());

				// première ligne
				s(0) = (double)im(0, 0);
				this->operator()(0) = (double)im(0, 0);
				this->ecrireMin((double)im(0, 0));

				for (int j = 1; j < im.lireLargeur(); j++) {
					s(j) = s(j - 1) + (double)im(0, j);
					this->operator()(j) = this->operator()(j - 1) + (double)im(0, j);
				}

				// le reste
				for (int i = 1; i < im.lireHauteur(); i++) {
					s(i, 0) = (double)im(i, 0);
					this->operator()(i, 0) = this->operator()(i - 1, 0) + (double)im(i, 0);
					for (int j = 1; j < im.lireLargeur(); j++) {
						s(i, j) = s(i, j - 1) + (double)im(i, j);
						this->operator()(i, j) = this->operator()(i - 1, j) + s(i, j);
					}
				}

				this->ecrireMax(this->operator()(this->lireNbPixels() - 1));
			}
			else if (methode.compare("integrale2") == 0) {
				this->m_sNom = im.lireNom() + "DI2";
				CImageDouble s(im.lireHauteur(), im.lireLargeur());

				// première ligne
				s(0) = (double)im(0, 0)*(double)im(0, 0);
				this->operator()(0) = (double)im(0, 0)*(double)im(0, 0);
				this->ecrireMin(this->operator()(0));

				for (int j = 1; j < im.lireLargeur(); j++) 
				{
					s(j) = s(j - 1) + (double)im(0, j)*(double)im(0, j);
					this->operator()(j) = this->operator()(j - 1) + (double)im(0, j)*(double)im(0, j);
				}

				// le reste
				for (int i = 1; i < im.lireHauteur(); i++) {
					s(i, 0) = (double)im(i, 0)* (double)im(i, 0);
					this->operator()(i, 0) = this->operator()(i - 1, 0) + (double)im(i, 0)* (double)im(i, 0);
					for (int j = 1; j < im.lireLargeur(); j++) {
						s(i, j) = s(i, j - 1) + (double)im(i, j)*(double)im(i, j);
						this->operator()(i, j) = this->operator()(i - 1, j) + s(i, j);
					}
				}

				this->ecrireMax(this->operator()(this->lireNbPixels() - 1));
			}
}

CImageDouble& CImageDouble::operator=(const CImageDouble& im) {

	if (&im == this)
		return *this;

	this->m_iHauteur = im.lireHauteur();
	this->m_iLargeur = im.lireLargeur();
	this->m_sNom = im.lireNom();
	this->m_vMax = im.lireMax();
	this->m_vMin = im.lireMin();

	if (this->m_pucPixel)
		delete[] this->m_pucPixel;
	this->m_pucPixel = new double[im.lireNbPixels()];

	if (im.m_pucPixel != NULL)
		memcpy(this->m_pucPixel, im.m_pucPixel, im.lireNbPixels()*sizeof(double));

	return *this;
}

// distance au fond
CImageDouble CImageDouble::distance(std::string eltStructurant, double valBord) 
{
	// distance au fond
	// gestion du bord : 0 ou autre valeur valant max des float

	CImageDouble out(this->lireHauteur(), this->lireLargeur());
	out.ecrireNom(this->lireNom() + "DF");
	out.ecrireMax(DBL_MIN);
	out.ecrireMin(DBL_MAX);

	CImageDouble agrandie(this->lireHauteur() + 2, this->lireLargeur() + 2);
	// gestion des bords ajoutés
	if (valBord != 0) {
		for (int i = 0; i<agrandie.lireHauteur(); i++) {
			agrandie(i, 0) = valBord;
			agrandie(i, agrandie.lireLargeur() - 1) = valBord;
		}
		for (int j = 0; j<agrandie.lireLargeur(); j++) {
			agrandie(0, j) = valBord;
			agrandie(agrandie.lireHauteur() - 1, j) = valBord;
		}
	}

	// coeur image
	for (int i = 0; i<this->lireHauteur(); i++)
		for (int j = 0; j<this->lireLargeur(); j++) {
			agrandie(i + 1, j + 1) = (this->operator()(i, j) > 0) ? (double)INT_MAX-1 : 0;
		}

	if (eltStructurant.compare("V4") == 0) {
		// parcours avant
		for (int i = 1; i<agrandie.lireHauteur() - 1; i++)
			for (int j = 1; j<agrandie.lireLargeur() - 1; j++) {
				double pixel = agrandie(i, j);
				pixel = std::min(pixel, agrandie(i - 1, j) + 1);
				pixel = std::min(pixel, agrandie(i, j - 1) + 1);
				agrandie(i, j) = pixel;
			}
		for (int i = agrandie.lireHauteur() - 2; i >= 1; i--)
			for (int j = agrandie.lireLargeur() - 2; j >= 1; j--) {
				double pixel = agrandie(i, j);
				pixel = std::min(pixel, agrandie(i + 1, j) + 1);
				pixel = std::min(pixel, agrandie(i, j + 1) + 1);
				agrandie(i, j) = pixel;
			}
		// conservation du centre
		for (int i = 1; i<agrandie.lireHauteur() - 1; i++)
			for (int j = 1; j<agrandie.lireLargeur() - 1; j++) {
				out(i - 1, j - 1) = agrandie(i, j);
			}
	}
	else {
		// parcours avant
		for (int i = 1; i<agrandie.lireHauteur() - 1; i++)
			for (int j = 1; j<agrandie.lireLargeur() - 1; j++) {
				double pixel = agrandie(i, j);
				pixel = std::min(pixel, agrandie(i - 1, j) + 1);
				pixel = std::min(pixel, agrandie(i, j - 1) + 1);
				pixel = std::min(pixel, agrandie(i - 1, j - 1) + 1);
				pixel = std::min(pixel, agrandie(i - 1, j + 1) + 1);
				agrandie(i, j) = pixel;
			}
		for (int i = agrandie.lireHauteur() - 2; i >= 1; i--)
			for (int j = agrandie.lireLargeur() - 2; j >= 1; j--) {
				double pixel = agrandie(i, j);
				pixel = std::min(pixel, agrandie(i + 1, j) + 1);
				pixel = std::min(pixel, agrandie(i, j + 1) + 1);
				pixel = std::min(pixel, agrandie(i + 1, j + 1) + 1);
				pixel = std::min(pixel, agrandie(i + 1, j - 1) + 1);
				agrandie(i, j) = pixel;
			}
		// conservation du centre
		for (int i = 1; i<agrandie.lireHauteur() - 1; i++)
			for (int j = 1; j<agrandie.lireLargeur() - 1; j++) {
				out(i - 1, j - 1) = agrandie(i, j);
				if (out(i - 1, j - 1) < out.lireMin())
					out.ecrireMin(out(i - 1, j - 1));
				if (out(i - 1, j - 1) > out.lireMax())
					out.ecrireMax(out(i - 1, j - 1));
			}
	}

	return out;
}

// conversion entre types
CImageNdg CImageDouble::toNdg(const std::string& methode) {

	CImageNdg out(this->lireHauteur(), this->lireLargeur());
	out.ecrireBinaire(false);
	out.choixPalette("grise");
	out.ecrireNom(this->lireNom() + "2NDG");

	if (methode.compare("defaut") == 0) {
		for (int i = 0; i < this->lireNbPixels(); i++)
			if (this->operator()(i) < 0)
				out(i) = 0;
			else
				if (this->operator()(i) > 256)
					out(i) = 255;
				else
					out(i) = (unsigned char)this->operator()(i);
	}
	else
		if (methode.compare("expansion") == 0) {
			double a = 255 / (this->lireMax() - this->lireMin());
			double b = -a*this->lireMin();

			for (int i = 0; i < this->lireNbPixels(); i++)
				out(i) = (unsigned char)(a*this->operator()(i)+b);
		}

	return(out);
}

// vecteur gradient
CImageDouble CImageDouble::vecteurGradient(const std::string& axe) 
{
	CImageDouble out(this->lireHauteur(), this->lireLargeur());

	if (axe.compare("norme") == 0)
	{
		out.ecrireNom(this->lireNom() + "NVG");
		double vMin = sqrt(2) * 255;
		double vMax = 0;

		CImageDouble agrandie(this->lireHauteur() + 2, this->lireLargeur() + 2);

		// gestion des bords et des coins
		int pix;
		agrandie(0, 0) = this->operator()(0, 0);
		agrandie(0, agrandie.lireLargeur() - 1) = this->operator()(0, this->lireLargeur() - 1);
		for (pix = 1; pix < agrandie.lireLargeur() - 1; pix++) {
			agrandie(0, pix) = this->operator()(0, pix - 1);
			agrandie(agrandie.lireHauteur() - 1, pix) = this->operator()(this->lireHauteur() - 1, pix - 1);
		}
		agrandie(agrandie.lireHauteur() - 1, 0) = this->operator()(this->lireHauteur() - 1, 0);
		agrandie(agrandie.lireHauteur() - 1, agrandie.lireLargeur() - 1) = this->operator()(this->lireHauteur() - 1, this->lireLargeur() - 1);
		for (pix = 1; pix < agrandie.lireHauteur() - 1; pix++) {
			agrandie(pix, 0) = this->operator()(pix - 1, 0);
			agrandie(pix, agrandie.lireLargeur() - 1) = this->operator()(pix - 1, this->lireLargeur() - 1);
		}

		// gestion du coeur
		for (int i = 0; i < this->lireHauteur(); i++)
			for (int j = 0; j < this->lireLargeur(); j++) {
				agrandie(i + 1, j + 1) = this->operator()(i, j);
			}

		// passage des noyaux

		for (int i = 1; i < agrandie.lireHauteur() - 1; i++)
			for (int j = 1; j < agrandie.lireLargeur() - 1; j++)
			{
				double vx = agrandie(i + 1, j) - agrandie(i - 1, j);
				double vy = agrandie(i, j + 1) - agrandie(i, j - 1);

				out(i - 1, j - 1) = sqrt((vx*vx) + (vy*vy));
				if (out(i - 1, j - 1) < vMin)
					vMin = out(i - 1, j - 1);
				if (out(i - 1, j - 1) > vMax)
					vMax = out(i - 1, j - 1);
			}

		out.ecrireMin(vMin);
		out.ecrireMax(vMax);
	}
	else
		if (axe.compare("angle") == 0)
		{
			out.ecrireNom(this->lireNom() + "AVG");

			CImageDouble agrandie(this->lireHauteur() + 2, this->lireLargeur() + 2);

			// gestion des bords et des coins
			int pix;
			agrandie(0, 0) = this->operator()(0, 0);
			agrandie(0, agrandie.lireLargeur() - 1) = this->operator()(0, this->lireLargeur() - 1);
			for (pix = 1; pix < agrandie.lireLargeur() - 1; pix++) {
				agrandie(0, pix) = this->operator()(0, pix - 1);
				agrandie(agrandie.lireHauteur() - 1, pix) = this->operator()(this->lireHauteur() - 1, pix - 1);
			}
			agrandie(agrandie.lireHauteur() - 1, 0) = this->operator()(this->lireHauteur() - 1, 0);
			agrandie(agrandie.lireHauteur() - 1, agrandie.lireLargeur() - 1) = this->operator()(this->lireHauteur() - 1, this->lireLargeur() - 1);
			for (pix = 1; pix < agrandie.lireHauteur() - 1; pix++) {
				agrandie(pix, 0) = this->operator()(pix - 1, 0);
				agrandie(pix, agrandie.lireLargeur() - 1) = this->operator()(pix - 1, this->lireLargeur() - 1);
			}

			// gestion du coeur
			for (int i = 0; i < this->lireHauteur(); i++)
				for (int j = 0; j < this->lireLargeur(); j++) {
					agrandie(i + 1, j + 1) = this->operator()(i, j);
				}

			// passage des noyaux

			for (int i = 1; i < agrandie.lireHauteur() - 1; i++)
				for (int j = 1; j < agrandie.lireLargeur() - 1; j++)
				{
					double vx = agrandie(i + 1, j) - agrandie(i - 1, j);
					double vy = agrandie(i, j + 1) - agrandie(i, j - 1);
					out(i - 1, j - 1) = atan2(vy, vx) * 180 / PI;
				}

			// fixer intervall -PI.. PI soit -180 .. 180 en degres
			out.ecrireMin(-180); 
			out.ecrireMax(180);
		}

	return out;
}

// filtrage : moyen ou gaussien (approches par vecteur et transposée plus rapide)
CImageDouble CImageDouble::filtrage(const std::string& methode, int N, double sigma) {

	CImageDouble out(this->lireHauteur(), this->lireLargeur());
	out.m_vMax = DBL_MIN;
	out.m_vMin = DBL_MAX;

	if (methode.compare("moyen") == 0) {
		out.m_sNom = this->lireNom() + "FMo";
		int nbBords = N / 2;

		CImageDouble agrandie(this->lireHauteur() + nbBords * 2, this->lireLargeur() + nbBords * 2);

		// gestion du coeur
		for (int i = 0; i < this->lireHauteur(); i++)
			for (int j = 0; j < this->lireLargeur(); j++) {
				agrandie(i + nbBords, j + nbBords) = this->operator()(i, j);
			}

		// gestion des bords
		for (int pix = 0; pix < agrandie.lireLargeur(); pix++) {
			for (int t = nbBords - 1; t >= 0; t--)
				agrandie(t, pix) = agrandie(nbBords, pix);
			for (int t = agrandie.lireHauteur() - 1; t >= agrandie.lireHauteur() - 1 - nbBords; t--)
				agrandie(t, pix) = agrandie(agrandie.lireHauteur() - 1 - nbBords, pix);
		}
		for (int pix = 0; pix < agrandie.lireHauteur(); pix++) {
			for (int t = nbBords - 1; t >= 0; t--)
				agrandie(pix, t) = agrandie(pix, nbBords);
			for (int t = agrandie.lireLargeur() - 1; t >= agrandie.lireLargeur() - 1 - nbBords; t--)
				agrandie(pix, t) = agrandie(pix, agrandie.lireLargeur() - 1 - nbBords);
		}

		CImageDouble agrandie2 = agrandie;

		// colonnes
		for (int i = nbBords; i < agrandie.lireHauteur() - nbBords; i++)
			for (int j = nbBords; j < agrandie.lireLargeur() - nbBords; j++) {
				double somme = 0;
				double moy = 0;

				for (int k = -nbBords; k <= nbBords; k++) {
					moy += (double)agrandie(i - k, j);
					somme += (double)1;
				}
				agrandie2(i, j) = moy / somme;
			}
		// lignes
		for (int i = nbBords; i < agrandie.lireHauteur() - nbBords; i++)
			for (int j = nbBords; j < agrandie.lireLargeur() - nbBords; j++) {
				double somme = 0;
				double moy = 0;

				for (int l = -nbBords; l <= nbBords; l++) {
					moy += (double)agrandie2(i, j - l);
					somme += (double)1;
				}
				agrandie(i, j) = (moy / somme);
			}
		// image out
		for (int i = nbBords; i < agrandie.lireHauteur() - nbBords; i++)
			for (int j = nbBords; j < agrandie.lireLargeur() - nbBords; j++)
			{
				out(i - nbBords, j - nbBords) = agrandie(i, j);
				if (out(i - nbBords, j - nbBords) < out.lireMin())
					out.ecrireMin(out(i - nbBords, j - nbBords));
				if (out(i - nbBords, j - nbBords) > out.lireMax())
					out.ecrireMax(out(i - nbBords, j - nbBords));
			}
	}
	else
		if (methode.compare("gaussien") == 0)
		{
			out.m_sNom = this->lireNom() + "FGa";
			// définition du noyau
			double noyau[50]; // taille maxi pour optimisation 

			double somme = 0; // normalisation
			for (int i = 0; i < N; i++)
			{
				noyau[i] = exp(-((i - N / 2)*(i - N / 2)) / (2 * sigma*sigma));
				somme += noyau[i];
			}

			// filtrage
			int nbBords = N / 2;

			CImageDouble agrandie(this->lireHauteur() + nbBords * 2, this->lireLargeur() + nbBords * 2);

			// gestion du coeur
			for (int i = 0; i < this->lireHauteur(); i++)
				for (int j = 0; j < this->lireLargeur(); j++) {
					agrandie(i + nbBords, j + nbBords) = this->operator()(i, j);
				}

			// gestion des bords
			for (int pix = 0; pix < agrandie.lireLargeur(); pix++) {
				for (int t = nbBords - 1; t >= 0; t--)
					agrandie(t, pix) = agrandie(nbBords, pix);
				for (int t = agrandie.lireHauteur() - 1; t >= agrandie.lireHauteur() - 1 - nbBords; t--)
					agrandie(t, pix) = agrandie(agrandie.lireHauteur() - 1 - nbBords, pix);
			}
			for (int pix = 0; pix < agrandie.lireHauteur(); pix++) {
				for (int t = nbBords - 1; t >= 0; t--)
					agrandie(pix, t) = agrandie(pix, nbBords);
				for (int t = agrandie.lireLargeur() - 1; t >= agrandie.lireLargeur() - 1 - nbBords; t--)
					agrandie(pix, t) = agrandie(pix, agrandie.lireLargeur() - 1 - nbBords);
			}

			CImageDouble agrandie2 = agrandie;

			// colonnes
			for (int i = nbBords; i < agrandie.lireHauteur() - nbBords; i++)
				for (int j = nbBords; j < agrandie.lireLargeur() - nbBords; j++) {
					double somme = 0;
					double moy = 0;

					for (int k = -nbBords; k <= nbBords; k++) {
						moy += (double)agrandie(i - k, j)*noyau[k + nbBords];
						somme += noyau[k + nbBords];
					}
					agrandie2(i, j) = moy / somme;
				}
			// lignes
			for (int i = nbBords; i < agrandie.lireHauteur() - nbBords; i++)
				for (int j = nbBords; j < agrandie.lireLargeur() - nbBords; j++) {
					double somme = 0;
					double moy = 0;

					for (int l = -nbBords; l <= nbBords; l++) {
						moy += (double)agrandie2(i, j - l)*noyau[l + nbBords];
						somme += noyau[l + nbBords];
					}
					agrandie(i, j) = (moy / somme);
				}
			// image out
			for (int i = nbBords; i < agrandie.lireHauteur() - nbBords; i++)
				for (int j = nbBords; j < agrandie.lireLargeur() - nbBords; j++)
				{
					out(i - nbBords, j - nbBords) = agrandie(i, j);
					if (out(i - nbBords, j - nbBords) < out.lireMin())
						out.ecrireMin(out(i - nbBords, j - nbBords));
					if (out(i - nbBords, j - nbBords) > out.lireMax())
						out.ecrireMax(out(i - nbBords, j - nbBords));
				}
		}

	return out;
}

std::vector<CImageDouble> CImageDouble::pyramide(int hauteur, int tailleFiltre, double sigma)
{
	std::vector<CImageDouble> burt;

	// propagation des min,max du niveau initial aux autres niveaux, sinon va modifier la dynamique des niveaux
	burt.resize(hauteur);
	burt.at(0) = *this;
	burt.at(0).ecrireNom(this->lireNom() + std::to_string(0));

	for (int niv = 1; niv < hauteur; niv++)
	{
		// filtrage gaussien qui améliore les résultats avant sous-échantillonage
		CImageDouble niveau = burt.at(niv - 1).filtrage("gaussien", 5, 1);
		CImageDouble inter(niveau.lireHauteur() / 2, niveau.lireLargeur() / 2);

		inter.ecrireMax(this->lireMax()); // pour ne pas changer la dynamique entre niveaux
		inter.ecrireMin(this->lireMin());
		inter.ecrireNom(this->lireNom() + std::to_string(niv));

		for (int i = 0; i < inter.lireHauteur(); i++)
			for (int j = 0; j < inter.lireLargeur(); j++)
				inter(i, j) = (niveau(2 * i, 2 * j) + niveau(2 * i + 1, 2 * j) + niveau(2 * i, 2 * j + 1) + niveau(2 * i + 1, 2 * j + 1)) / 4;

		burt.at(niv) = inter;
	}

	return burt;
}

// plan Hough extraction lignes


CImageDouble CImageDouble::maxiLocaux(int N, int M) 
{

	CImageDouble out(this->lireHauteur(), this->lireLargeur());

	int ns2 = N / 2;
	int ms2 = M / 2;

	out.ecrireNom(this->lireNom() + "ML");
	for (int i = 0; i < this->lireHauteur(); i++)
		for (int j = 0; j < this->lireLargeur(); j++)
			if (this->operator()(i, j) > 0) {	// test si le pixel existe i-taille/2
				int dk = std::max(0, i - ns2);
				int fk = std::min(i + ns2, this->lireHauteur() - 1);
				int dl = std::max(0, j - ms2);
				int fl = std::min(j + ms2, this->lireLargeur() - 1);

				double maxVal = this->operator()(i, j);
				bool flag = true;
				int k = dk;
				while ((k <= fk) && (flag == true)) {
					int l = dl;
					while ((l <= fl) && (flag == true)) {
						if (this->operator()(k, l) > maxVal)
							flag = false;
						l++;
					}
					k++;
				}
				if (flag == true)
					out(i, j) = 1;
			}
	out.m_vMax = 1;

	return out;
}

typedef struct pics 
{
	int numero;
	int angles;
	int rhos;
	int taille;
} PICS;

static bool myTri(PICS p1, PICS p2) 
{
	return (p1.taille > p2.taille);
}

CImageNdg CImageDouble::houghExtractionLignes(const std::string& methode, const CImageNdg& img, int N, int M, double dim, int nombre, bool enregistrementCSV) {
	// HOUGH transform


	int hough_h = (int)(std::max(img.lireHauteur() / 2, img.lireLargeur() / 2) * sqrt(2.0));
	//moitiee de la diagonale de l'image

	int DIAG = (int)(hough_h * 2);
	// taille de l'image hough, permet de determiner la taille totale de l'espace des rho,
	//de -hough_h a +hough_h


	CImageDouble planHough(DIAG, 180);
	// initialisation du plan hough: 180 colonnes pour les angles, DIAG lignes pour les rho

	planHough.ecrireMin(0);
	planHough.ecrireMax(0);

	int cx = img.lireHauteur() / 2; //represente les coordonnees du centre de l'image
	int cy = img.lireLargeur() / 2; 

	for (int x = 0; x < img.lireHauteur(); x++)
	{
		for (int y = 0; y < img.lireLargeur(); y++)
		{
			if (img(x, y) > 0)
			{
				for (int t = 0; t <= 179; t++)
				{
					int r = (int)(((double)x - cx) * cos((double)t * (PI / 180)) + (((double)y - cy) * sin((double)t * (PI / 180)))); //r=rho*coseteta+rho*sinteta , t=teta converti en degres
					planHough(hough_h + r, t) += 1;
					   //accumulation: chaque calcul de r ajuste l'indice
					   //en ajoutant 'hough_h' pour eviter les valeurs negatives
				       //la valeur est incrementee dans planHough a l'index correspondant a la 
					   //combinaison de r et t
					   //cela construit l'histogramme de hough ou chaque incrementation
					   //correspond a un point d'une ligne potentielle passant
					   //par le pixel (x,y) dans l'image d'origine sous un angle t
				}
			}
		}

	}

	// filtrage gaussien
	planHough = planHough.filtrage("gaussien", 5, 1); 
	// optionnel, utilise pour lisser l'image et donc reduire le bruit et les 
	// faux positifs dans l'espace de Hough
	// le 5 indice 5*5: la taille du noyau du filtre et 1 indique l'ecart type du filtre 

	for (int p = 0; p < planHough.lireNbPixels(); p++)
		if (planHough(p) > planHough.lireMax())
			planHough.ecrireMax(planHough(p));
	planHough.toNdg("expansion").sauvegarde("planHough");
	//parcourt tous les pixels du plan de Hough et met a jour la valeur maxi stockee
	//si elle trouve un pixel avec une valeur plus grande que le maximum actuel

	// extraction maxi locaux
	CImageDouble mL = planHough.maxiLocaux(N, M);

	// Hough inverse
	// creation de l'image de sortie avec les lignes detectees pour l'image de hough inverse
	CImageNdg HI(img.lireHauteur(), img.lireLargeur(), 0);
	HI.ecrireNom(img.lireNom() + "HI");
	HI.choixPalette("binaire"); //pour afficher les lignes detectees en blanc

	if (methode.compare("longueur") == 0) 
	{
		// extraction pics
		int nbLignes = 1;
		//initialise un compteur pour numeroter les lignes detectees

		std::stack<PICS> pics;
		//creer une pile pour stocker les structures PICS
		//qui contiennent les informations sur les lignes detectees
		//dans l'espace de Hough
		//suggere que l'ordre d'extraction pourrait etre utilisé
		//ulterieurement dans un contexte de dernier entre, premier sorti

		for (int r = 0; r < DIAG; r++) //parcourt l'espace de Hough
			for (int a = 0; a <= 179; a++)
				if ((mL(r, a) > 0) && (planHough(r, a) >= dim))
					//verifie si le pixel actuel est un maximum local et si
					//sa valeur est superieure a un seuil 'dim'
					//permet de selectionner les pics qui sont maximas locaux et assez significatifs
										
				{
					//création et stockage des structures PICS

					PICS pic = { 0,0,0,0 };
					//initialise une nouvelle instance de la structure PICS

					pic.numero = nbLignes; //assigne un numero unique a chaque pic detecte
					pic.angles = a; //stocke l'angle de la ligne detectee
					pic.rhos = r - hough_h; //stocke la distance de la ligne detectee (ajuste pour stocker la valeur autour de 0)
					pic.taille = (int)planHough(r, a);//enregistre la taille du pic, donc l'intensite de la ligne detectee
					pics.push(pic); //empile la structure PICS dans la pile
					nbLignes += 1; //incremente le compteur de lignes detectees
				}

		// d pilement pics

		if (enregistrementCSV) 
		{
			std::string fichier = "res/" + img.lireNom() + "_Pics.csv";//definit le nom du fichier CSV
			std::ofstream f(fichier.c_str());//ouvre le fichier en ecriture

			if (!f.is_open())
				std::cout << "Impossible d'ouvrir le fichier en ecriture !" << std::endl;
			//verifie si le fichier s'est correctement ouvert

			else 
			{
				f << "Numero; Distance; Angle; Taille" << std::endl; //ecriture des entetes de colonnes
				while (!pics.empty()) //tant que la pile pics n'est pas vide 
				{
					PICS pic = pics.top();//xtrait le dernier element de la pile
					int label = pic.numero;//recupere le numero de la ligne detectee
					double angle = pic.angles;//recupere l'angle de la ligne detectee
					double rho = pic.rhos;//recupere la distance de la ligne detectee
					int tai = pic.taille;//recupere la taille du pic, donc l'intensite de la ligne detectee

					f << label << " ; " << rho << " ; " << angle << " ; " << tai << std::endl;
					if (angle != 0)
					{
						for (int i = 0; i < img.lireHauteur(); i++)
						{
							double x = i - cx; //transformee de Hough inverse
							int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
							int j = y + (int)cy;
							if ((j >= 0) && (j < img.lireLargeur())) //si le pixel est dans les limites de l'image
								HI(i, j) = label;//les pixels correspondants sont marques avec le numero de la ligne detectee
						}
						for (int j = 0; j < img.lireLargeur(); j++)
						{
							double y = j - (int)cy;
							int x = (int)((rho - y * sin(angle * (PI / 180))) / cos(angle * (PI / 180)));
							int i = x + (int)cx;
							if ((i >= 0) && (i < img.lireHauteur()))
								HI(i, j) = label;
						}
					}
					else
						if (angle != 90)
						{
							for (int j = 0; j < img.lireLargeur(); j++) {
								double y = j - (int)cy;
								int x = (int)((rho - y * sin(angle * PI / 180)) / cos(angle * PI / 180));
								int i = x + (int)cx;
								if ((i >= 0) && (i < img.lireHauteur()))
									HI(i, j) = label;
							}
							for (int i = 0; i < img.lireHauteur(); i++)
							{
								double x = i - (int)cx;
								int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
								int j = y + (int)cy;
								if ((j >= 0) && (j < img.lireLargeur()))
									HI(i, j) = label;
							}
						}
					pics.pop();//vide la pile pics
				}
				f.close();//ferme le fichier
			}
		}


		//ici, les lignes detectees sont affichees dans la console donc pas d'enregistrement CSV
		else {
			while (!pics.empty())
			{
				PICS pic = pics.top(); //chaque pic est extrait de la pile

				int label = pic.numero;
				double angle = pic.angles;
				double rho = pic.rhos;
				std::cout << label << " " << angle << " " << rho << std::endl; //les détails de chaque pic sont affichés dans la console

				if (angle != 0)
				{
					for (int i = 0; i < img.lireHauteur(); i++)
					{
						double x = i - (int)cx;
						int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
						int j = y + (int)cy;
						if ((j >= 0) && (j < img.lireLargeur()))
							HI(i, j) = label;
					}
					for (int j = 0; j < img.lireLargeur(); j++)
					{
						double y = j - (int)cy;
						int x = (int)((rho - y * sin(angle * (PI / 180))) / cos(angle * (PI / 180)));
						int i = x + (int)cx;
						if ((i >= 0) && (i < img.lireHauteur()))
							HI(i, j) = label;
					}
				}
				else
					if (angle != 90)
					{
						for (int j = 0; j < img.lireLargeur(); j++) {
							double y = j - (int)cy;
							int x = (int)((rho - y * sin(angle * PI / 180)) / cos(angle * PI / 180));
							int i = x + (int)cx;
							if ((i >= 0) && (i < img.lireHauteur()))
								HI(i, j) = label;
						}
						for (int i = 0; i < img.lireHauteur(); i++)
						{
							double x = i - (int)cx;
							int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
							int j = y + (int)cy;
							if ((j >= 0) && (j < img.lireLargeur()))
								HI(i, j) = label;
						}
					}
				pics.pop();
			}
		}
	}
	else
		if (methode.compare("nombre") == 0) {
			// extraction pics
			int nbLignes = 1; //initialise un compteur pour numeroter les lignes detectees

			std::vector<PICS> pics; //creer un vecteur pour stocker les structures PICS detectees dans l'espace de Hough

			for (int r = 0; r < DIAG; r++)
				for (int a = 0; a <= 179; a++)
					//parcourt l'espace de Hough

					if ((mL(r, a) > 0) && (planHough(r, a) >= dim)) // base minimale pour comptabiliser une droite
					{
						PICS pic = { 0,0,0,0 };
						pic.numero = nbLignes;
						pic.angles = a;
						pic.rhos = r - hough_h;
						pic.taille = (int)planHough(r, a);
						pics.push_back(pic);
						nbLignes += 1;
						//nouvelle strucutre PICS est creee et stockee dans le vecteur pics
					}

			int nbPics = std::min(nbLignes - 1, nombre); // si pas suffisamment de pics extrait
						//si plus de lignes detectees que le nombre de lignes a extraire, le nombre de lignes a extraire est ajuste
			// d pilement pics

			sort(pics.begin(), pics.end(), myTri); //trie les lignes detectees par taille decroissante
				//permet de classer les lignes en fonction de leur intensite, donc de leur taille

			if (enregistrementCSV) 
			{
				std::string fichier = "res/" + img.lireNom() + "_Pics.csv";
				std::ofstream f(fichier.c_str());

				if (!f.is_open())
					std::cout << "Impossible d'ouvrir le fichier en ecriture !" << std::endl;
				else {
					f << "Numero; Distance; Angle; Taille" << std::endl;
					for (int p = 0; p < nbPics; p++)
					{
						PICS pic = pics.at(p);
						int label = pic.numero;
						double angle = pic.angles;
						double rho = pic.rhos;
						int tai = pic.taille;

						f << label << " ; " << rho << " ; " << angle << " ; " << tai << std::endl;

						if (angle != 0)
						{
							for (int i = 0; i < img.lireHauteur(); i++)
							{
								int x = i - cx;
								int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
								int j = y + cy;
								if ((j >= 0) && (j < img.lireLargeur()))
									HI(i, j) = label;
							}
							for (int j = 0; j < img.lireLargeur(); j++)
							{
								double y = j - cy;
								int x = (int)((rho - y * sin(angle * (PI / 180))) / cos(angle * (PI / 180)));
								int i = x + cx;
								if ((i >= 0) && (i < img.lireHauteur()))
									HI(i, j) = label;
							}
						}
						else
							if (angle != 90)
							{
								for (int j = 0; j < img.lireLargeur(); j++) {
									double y = j - cy;
									int x = (int)((rho - y * sin(angle * PI / 180)) / cos(angle * PI / 180));
									int i = x + cx;
									if ((i >= 0) && (i < img.lireHauteur()))
										HI(i, j) = label;
								}
								for (int i = 0; i < img.lireHauteur(); i++)
								{
									double x = i - cx;
									int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
									int j = y + cy;
									if ((j >= 0) && (j < img.lireLargeur()))
										HI(i, j) = label;
								}
							}
					}
					f.close();
				}
			}
			else {
				for (int p = 0; p < nbPics; p++)
				{
					PICS pic = pics.at(p);
					int label = pic.numero;
					double angle = pic.angles;
					double rho = pic.rhos;
					int tai = pic.taille;

					std::cout << label << " " << angle << " " << rho << " -> " << tai << std::endl;
					if (angle != 0)
					{
						for (int i = 0; i < img.lireHauteur(); i++)
						{
							int x = i - cx;
							int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
							int j = y + cy;
							if ((j >= 0) && (j < img.lireLargeur()))
								HI(i, j) = label;
						}
						for (int j = 0; j < img.lireLargeur(); j++)
						{
							int y = j - cy;
							int x = (int)((rho - y * sin(angle * (PI / 180))) / cos(angle * (PI / 180)));
							int i = x + cx;
							if ((i >= 0) && (i < img.lireHauteur()))
								HI(i, j) = label;
						}
					}
					else
						if (angle != 90)
						{
							for (int j = 0; j < img.lireLargeur(); j++) {
								int y = j - cy;
								int x = (int)((rho - y * sin(angle * PI / 180)) / cos(angle * PI / 180));
								int i = x + cx;
								if ((i >= 0) && (i < img.lireHauteur()))
									HI(i, j) = label;
							}
							for (int i = 0; i < img.lireHauteur(); i++)
							{
								int x = i - cx;
								int y = (int)((rho - x * cos(angle * (PI / 180))) / sin(angle * (PI / 180)));
								int j = y + cy;
								if ((j >= 0) && (j < img.lireLargeur()))
									HI(i, j) = label;
							}
						}
				}
			}
		}

	// pas de maskage sur image binaire d'entree qui permettrait aussi de filtrer les "vraies" lignes
	return(HI);
}
