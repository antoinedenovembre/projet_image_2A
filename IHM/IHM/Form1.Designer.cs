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
            this.btnOuvrir = new System.Windows.Forms.Button();
            this.btnStartStop = new System.Windows.Forms.Button();
            this.pictureBoxvterrain = new System.Windows.Forms.PictureBox();
            this.pictureBoxTraite = new System.Windows.Forms.PictureBox();
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
            this.btnDispVerdict = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxvterrain)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxTraite)).BeginInit();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxiinitiale)).BeginInit();
            this.SuspendLayout();
            // 
            // ofd_ouverture_image
            // 
            this.ofd_ouverture_image.FileName = "openFileDialog1";
            // 
            // btnOuvrir
            // 
            this.btnOuvrir.Location = new System.Drawing.Point(60, 495);
            this.btnOuvrir.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnOuvrir.Name = "btnOuvrir";
            this.btnOuvrir.Size = new System.Drawing.Size(286, 46);
            this.btnOuvrir.TabIndex = 1;
            this.btnOuvrir.Text = "Ouvrir images";
            this.btnOuvrir.UseVisualStyleBackColor = true;
            this.btnOuvrir.Click += new System.EventHandler(this.ouvrir);
            // 
            // btnStartStop
            // 
            this.btnStartStop.Location = new System.Drawing.Point(352, 495);
            this.btnStartStop.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnStartStop.Name = "btnStartStop";
            this.btnStartStop.Size = new System.Drawing.Size(293, 46);
            this.btnStartStop.TabIndex = 2;
            this.btnStartStop.Text = "Début/Pause cycle";
            this.btnStartStop.UseVisualStyleBackColor = true;
            this.btnStartStop.Click += new System.EventHandler(this.startStopCycle);
            // 
            // pictureBoxvterrain
            // 
            this.pictureBoxvterrain.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxvterrain.Location = new System.Drawing.Point(650, 141);
            this.pictureBoxvterrain.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.pictureBoxvterrain.Name = "pictureBoxvterrain";
            this.pictureBoxvterrain.Size = new System.Drawing.Size(285, 315);
            this.pictureBoxvterrain.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxvterrain.TabIndex = 3;
            this.pictureBoxvterrain.TabStop = false;
            // 
            // pictureBoxTraite
            // 
            this.pictureBoxTraite.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxTraite.Location = new System.Drawing.Point(351, 141);
            this.pictureBoxTraite.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.pictureBoxTraite.Name = "pictureBoxTraite";
            this.pictureBoxTraite.Size = new System.Drawing.Size(292, 315);
            this.pictureBoxTraite.TabIndex = 4;
            this.pictureBoxTraite.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(54, 115);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(102, 20);
            this.label1.TabIndex = 5;
            this.label1.Text = "Image initiale";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(360, 116);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(103, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Image traitée";
            // 
            // pourcentage_reussite
            // 
            this.pourcentage_reussite.AutoSize = true;
            this.pourcentage_reussite.Location = new System.Drawing.Point(63, 583);
            this.pourcentage_reussite.Name = "pourcentage_reussite";
            this.pourcentage_reussite.Size = new System.Drawing.Size(0, 20);
            this.pourcentage_reussite.TabIndex = 8;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(647, 116);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(100, 20);
            this.label3.TabIndex = 9;
            this.label3.Text = "Vérité terrain";
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.traitementToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(7, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(1287, 33);
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
            this.traitementToolStripMenuItem.Size = new System.Drawing.Size(110, 29);
            this.traitementToolStripMenuItem.Text = "Traitement";
            // 
            // rotation90ToolStripMenuItem
            // 
            this.rotation90ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sensHoraireToolStripMenuItem,
            this.sensTrigonométriqueToolStripMenuItem});
            this.rotation90ToolStripMenuItem.Name = "rotation90ToolStripMenuItem";
            this.rotation90ToolStripMenuItem.Size = new System.Drawing.Size(225, 34);
            this.rotation90ToolStripMenuItem.Text = "Rotation [90]";
            // 
            // sensHoraireToolStripMenuItem
            // 
            this.sensHoraireToolStripMenuItem.Name = "sensHoraireToolStripMenuItem";
            this.sensHoraireToolStripMenuItem.Size = new System.Drawing.Size(286, 34);
            this.sensHoraireToolStripMenuItem.Text = "Sens horaire";
            this.sensHoraireToolStripMenuItem.Click += new System.EventHandler(this.sensHoraireToolStripMenuItem_Click);
            // 
            // sensTrigonométriqueToolStripMenuItem
            // 
            this.sensTrigonométriqueToolStripMenuItem.Name = "sensTrigonométriqueToolStripMenuItem";
            this.sensTrigonométriqueToolStripMenuItem.Size = new System.Drawing.Size(286, 34);
            this.sensTrigonométriqueToolStripMenuItem.Text = "Sens trigonométrique";
            this.sensTrigonométriqueToolStripMenuItem.Click += new System.EventHandler(this.sensTrigonométriqueToolStripMenuItem_Click);
            // 
            // floutageToolStripMenuItem
            // 
            this.floutageToolStripMenuItem.Name = "floutageToolStripMenuItem";
            this.floutageToolStripMenuItem.Size = new System.Drawing.Size(225, 34);
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
            this.zoomToolStripMenuItem.Size = new System.Drawing.Size(225, 34);
            this.zoomToolStripMenuItem.Text = "Zoom";
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(132, 34);
            this.toolStripMenuItem2.Text = "*2";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(129, 6);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(129, 6);
            // 
            // toolStripMenuItem5
            // 
            this.toolStripMenuItem5.Name = "toolStripMenuItem5";
            this.toolStripMenuItem5.Size = new System.Drawing.Size(132, 34);
            this.toolStripMenuItem5.Text = "/2";
            // 
            // gradientToolStripMenuItem
            // 
            this.gradientToolStripMenuItem.Name = "gradientToolStripMenuItem";
            this.gradientToolStripMenuItem.Size = new System.Drawing.Size(225, 34);
            this.gradientToolStripMenuItem.Text = "Gradient";
            // 
            // houghToolStripMenuItem
            // 
            this.houghToolStripMenuItem.Name = "houghToolStripMenuItem";
            this.houghToolStripMenuItem.Size = new System.Drawing.Size(225, 34);
            this.houghToolStripMenuItem.Text = "Hough";
            // 
            // segmentationToolStripMenuItem
            // 
            this.segmentationToolStripMenuItem.Name = "segmentationToolStripMenuItem";
            this.segmentationToolStripMenuItem.Size = new System.Drawing.Size(225, 34);
            this.segmentationToolStripMenuItem.Text = "Segmentation";
            // 
            // pictureBoxiinitiale
            // 
            this.pictureBoxiinitiale.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBoxiinitiale.Location = new System.Drawing.Point(57, 139);
            this.pictureBoxiinitiale.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.pictureBoxiinitiale.Name = "pictureBoxiinitiale";
            this.pictureBoxiinitiale.Size = new System.Drawing.Size(287, 318);
            this.pictureBoxiinitiale.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxiinitiale.TabIndex = 11;
            this.pictureBoxiinitiale.TabStop = false;
            // 
            // labelVerdict
            // 
            this.labelVerdict.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.labelVerdict.Location = new System.Drawing.Point(966, 140);
            this.labelVerdict.Name = "labelVerdict";
            this.labelVerdict.Size = new System.Drawing.Size(252, 250);
            this.labelVerdict.TabIndex = 12;
            // 
            // btnDispVerdict
            // 
            this.btnDispVerdict.Location = new System.Drawing.Point(651, 495);
            this.btnDispVerdict.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnDispVerdict.Name = "btnDispVerdict";
            this.btnDispVerdict.Size = new System.Drawing.Size(286, 46);
            this.btnDispVerdict.TabIndex = 13;
            this.btnDispVerdict.Text = "Afficher verdict couleur";
            this.btnDispVerdict.UseVisualStyleBackColor = true;
            this.btnDispVerdict.Click += new System.EventHandler(this.displayVerdict);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(970, 115);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(118, 20);
            this.label4.TabIndex = 14;
            this.label4.Text = "Verdict Couleur";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1287, 587);
            this.Controls.Add(this.pictureBoxiinitiale);
            this.Controls.Add(this.pictureBoxvterrain);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btnDispVerdict);
            this.Controls.Add(this.labelVerdict);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.pourcentage_reussite);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBoxTraite);
            this.Controls.Add(this.btnStartStop);
            this.Controls.Add(this.btnOuvrir);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form1";
            this.Text = "ProjetImage";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxvterrain)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxTraite)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxiinitiale)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.OpenFileDialog ofd_ouverture_image;
        private System.Windows.Forms.Button btnOuvrir;
        private System.Windows.Forms.Button btnStartStop;
        private System.Windows.Forms.PictureBox pictureBoxvterrain;
        private System.Windows.Forms.PictureBox pictureBoxTraite;
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
        private System.Windows.Forms.Button btnDispVerdict;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ToolStripMenuItem sensHoraireToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem sensTrigonométriqueToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem5;
    }
}

