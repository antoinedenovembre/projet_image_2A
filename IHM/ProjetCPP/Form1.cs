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
                pictureBoxiinitiale.ImageLocation = fichiersImageInit[indexImageInit];
                pictureBoxiinitiale.Load();
            }
            else
            {
                indexImageInit = 0;
            }

            Bitmap bmp = new Bitmap(pictureBoxiinitiale.Image);
            Bitmap bmpGT = new Bitmap(pictureBoxvterrain.Image);
            ClImage Img = new ClImage();

            unsafe
            {
                BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                BitmapData bmpDataGT = bmpGT.LockBits(new Rectangle(0, 0, bmpGT.Width, bmpGT.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                Img.objetLibDataImgPtr(1, bmpData.Scan0, bmpDataGT.Scan0, bmpData.Stride, bmp.Height, bmp.Width);
                bmp.UnlockBits(bmpData);
                bmpGT.UnlockBits(bmpDataGT);
            }

            double score = (double)Img.objetLibValeurChamp(0) * 100;

            label4.Text = "Score : " + score.ToString("F1");

            displayVerdict(score);

            // transférer C++ vers bmp
            pictureBoxTraite.Image = bmp;

            // Mettre à jour l'image de vérité terrain
            if (indexVeriteTerrain < fichiersVeriteTerrain.Length)
            {
                pictureBoxvterrain.ImageLocation = fichiersVeriteTerrain[indexVeriteTerrain];
                pictureBoxvterrain.Load();
            }
            else
            {
                indexVeriteTerrain = 0;
            }

            indexImageInit++;
            indexVeriteTerrain++;
        }

        private void InitialiserImages()
        {
            string dossierImageInit = Path.Combine(dossierBase, "image_init_source");
            string dossierVeriteTerrain = Path.Combine(dossierBase, "verite_terrain");

            if (Directory.Exists(dossierImageInit) && Directory.Exists(dossierVeriteTerrain))
            {
                // Charger les images de image_init_source
                fichiersImageInit = Directory.EnumerateFiles(dossierImageInit)
                    .Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase))
                    .ToArray();

                // Charger les images de verite_terrain
                fichiersVeriteTerrain = Directory.EnumerateFiles(dossierVeriteTerrain)
                    .Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase))
                    .ToArray();

                // Charger la première image de image_init_source
                if (fichiersImageInit.Length > 0)
                {
                    pictureBoxiinitiale.ImageLocation = fichiersImageInit[0];
                }

                // Charger la première image de verite_terrain
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

        private void displayVerdict(double score)
        {
            // Définir la couleur de fond du label Verdict basé sur le pourcentage
            if (score > 90)
            {
                labelVerdict.BackColor = Color.Green;
            }
            else if (score > 80 && score <= 90)
            {
                labelVerdict.BackColor = Color.Yellow;
            }
            else
            {
                labelVerdict.BackColor = Color.Red;
            }
        }
    }
}
