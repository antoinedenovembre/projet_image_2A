using System;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

namespace IHM
{
    public partial class Form1 : Form
    {
        // Dossiers contenant les images
        private string dossierBase;
        private string[] fichiersImageInit;
        private string[] fichiersVeriteTerrain;

        // Indices des images actuellement affichées
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
                // Ne pas initialiser les images ici pour continuer là où on s'est arrêté
                timer.Start();
                btnStartStop.Text = "Pause";
            }
            else
            {
                timer.Stop();
                btnStartStop.Text = "Début";
            }
            cycleEnCours = !cycleEnCours;
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            // Mettre à jour l'image initiale
            if (indexImageInit < fichiersImageInit.Length)
            {
                pictureBoxiinitiale.ImageLocation = fichiersImageInit[indexImageInit++];
            }
            else
            {
                indexImageInit = 0;
            }

            // Mettre à jour l'image de vérité terrain
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
                // Charger la première image de image_init_source
                fichiersImageInit = Directory.EnumerateFiles(dossierImageInit).Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase)).ToArray();
                if (fichiersImageInit.Length > 0)
                {
                    pictureBoxiinitiale.ImageLocation = fichiersImageInit[0];
                }

                // Charger la première image de verite_terrain
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

            // Réinitialiser les indices
            indexImageInit = 0;
            indexVeriteTerrain = 0;
        }

        private void displayVerdict(object sender, EventArgs e)
        {
            // Supposons que la méthode CalculerPourcentage retourne un double entre 0 et 100
            double pourcentage = CalculScore();

            // Définir la couleur de fond du label Verdict basé sur le pourcentage
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

        private void sensHoraireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Image img = pictureBoxiinitiale.Image;
            Image image = pictureBoxvterrain.Image;
            Bitmap bmp = new Bitmap(img);
            Bitmap bmp2 = new Bitmap(image);

            // Rotation de 90 degrés dans le sens horaire
            bmp.RotateFlip(RotateFlipType.Rotate270FlipNone);
            bmp2.RotateFlip(RotateFlipType.Rotate270FlipNone);
            pictureBoxiinitiale.Image = bmp;
            pictureBoxvterrain.Image = bmp2;
        }

        private void sensTrigonométriqueToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Image img = pictureBoxiinitiale.Image;
            Image image = pictureBoxvterrain.Image;
            Bitmap bmp = new Bitmap(img);
            Bitmap bmp2 = new Bitmap(image);

            // Rotation de 90 degrés dans le sens antihoraire
            bmp.RotateFlip(RotateFlipType.Rotate90FlipNone);
            bmp2.RotateFlip(RotateFlipType.Rotate90FlipNone);
            pictureBoxiinitiale.Image = bmp;
            pictureBoxvterrain.Image = bmp2;
        }
    }
}
