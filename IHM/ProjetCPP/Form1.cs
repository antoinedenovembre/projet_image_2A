using libImage;
using System.Data;
using System.Drawing.Imaging;

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

        // Listes des scores
        private List<double> scoresIou = new List<double>();
        private List<double> scoresHamming = new List<double>();

        public Form1()
        {
            InitializeComponent();
            timer.Interval = 1;
            timer.Tick += Timer_Tick;

            switchProgressVisibility(false);
            switchScoreStats(false);
        }

        private void switchProgressVisibility(bool visible)
        {
            progressBar.Visible = visible;
            progressTitleLabel.Visible = visible;
            progressLabel.Visible = visible;

            this.Height = visible ? this.Height + 100 : this.Height - 100;
        }

        private void switchScoreStats(bool visible)
        {
            labelMeanIou.Visible = visible;
            labelMedIou.Visible = visible;
            meanIou.Visible = visible;
            medIou.Visible = visible;
            labelMeanHamming.Visible = visible;
            labelMedHamming.Visible = visible;
            meanHamming.Visible = visible;
            medHamming.Visible = visible;
        }

        private void ouvrir(object sender, EventArgs e)
        {
            // Ouvrir un dialogue pour choisir un dossier contenant les deux dossier image_init_source et verite_terrain
            FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
            folderBrowserDialog.Description = "Choisir un dossier contenant les images";
            folderBrowserDialog.ShowNewFolderButton = false;
            folderBrowserDialog.RootFolder = Environment.SpecialFolder.MyComputer;
            folderBrowserDialog.ShowDialog();

            if (string.IsNullOrEmpty(folderBrowserDialog.SelectedPath))
            {
                return;
            }

            dossierBase = folderBrowserDialog.SelectedPath;

            switchProgressVisibility(true);
            switchScoreStats(true);

            // Initialiser la progress bar a la bonne taille, avec seulement le dossier image_init_source considéré
            progressBar.Maximum = Directory.EnumerateFiles(Path.Combine(dossierBase, "image_init_source"))
                .Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase))
                .ToArray().Length;

            // Initialiser le label de progression, avec entre parentheses le pourcentage de progression
            progressLabel.Text = "0/" + progressBar.Maximum + " (0%)";

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

                // Mettre à jour l'image de vérité terrain
                if (indexVeriteTerrain < fichiersVeriteTerrain.Length)
                {
                    pictureBoxvterrain.ImageLocation = fichiersVeriteTerrain[indexVeriteTerrain];
                    pictureBoxvterrain.Load();
                }
                else
                {
                    timer.Stop();
                    return;
                }
            }
            else
            {
                timer.Stop();
                return;
            }

            Bitmap bmp = new Bitmap(pictureBoxiinitiale.Image);
            Bitmap bmpGT = new Bitmap(pictureBoxvterrain.Image);
            ClImage Img = new ClImage();

            unsafe
            {
                BitmapData bmpData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                BitmapData bmpDataGT = bmpGT.LockBits(new Rectangle(0, 0, bmpGT.Width, bmpGT.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
                Img.objetLibDataImgPtr(2, bmpData.Scan0, bmpDataGT.Scan0, bmpData.Stride, bmp.Height, bmp.Width);
                bmp.UnlockBits(bmpData);
                bmpGT.UnlockBits(bmpDataGT);
            }

            double scoreIou = (double)Img.objetLibValeurChamp(0) * 100;
            double scoreHamming = (double)Img.objetLibValeurChamp(1) * 100;

            scoresIou.Add(scoreIou);
            scoresHamming.Add(scoreHamming);

            iouValue.Text = scoreIou.ToString("F2") + "%";
            hammingValue.Text = scoreHamming.ToString("F2") + "%";
            displayVerdictIou(scoreIou);
            displayVerdictHamming(scoreHamming);

            // Calcul de la moyenne et de la médiane
            meanIou.Text = scoresIou.Average().ToString("F2") + "%";
            medIou.Text = Median(scoresIou).ToString("F2") + "%";

            meanHamming.Text = scoresHamming.Average().ToString("F2") + "%";
            medHamming.Text = Median(scoresHamming).ToString("F2") + "%";


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

            // Liberation de la mémoire
            bmpGT.Dispose();

            // Update progress bar and progress label
            progressBar.Value = indexImageInit;
            progressLabel.Text = indexImageInit + "/" + progressBar.Maximum + " (" + (indexImageInit * 100 / progressBar.Maximum) + "%)";
        }

        private double Median(List<double> sourceNumbers)
        {
            // Create a copy of the input, and sort the copy
            double[] sortedPNumbers = sourceNumbers.ToArray();
            Array.Sort(sortedPNumbers);

            // Get the median
            int size = sortedPNumbers.Length;
            int mid = size / 2;
            double median = (size % 2 != 0) ? (double)sortedPNumbers[mid] : ((double)sortedPNumbers[mid] + (double)sortedPNumbers[mid - 1]) / 2;
            return median;
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

        private void displayVerdictIou(double score)
        {
            // Définir la couleur de fond du label Verdict basé sur le pourcentage
            if (score > 50)
            {
                labelVerdictIOU.BackColor = Color.Green;
            }
            else if (score > 40 && score <= 50)
            {
                labelVerdictIOU.BackColor = Color.Yellow;
            }
            else
            {
                labelVerdictIOU.BackColor = Color.Red;
            }
        }

        private void displayVerdictHamming(double score)
        {
            // Définir la couleur de fond du label Verdict basé sur le pourcentage
            if (score > 90)
            {
                labelVerdictHamming.BackColor = Color.Green;
            }
            else if (score > 70 && score <= 90)
            {
                labelVerdictHamming.BackColor = Color.Yellow;
            }
            else
            {
                labelVerdictHamming.BackColor = Color.Red;
            }
        }
    }
}
