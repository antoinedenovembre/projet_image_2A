namespace IHM
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.ofd_ouverture_image = new System.Windows.Forms.OpenFileDialog();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.pictureBoxvterrain = new System.Windows.Forms.PictureBox();
            this.pictureBox3 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.pourcentage_reussite = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.traitementToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.rotation90ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sensHoraireToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sensTrigonométriqueToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.floutageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.zoomToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripMenuItem5 = new System.Windows.Forms.ToolStripMenuItem();
            this.gradientToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.houghToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.segmentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBoxiinitiale = new System.Windows.Forms.PictureBox();
            this.folderBrowserDialog1 = new System.Windows.Forms.FolderBrowserDialog();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.labelVerdict = new System.Windows.Forms.Label();
            this.button3 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxvterrain)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxiinitiale)).BeginInit();
            this.SuspendLayout();
            // 
            // ofd_ouverture_image
            // 
            this.ofd_ouverture_image.FileName = "openFileDialog1";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(156, 426);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(101, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Ouvrir images";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(156, 455);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(137, 23);
            this.button2.TabIndex = 2;
            this.button2.Text = "Début/Pause cycle";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // pictureBoxvterrain
            // 
            this.pictureBoxvterrain.Location = new System.Drawing.Point(578, 113);
            this.pictureBoxvterrain.Name = "pictureBoxvterrain";
            this.pictureBoxvterrain.Size = new System.Drawing.Size(253, 252);
            this.pictureBoxvterrain.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxvterrain.TabIndex = 3;
            this.pictureBoxvterrain.TabStop = false;
            // 
            // pictureBox3
            // 
            this.pictureBox3.Location = new System.Drawing.Point(312, 113);
            this.pictureBox3.Name = "pictureBox3";
            this.pictureBox3.Size = new System.Drawing.Size(260, 252);
            this.pictureBox3.TabIndex = 4;
            this.pictureBox3.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(48, 92);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 16);
            this.label1.TabIndex = 5;
            this.label1.Text = "Image initiale";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(320, 93);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 16);
            this.label2.TabIndex = 6;
            this.label2.Text = "Image traitée";
            // 
            // pourcentage_reussite
            // 
            this.pourcentage_reussite.AutoSize = true;
            this.pourcentage_reussite.Location = new System.Drawing.Point(161, 494);
            this.pourcentage_reussite.Name = "pourcentage_reussite";
            this.pourcentage_reussite.Size = new System.Drawing.Size(0, 16);
            this.pourcentage_reussite.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(575, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(82, 16);
            this.label3.TabIndex = 9;
            this.label3.Text = "Vérité terrain";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.traitementToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1470, 28);
            this.menuStrip1.TabIndex = 10;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // traitementToolStripMenuItem
            // 
            this.traitementToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.rotation90ToolStripMenuItem,
            this.floutageToolStripMenuItem,
            this.zoomToolStripMenuItem,
            this.gradientToolStripMenuItem,
            this.houghToolStripMenuItem,
            this.segmentationToolStripMenuItem});
            this.traitementToolStripMenuItem.Name = "traitementToolStripMenuItem";
            this.traitementToolStripMenuItem.Size = new System.Drawing.Size(94, 24);
            this.traitementToolStripMenuItem.Text = "Traitement";
            // 
            // rotation90ToolStripMenuItem
            // 
            this.rotation90ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sensHoraireToolStripMenuItem,
            this.sensTrigonométriqueToolStripMenuItem});
            this.rotation90ToolStripMenuItem.Name = "rotation90ToolStripMenuItem";
            this.rotation90ToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.rotation90ToolStripMenuItem.Text = "Rotation [90]";
            // 
            // sensHoraireToolStripMenuItem
            // 
            this.sensHoraireToolStripMenuItem.Name = "sensHoraireToolStripMenuItem";
            this.sensHoraireToolStripMenuItem.Size = new System.Drawing.Size(235, 26);
            this.sensHoraireToolStripMenuItem.Text = "Sens horaire";
            this.sensHoraireToolStripMenuItem.Click += new System.EventHandler(this.sensHoraireToolStripMenuItem_Click);
            // 
            // sensTrigonométriqueToolStripMenuItem
            // 
            this.sensTrigonométriqueToolStripMenuItem.Name = "sensTrigonométriqueToolStripMenuItem";
            this.sensTrigonométriqueToolStripMenuItem.Size = new System.Drawing.Size(235, 26);
            this.sensTrigonométriqueToolStripMenuItem.Text = "Sens trigonométrique";
            this.sensTrigonométriqueToolStripMenuItem.Click += new System.EventHandler(this.sensTrigonométriqueToolStripMenuItem_Click);
            // 
            // floutageToolStripMenuItem
            // 
            this.floutageToolStripMenuItem.Name = "floutageToolStripMenuItem";
            this.floutageToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.floutageToolStripMenuItem.Text = "Floutage";
            // 
            // zoomToolStripMenuItem
            // 
            this.zoomToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.toolStripMenuItem1,
            this.toolStripMenuItem3,
            this.toolStripMenuItem5});
            this.zoomToolStripMenuItem.Name = "zoomToolStripMenuItem";
            this.zoomToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.zoomToolStripMenuItem.Text = "Zoom";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(106, 26);
            this.toolStripMenuItem2.Text = "*2";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(103, 6);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(103, 6);
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(106, 26);
            this.toolStripMenuItem5.Text = "/2";
            // 
            // gradientToolStripMenuItem
            // 
            this.gradientToolStripMenuItem.Name = "gradientToolStripMenuItem";
            this.gradientToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.gradientToolStripMenuItem.Text = "Gradient";
            // 
            // houghToolStripMenuItem
            // 
            this.houghToolStripMenuItem.Name = "houghToolStripMenuItem";
            this.houghToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.houghToolStripMenuItem.Text = "Hough";
            // 
            // segmentationToolStripMenuItem
            // 
            this.segmentationToolStripMenuItem.Name = "segmentationToolStripMenuItem";
            this.segmentationToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.segmentationToolStripMenuItem.Text = "Segmentation";
            // 
            // pictureBoxiinitiale
            // 
            this.pictureBoxiinitiale.Location = new System.Drawing.Point(51, 111);
            this.pictureBoxiinitiale.Name = "pictureBoxiinitiale";
            this.pictureBoxiinitiale.Size = new System.Drawing.Size(255, 254);
            this.pictureBoxiinitiale.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxiinitiale.TabIndex = 11;
            this.pictureBoxiinitiale.TabStop = false;
            // 
            // labelVerdict
            // 
            this.labelVerdict.Location = new System.Drawing.Point(859, 112);
            this.labelVerdict.Name = "labelVerdict";
            this.labelVerdict.Size = new System.Drawing.Size(224, 200);
            this.labelVerdict.TabIndex = 12;
            this.labelVerdict.Click += new System.EventHandler(this.label4_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(156, 484);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(150, 23);
            this.button3.TabIndex = 13;
            this.button3.Text = "Afficher verdict couleur";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(862, 92);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(98, 16);
            this.label4.TabIndex = 14;
            this.label4.Text = "Verdict Couleur";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1470, 568);
            this.Controls.Add(this.pictureBoxiinitiale);
            this.Controls.Add(this.pictureBoxvterrain);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.labelVerdict);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.pourcentage_reussite);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxvterrain)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox3)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxiinitiale)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.OpenFileDialog ofd_ouverture_image;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.PictureBox pictureBoxvterrain;
        private System.Windows.Forms.PictureBox pictureBox3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label pourcentage_reussite;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem traitementToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem rotation90ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem floutageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem zoomToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
        private System.Windows.Forms.PictureBox pictureBoxiinitiale;
        private System.Windows.Forms.ToolStripMenuItem gradientToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem houghToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem segmentationToolStripMenuItem;
        private System.Windows.Forms.FolderBrowserDialog folderBrowserDialog1;
        private System.Windows.Forms.Timer timer;
        private System.Windows.Forms.Label labelVerdict;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolStripMenuItem sensHoraireToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem sensTrigonométriqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem5;
    }
}

