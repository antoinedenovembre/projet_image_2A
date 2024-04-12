using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IHM
{
    public partial class Form1 : Form
    {
        private string[] fichiersImageInit;
        private string[] fichiersVeriteTerrain;
        private int indexImageInit = 0;
        private int indexVeriteTerrain = 0;
        private bool cycleEnCours = false;


        public Form1()
        {
            InitializeComponent();
            timer.Interval = 200;
            timer.Tick += Timer_Tick;
            InitialiserImages();
        }

        
        private void Form1_Load(object sender, EventArgs e)
        {

        }

     
        private void Button1_Click(object sender, EventArgs e)
        {

        string dossierBase = @"C:\Users\julie\OneDrive\Documents\projet_image_2A\banque_image";
        string dossierImageInit = Path.Combine(dossierBase, "image_init_source");
        string dossierVeriteTerrain = Path.Combine(dossierBase, "verite_terrain");

        // Charger la première image de image_init_source
        string[] fichiersImageInit = Directory.EnumerateFiles(dossierImageInit).Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase)).ToArray();
        if (fichiersImageInit.Length > 0)
        {
                pictureBoxiinitiale.ImageLocation = fichiersImageInit[0];
        }

            // Charger la première image de verite_terrain
        string[] fichiersVeriteTerrain = Directory.EnumerateFiles(dossierVeriteTerrain).Where(file => file.EndsWith(".bmp", StringComparison.OrdinalIgnoreCase) || file.EndsWith(".png", StringComparison.OrdinalIgnoreCase)).ToArray(); 
        if (fichiersVeriteTerrain.Length > 0)
        {
                pictureBoxvterrain.ImageLocation = fichiersVeriteTerrain[0];
        }


        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!cycleEnCours)
            {
                // Ne pas initialiser les images ici pour continuer là où on s'est arrêté
                timer.Start();
                button2.Text = "Pause";
            }
            else
            {
                timer.Stop();
                button2.Text = "Début";
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
            string dossierBase = @"C:\Users\julie\OneDrive\Documents\projet_image_2A\banque_image";
            string dossierImageInit = Path.Combine(dossierBase, "image_init_source");
            string dossierVeriteTerrain = Path.Combine(dossierBase, "verite_terrain");

            fichiersImageInit = Directory.EnumerateFiles(dossierImageInit, "*.*")
                .Where(file => new[] { ".bmp", ".png" }.Contains(Path.GetExtension(file).ToLowerInvariant()))
                .ToArray();

            fichiersVeriteTerrain = Directory.EnumerateFiles(dossierVeriteTerrain, "*.*")
                .Where(file => new[] { ".bmp", ".png" }.Contains(Path.GetExtension(file).ToLowerInvariant()))
                .ToArray();

            // Réinitialiser les indices
            indexImageInit = 0;
            indexVeriteTerrain = 0;
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
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


        // Méthode hypothétique pour calculer le pourcentage
        // Vous devez remplacer cette méthode par votre propre logique de calcul
        private double CalculScore()
        {
            // Logique de calcul du pourcentage
            // Retourner un pourcentage pour tester l'implémentation
            return 95.0; // Exemple de valeur de retour
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

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {

        }
    }
}
