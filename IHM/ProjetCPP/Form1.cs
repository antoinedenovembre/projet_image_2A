using libImage;
using System.Data;
using System.Drawing.Imaging;
using Image = System.Drawing.Image;

namespace ProjetCPP
{
    public partial class Form1 : Form
    {
        // Dossiers contenant les images
        private string dossierBase;
        private string[] fichiersImageInit;
        private string[] fichiersVeriteTerrain;

        // Indices des images actuellement affich�es
        private int indexImageInit = 0;
        private int indexVeriteTerrain = 0;

        // Booleen pour savoir si le cycle est en cours
        private bool cycleEnCours = false;

        public Form1()
        {
            InitializeComponent();
            timer.Interval = 200;
            timer.Tick += Timer_Tick;
        }

        private void ouvrir(object sender, EventArgs e)
        {
            // Ouvrir un dialogue pour choisir un dossier contenant les deux dossier image_init_source et verite_terrain
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            folderBrowserDialog.Description = "Choisir un dossier contenant les images";
            folderBrowserDialog.ShowNewFolderButton = false;
            folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;
            folderBrowserDialog.ShowDialog();

            dossierBase = folderBrowserDialog.SelectedPath;

            InitialiserImages();
        }

        private void startStopCycle(object sender, EventArgs e)
        {
            if (!cycleEnCours)
            {
                // Ne pas initialiser les images ici pour continuer l� o� on s'est arr�t�
                timer.Start();
                btnStartStop.Text = "Pause";
            }
            else
            {
                timer.Stop();
                btnStartStop.Text = "D�but";
            }
            cycleEnCours = !cycleEnCours;
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            // Mettre � jour l'image initiale
            if (indexImageInit < fichiersImageInit.Length)
            {
                pictureBoxiinitiale.ImageLocation = fichiersImageInit[indexImageInit++];
            }
            else
            {
                indexImageInit = 0;
            }

            Bitmap bmp = new Bitmap(pictureBoxiinitiale.Image);
            ClImage Img = new ClImage();

            unsafe
            {
                BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                Img.objetLibDataImgPtr(1, bmpData.Scan0, bmpData.Stride, bmp.Height, bmp.Width);
                // 1 champ texte retour C++, le seuil auto
                bmp.UnlockBits(bmpData);
            }

            int seuil = (int)Img.objetLibValeurChamp(0);

            label4.Text = "Seuil auto : " + seuil;

            displayVerdict();

            // transf�rer C++ vers bmp
            pictureBoxTraite.Image = bmp;

            // Mettre � jour l'image de v�rit� terrain
            if (indexVeriteTerrain < fichiersVeriteTerrain.Length)
            {
                pictureBoxvterrain.ImageLocation = fichiersVeriteTerrain[indexVeriteTerrain++];
            }
            else
            {
                indexVeriteTerrain = 0;
            }
        }

        private void InitialiserImages()
        {
            string dossierImageInit = Path.Combine(dossierBase, "image_init_source");
            string dossierVeriteTerrain = Path.Combine(dossierBase, "verite_terrain");

            if (Directory.Exists(dossierImageInit) && Directory.Exists(dossierVeriteTerrain))
            {
                // Charger la premi�re image de image_init_source
                fichiersImageInit = Directory.EnumerateFiles(dossierImageInit).Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase)).ToArray();
                if (fichiersImageInit.Length > 0)
                {
                    pictureBoxiinitiale.ImageLocation = fichiersImageInit[0];
                }

                // Charger la premi�re image de verite_terrain
                fichiersVeriteTerrain = Directory.EnumerateFiles(dossierVeriteTerrain).Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase)).ToArray();
                if (fichiersVeriteTerrain.Length > 0)
                {
                    pictureBoxvterrain.ImageLocation = fichiersVeriteTerrain[0];
                }
            }
            else
            {
                MessageBox.Show("Le dossier choisi ne contient pas les dossiers image_init_source et verite_terrain", "Erreur", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }

            // R�initialiser les indices
            indexImageInit = 0;
            indexVeriteTerrain = 0;
        }

        private void displayVerdict()
        {
            // Supposons que la m�thode CalculerPourcentage retourne un double entre 0 et 100
            double pourcentage = CalculScore();

            // D�finir la couleur de fond du label Verdict bas� sur le pourcentage
            if (pourcentage > 90)
            {
                labelVerdict.BackColor = Color.Green;
            }
            else if (pourcentage > 80 && pourcentage <= 90)
            {
                labelVerdict.BackColor = Color.Yellow;
            }
            else
            {
                labelVerdict.BackColor = Color.Red;
            }
        }

        private double CalculScore()
        {
            // Logique de calcul du pourcentage
            return 95.0;
        }

        /*
        private void sensHoraireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Image img = pictureBoxiinitiale.Image;
            Image image = pictureBoxvterrain.Image;
            Bitmap bmp = new Bitmap(img);
            Bitmap bmp2 = new Bitmap(image);

            // Rotation de 90 degr�s dans le sens horaire
            bmp.RotateFlip(RotateFlipType.Rotate270FlipNone);
            bmp2.RotateFlip(RotateFlipType.Rotate270FlipNone);
            pictureBoxiinitiale.Image = bmp;
            pictureBoxvterrain.Image = bmp2;
        }

        private void sensTrigonom�triqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Image img = pictureBoxiinitiale.Image;
            Image image = pictureBoxvterrain.Image;
            Bitmap bmp = new Bitmap(img);
            Bitmap bmp2 = new Bitmap(image);

            // Rotation de 90 degr�s dans le sens antihoraire
            bmp.RotateFlip(RotateFlipType.Rotate90FlipNone);
            bmp2.RotateFlip(RotateFlipType.Rotate90FlipNone);
            pictureBoxiinitiale.Image = bmp;
            pictureBoxvterrain.Image = bmp2;
        }
        */
    }
}
