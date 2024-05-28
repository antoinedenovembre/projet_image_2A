#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <cmath>
#include <vector>
#include <ctime>
#include <stack>

#include "libIHM.h"

ClibIHM::ClibIHM() {

	this->nbDataImg = 0;
	this->dataFromImg.clear();
	this->imgPt = NULL;
}

ClibIHM::ClibIHM(int nbChamps, byte* data, byte* GT, int stride, int nbLig, int nbCol){
	this->nbDataImg = nbChamps;
	this->dataFromImg.resize(nbChamps);

	this->imgPt = new CImageCouleur(nbLig, nbCol);
	CImageCouleur GTImg = CImageCouleur(nbLig, nbCol);

	// on remplit les pixels
	byte* pixPtr = (byte*)data;
	byte* pixPtrGt = (byte*)GT;
	for (int y = 0; y < nbLig; y++)
	{
		for (int x = 0; x < nbCol; x++)
		{
			this->imgPt->operator()(y, x)[0] = pixPtr[3 * x + 2];
			this->imgPt->operator()(y, x)[1] = pixPtr[3 * x + 1];
			this->imgPt->operator()(y, x)[2] = pixPtr[3 * x ];

			GTImg(y, x)[0] = pixPtrGt[3 * x + 2];
			GTImg(y, x)[1] = pixPtrGt[3 * x + 1];
			GTImg(y, x)[2] = pixPtrGt[3 * x];
		}
		pixPtr += stride; // largeur une seule ligne gestion multiple 32 bits
		pixPtrGt += stride;
	}

	CImageNdg res;
	res = this->imgPt->plan().process();

	CImageNdg GTNdg = GTImg.plan();
	GTNdg.ecrireBinaire(true);

	double scoreIou = res.score(GTNdg);
	this->dataFromImg.at(0) = scoreIou;
	double scoreHamming = res.Hammingdistance(GTNdg);
	this->dataFromImg.at(1) = scoreHamming;

	pixPtr = (byte*)data;
	for (int y = 0; y < nbLig; y++)
	{
		for (int x = 0; x < nbCol; x++)
		{
			pixPtr[3 * x + 2] = res(y, x) * 255;
			pixPtr[3 * x + 1] = res(y, x) * 255;
			pixPtr[3 * x] = res(y, x) * 255;
		}
		pixPtr += stride; // largeur une seule ligne gestion multiple 32 bits
	}
}

ClibIHM::~ClibIHM() {
	if (imgPt)
		(*this->imgPt).~CImageCouleur(); 
	this->dataFromImg.clear();
}