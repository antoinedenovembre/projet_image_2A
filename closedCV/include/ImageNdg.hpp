#ifndef _IMAGE_NDG_
#define _IMAGE_NDG_

#ifdef _WIN32
#define _EXPORT_ __declspec(dllexport)
#else
#define _EXPORT_ __attribute__((visibility("default")))
#endif

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <complex>

#define MAGIC_NUMBER_BMP ('B'+('M'<<8)) 

static const double PI = 3.141592653589793238460;

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned long LONG;

typedef std::complex<double> Complex;
typedef std::vector<Complex> CVector;

typedef struct tagBITMAPFILEHEADER 
{
	WORD  bfType = 0;
	DWORD bfSize = 0;
	WORD  bfReserved1 = 0;
	WORD  bfReserved2 = 0;
	DWORD bfOffBits = 0;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER 
{
	DWORD biSize = 0;
	LONG  biWidth = 0;
	LONG  biHeight = 0;
	WORD  biPlanes = 0;
	WORD  biBitCount = 0;
	DWORD biCompression = 0;
	DWORD biSizeImage = 0;
	LONG  biXPelsPerMeter = 0;
	LONG  biYPelsPerMeter = 0;
	DWORD biClrUsed = 0;
	DWORD biClrImportant = 0;
} BITMAPINFOHEADER;

typedef struct 
{
	int		minNdg;
	int		maxNdg;
	int		medianeNdg;
	float	moyenneNdg;
	float	ecartTypeNdg;
} MOMENTS;

struct POINT_POLAIRE
{
    int rho;
    int theta;

    std::string toString() const
    {
        return "rho: " + std::to_string(rho) + "\ttheta: " + std::to_string(theta) + "\n";
    }
};

class CImageNdg 
{
private : 

	int              m_iHauteur;
	int              m_iLargeur;  
	bool			 m_bBinaire;	
	std::string      m_sNom;
	unsigned char*   m_pucPixel;

	unsigned char*   m_pucPalette; 

public : 

	// constructeurs
	_EXPORT_ CImageNdg(); // par defaut
	_EXPORT_ CImageNdg(int hauteur, int largeur, int val=-1); // si -1 alors non pixels non initialises
	_EXPORT_ CImageNdg(const std::string nom); // fichier en entree
	_EXPORT_ CImageNdg(const CImageNdg& im); // image en entree

	// destructeur
	_EXPORT_ ~CImageNdg(); 

	// sauvegarde au format bmp
	_EXPORT_ void sauvegarde(const std::string file = ""); // sauvegarde data au format BMP

	// pouvoir acceder e un pixel par image(i)
	_EXPORT_ unsigned char & operator() (int i) const 
	{ 
		return m_pucPixel[i];
	}

	// pouvoir acceder e un pixel par image(i,j)
	_EXPORT_ unsigned char & operator() (int i, int j) const 
	{ 
		return m_pucPixel[i * m_iLargeur + j];
	}

	// operateur copie image par imOut = imIn
	_EXPORT_ CImageNdg& operator=(const CImageNdg& im);

	// get et set 

	_EXPORT_ int lireHauteur() const 
	{  
		return m_iHauteur;
	}

	_EXPORT_ int lireLargeur() const 
	{
		return m_iLargeur;
	}

	_EXPORT_ bool lireBinaire() const 
	{
		return m_bBinaire;
	}

	_EXPORT_ std::string lireNom() const 
	{
		return m_sNom;
	}

	_EXPORT_ void ecrireHauteur(int hauteur) 
	{
		m_iHauteur = hauteur;
	}

	_EXPORT_ void ecrireLargeur(int largeur) 
	{
		m_iLargeur = largeur;
	}

	_EXPORT_ void ecrireBinaire(bool type) 
	{
		m_bBinaire = type;
	}

	_EXPORT_ void ecrireNom(std::string nom) 
	{
		m_sNom = nom;
	}

	_EXPORT_ int lireNbPixels() const 
	{ 
		return m_iHauteur*m_iLargeur;
	}

	_EXPORT_ CImageNdg& choixPalette(std::string name = "grise") 
	{
		if (name.compare("rouge") == 0) 
		{
			for (int indice=0;indice<256;indice ++) 
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
						// fond toujours e 0
						this->m_pucPalette[0] = 0; this->m_pucPalette[1] = 0; this->m_pucPalette[2] = 0; this->m_pucPalette[3] = 0;

						// 8 couleurs de base
						// ensuite periodicite, de sorte que l'objet 1 a le meme label que l'objet 9 par exemple
						this->m_pucPalette[4]  = 255; this->m_pucPalette[5] = 0;    this->m_pucPalette[6] = 0;    this->m_pucPalette[7] = 0;
						this->m_pucPalette[8]  = 0;   this->m_pucPalette[9] = 255;  this->m_pucPalette[10] = 0;   this->m_pucPalette[11] = 0;
						this->m_pucPalette[12] = 0;   this->m_pucPalette[13] = 0;   this->m_pucPalette[14] = 255; this->m_pucPalette[15] = 0;
						this->m_pucPalette[16] = 255; this->m_pucPalette[17] = 255; this->m_pucPalette[18] = 0;   this->m_pucPalette[19] = 0;
						this->m_pucPalette[20] = 0;   this->m_pucPalette[21] = 255; this->m_pucPalette[22] = 255; this->m_pucPalette[23] = 0;
						this->m_pucPalette[24] = 255; this->m_pucPalette[25] = 0;   this->m_pucPalette[26] = 255; this->m_pucPalette[27] = 0;
						this->m_pucPalette[28] = 0;   this->m_pucPalette[29] = 128; this->m_pucPalette[30] = 255; this->m_pucPalette[31] = 0;
						this->m_pucPalette[32] = 128; this->m_pucPalette[33] = 255;   this->m_pucPalette[34] = 128; this->m_pucPalette[35] = 0;

						for (int indice=9;indice<256;indice ++) 
						{
							this->m_pucPalette[indice*4]   = this->m_pucPalette[indice*4-32];
							this->m_pucPalette[indice*4+1] = this->m_pucPalette[indice*4+1-32];;
							this->m_pucPalette[indice*4+2] = this->m_pucPalette[indice*4+2-32];;
							this->m_pucPalette[indice*4+3] = 0;
						}
					}
					else // palette gris
						for (int indice=0;indice<256;indice ++) 
						{
							this->m_pucPalette[indice*4]   = (unsigned char)(indice);
							this->m_pucPalette[indice*4+1] = (unsigned char)(indice);
							this->m_pucPalette[indice*4+2] = (unsigned char)(indice);
							this->m_pucPalette[indice*4+3] = 0;
						}
		return *this;
	}
	
	_EXPORT_ CImageNdg& choixPalette(std::vector<int> map) 
	{ 
		// couleurs donnees par tableau de 256 couleurs RGB)
		for (int indice=0;indice<256;indice ++) 
		{
			this->m_pucPalette[indice*4]   = (unsigned char)map[indice*3+2];
			this->m_pucPalette[indice*4+1] = (unsigned char)map[indice*3+1];
			this->m_pucPalette[indice*4+2] = (unsigned char)map[indice*3];
			this->m_pucPalette[indice*4+3] = 0;
		}
		return *this;
	}

	_EXPORT_ std::vector<int> lirePalette() const 
	{
		// palette image sortie au format tableau de 256 couleurs RGB
		std::vector<int> palette;
		palette.resize(256*3);
		for (int indice=0;indice<256;indice ++) 
		{
			palette[indice*3+2] = this->m_pucPalette[indice*4];
			palette[indice*3+1] = this->m_pucPalette[indice*4+1];
			palette[indice*3] = this->m_pucPalette[indice*4+2];
		}
		return palette;
	}

	// histogramme
	_EXPORT_ std::vector<unsigned long> histogramme(bool enregistrementCSV = false); 

	// signatures
	// methode avec histogramme prealablement calcule
	_EXPORT_ MOMENTS signatures(const std::vector<unsigned long> h);
	// methode sans histo prealablement calcule
	_EXPORT_ MOMENTS signatures();

	// operations ensemblistes pour images binaires
	// im1 = im1 operation im2;
	// options : "et", "ou", "-"
	_EXPORT_ CImageNdg& operation(const CImageNdg& im, const std::string methode = "et");

	// Score
	// _EXPORT_ CImageNdg& score(const CImageNdg& im, const std::string methode = "iou");

	// seuillage
	// options : "manuel", "otsu"
	_EXPORT_ CImageNdg seuillage(const std::string methode = "otsu", int seuilBas = 128, int seuilHaut = 255); // seuillage automatique Otsu par defaut, sinon "manuel" et choix des seuils Bas et Haut

	// transformation
	// options : "complement", "expansion", "egalisation"
	_EXPORT_ CImageNdg transformation(const std::string methode = "complement"); 

	// morphologie
	// methode options : "erosion", "dilatation"
	// element structurant options : "V4" ou "V8"
	_EXPORT_ CImageNdg morphologie(const std::string methode = "dilatation", const std::string eltStructurant = "V8");
	
	_EXPORT_ CImageNdg filtrage(const std::string& methode = "moyennage", int Ni = 3, int Nj = 3); // choix "moyennage" / "median"

	// Transformee de Hough
	_EXPORT_ CImageNdg hough(int threshold = 140, bool colorForEachLine = false);

	_EXPORT_ CImageNdg horizontalConcatenate(const CImageNdg& im);
	_EXPORT_ CImageNdg verticalConcatenate(const CImageNdg& im);

	_EXPORT_ CImageNdg erosion(int Ni = 3, int Nj = 3);
	_EXPORT_ CImageNdg dilatation(int Ni = 3, int Nj = 3);
	_EXPORT_ CImageNdg ouverture(int Ni = 3, int Nj = 3);
	_EXPORT_ CImageNdg fermeture(int Ni = 3, int Nj = 3);

	// Transformee de Fourier 1D
	void fft(CVector& x) {
		size_t N = x.size();
		if (N <= 1) return;

		// Divide
		CVector even = CVector(N / 2);
		CVector odd = CVector(N / 2);
		for (size_t i = 0; i < N / 2; ++i) {
			even[i] = x[i * 2];
			odd[i] = x[i * 2 + 1];
		}

		// Recurse
		fft(even);
		fft(odd);

		// Combine
		for (size_t k = 0; k < N / 2; ++k) {
			Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
			x[k] = even[k] + t;
			x[k + N / 2] = even[k] - t;
		}
	}

	void ifft(CVector& x) {
		size_t N = x.size();
		if (N <= 1) return;

		// Conjugate the complex numbers
		for(auto& num : x) {
			num = std::conj(num);
		}

		// Apply FFT
		fft(x);

		// Conjugate the complex numbers again
		for(auto& num : x) {
			num = std::conj(num);
		}

		// Normalize
		for(auto& num : x) {
			num /= N;
		}
	}

	void fftshift(CVector& x) {
		size_t N = x.size();
		size_t halfSize = N / 2;
		for (size_t i = 0; i < halfSize; ++i) {
			std::swap(x[i], x[i + halfSize]);
		}
	}

	void ifftshift(CVector& x) {
		fftshift(x); // For even-sized vectors, fftshift and ifftshift are the same.
	}

	// Transformee de Fourier 2D
	_EXPORT_ CImageNdg fft2();
	_EXPORT_ CImageNdg ifft2();
	_EXPORT_ CImageNdg fftshift2();
	_EXPORT_ CImageNdg ifftshift2();

	// Conversions
	CVector imageToComplexVector();
	CImageNdg complexVectorToImage(CVector& vec);
};

#endif // _IMAGE_NDG_
