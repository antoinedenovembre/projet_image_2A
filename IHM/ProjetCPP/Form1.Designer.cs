namespace ProjetCPP
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            components = new System.ComponentModel.Container();
            pictureBoxvterrain = new PictureBox();
            pictureBoxTraite = new PictureBox();
            pictureBoxiinitiale = new PictureBox();
            btnStartStop = new Button();
            btnOuvrir = new Button();
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            labelVerdictIOU = new Label();
            timer = new System.Windows.Forms.Timer(components);
            progressBar = new ProgressBar();
            progressTitleLabel = new Label();
            progressLabel = new Label();
            meanIou = new Label();
            labelMeanIou = new Label();
            medIou = new Label();
            labelMedIou = new Label();
            hammingValue = new Label();
            label6 = new Label();
            iouValue = new Label();
            label8 = new Label();
            labelVerdictHamming = new Label();
            medHamming = new Label();
            labelMedHamming = new Label();
            meanHamming = new Label();
            labelMeanHamming = new Label();
            ((System.ComponentModel.ISupportInitialize)pictureBoxvterrain).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBoxTraite).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBoxiinitiale).BeginInit();
            SuspendLayout();
            // 
            // pictureBoxvterrain
            // 
            pictureBoxvterrain.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxvterrain.Location = new Point(604, 87);
            pictureBoxvterrain.Name = "pictureBoxvterrain";
            pictureBoxvterrain.Size = new Size(285, 258);
            pictureBoxvterrain.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxvterrain.TabIndex = 0;
            pictureBoxvterrain.TabStop = false;
            // 
            // pictureBoxTraite
            // 
            pictureBoxTraite.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxTraite.Location = new Point(323, 87);
            pictureBoxTraite.Name = "pictureBoxTraite";
            pictureBoxTraite.Size = new Size(275, 258);
            pictureBoxTraite.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxTraite.TabIndex = 1;
            pictureBoxTraite.TabStop = false;
            // 
            // pictureBoxiinitiale
            // 
            pictureBoxiinitiale.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxiinitiale.Location = new Point(33, 87);
            pictureBoxiinitiale.Name = "pictureBoxiinitiale";
            pictureBoxiinitiale.Size = new Size(284, 258);
            pictureBoxiinitiale.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxiinitiale.TabIndex = 2;
            pictureBoxiinitiale.TabStop = false;
            // 
            // btnStartStop
            // 
            btnStartStop.Location = new Point(323, 376);
            btnStartStop.Name = "btnStartStop";
            btnStartStop.Size = new Size(236, 68);
            btnStartStop.TabIndex = 4;
            btnStartStop.Text = "Début/Pause cycle";
            btnStartStop.UseVisualStyleBackColor = true;
            btnStartStop.Click += startStopCycle;
            // 
            // btnOuvrir
            // 
            btnOuvrir.Location = new Point(36, 376);
            btnOuvrir.Name = "btnOuvrir";
            btnOuvrir.Size = new Size(245, 68);
            btnOuvrir.TabIndex = 5;
            btnOuvrir.Text = "Ouvrir Images";
            btnOuvrir.UseVisualStyleBackColor = true;
            btnOuvrir.Click += ouvrir;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(99, 39);
            label1.Name = "label1";
            label1.Size = new Size(154, 30);
            label1.TabIndex = 6;
            label1.Text = "Image initiale";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            label2.Location = new Point(393, 39);
            label2.Name = "label2";
            label2.Size = new Size(153, 30);
            label2.TabIndex = 7;
            label2.Text = "Image traitée";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            label3.Location = new Point(677, 39);
            label3.Name = "label3";
            label3.Size = new Size(151, 30);
            label3.TabIndex = 8;
            label3.Text = "Vérité terrain";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Font = new Font("Segoe UI", 11F, FontStyle.Bold, GraphicsUnit.Point);
            label4.Location = new Point(1126, 39);
            label4.Name = "label4";
            label4.Size = new Size(88, 30);
            label4.TabIndex = 9;
            label4.Text = "Verdict";
            // 
            // labelVerdictIOU
            // 
            labelVerdictIOU.BackColor = Color.White;
            labelVerdictIOU.BorderStyle = BorderStyle.FixedSingle;
            labelVerdictIOU.Location = new Point(895, 126);
            labelVerdictIOU.Name = "labelVerdictIOU";
            labelVerdictIOU.Size = new Size(266, 219);
            labelVerdictIOU.TabIndex = 10;
            // 
            // progressBar
            // 
            progressBar.Location = new Point(32, 518);
            progressBar.Name = "progressBar";
            progressBar.Size = new Size(1455, 45);
            progressBar.TabIndex = 13;
            // 
            // progressTitleLabel
            // 
            progressTitleLabel.AutoSize = true;
            progressTitleLabel.Location = new Point(34, 487);
            progressTitleLabel.Name = "progressTitleLabel";
            progressTitleLabel.Size = new Size(82, 25);
            progressTitleLabel.TabIndex = 14;
            progressTitleLabel.Text = "Progrès: ";
            // 
            // progressLabel
            // 
            progressLabel.AutoSize = true;
            progressLabel.Location = new Point(122, 490);
            progressLabel.Name = "progressLabel";
            progressLabel.Size = new Size(85, 25);
            progressLabel.TabIndex = 15;
            progressLabel.Text = ".../... (...%)";
            // 
            // meanIou
            // 
            meanIou.AutoSize = true;
            meanIou.Location = new Point(1021, 398);
            meanIou.Name = "meanIou";
            meanIou.Size = new Size(39, 25);
            meanIou.TabIndex = 17;
            meanIou.Text = "...%";
            // 
            // labelMeanIou
            // 
            labelMeanIou.AutoSize = true;
            labelMeanIou.Location = new Point(895, 398);
            labelMeanIou.Name = "labelMeanIou";
            labelMeanIou.Size = new Size(120, 25);
            labelMeanIou.TabIndex = 16;
            labelMeanIou.Text = "Score moyen:";
            // 
            // medIou
            // 
            medIou.AutoSize = true;
            medIou.Location = new Point(1021, 434);
            medIou.Name = "medIou";
            medIou.Size = new Size(39, 25);
            medIou.TabIndex = 19;
            medIou.Text = "...%";
            // 
            // labelMedIou
            // 
            labelMedIou.AutoSize = true;
            labelMedIou.Location = new Point(895, 434);
            labelMedIou.Name = "labelMedIou";
            labelMedIou.Size = new Size(124, 25);
            labelMedIou.TabIndex = 18;
            labelMedIou.Text = "Score médian:";
            // 
            // hammingValue
            // 
            hammingValue.AutoSize = true;
            hammingValue.Location = new Point(1327, 363);
            hammingValue.Name = "hammingValue";
            hammingValue.Size = new Size(39, 25);
            hammingValue.TabIndex = 23;
            hammingValue.Text = "...%";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new Point(1177, 363);
            label6.Name = "label6";
            label6.Size = new Size(144, 25);
            label6.TabIndex = 22;
            label6.Text = "Score Hamming:";
            // 
            // iouValue
            // 
            iouValue.AutoSize = true;
            iouValue.Location = new Point(1021, 363);
            iouValue.Name = "iouValue";
            iouValue.Size = new Size(39, 25);
            iouValue.TabIndex = 21;
            iouValue.Text = "...%";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new Point(895, 363);
            label8.Name = "label8";
            label8.Size = new Size(96, 25);
            label8.TabIndex = 20;
            label8.Text = "Score IOU:";
            // 
            // labelVerdictHamming
            // 
            labelVerdictHamming.BackColor = Color.White;
            labelVerdictHamming.BorderStyle = BorderStyle.FixedSingle;
            labelVerdictHamming.Location = new Point(1177, 126);
            labelVerdictHamming.Name = "labelVerdictHamming";
            labelVerdictHamming.Size = new Size(266, 219);
            labelVerdictHamming.TabIndex = 24;
            // 
            // medHamming
            // 
            medHamming.AutoSize = true;
            medHamming.Location = new Point(1327, 434);
            medHamming.Name = "medHamming";
            medHamming.Size = new Size(39, 25);
            medHamming.TabIndex = 28;
            medHamming.Text = "...%";
            // 
            // labelMedHamming
            // 
            labelMedHamming.AutoSize = true;
            labelMedHamming.Location = new Point(1177, 434);
            labelMedHamming.Name = "labelMedHamming";
            labelMedHamming.Size = new Size(124, 25);
            labelMedHamming.TabIndex = 27;
            labelMedHamming.Text = "Score médian:";
            // 
            // meanHamming
            // 
            meanHamming.AutoSize = true;
            meanHamming.Location = new Point(1327, 398);
            meanHamming.Name = "meanHamming";
            meanHamming.Size = new Size(39, 25);
            meanHamming.TabIndex = 26;
            meanHamming.Text = "...%";
            // 
            // labelMeanHamming
            // 
            labelMeanHamming.AutoSize = true;
            labelMeanHamming.Location = new Point(1177, 398);
            labelMeanHamming.Name = "labelMeanHamming";
            labelMeanHamming.Size = new Size(120, 25);
            labelMeanHamming.TabIndex = 25;
            labelMeanHamming.Text = "Score moyen:";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1522, 610);
            Controls.Add(medHamming);
            Controls.Add(labelMedHamming);
            Controls.Add(meanHamming);
            Controls.Add(labelMeanHamming);
            Controls.Add(labelVerdictHamming);
            Controls.Add(hammingValue);
            Controls.Add(label6);
            Controls.Add(iouValue);
            Controls.Add(label8);
            Controls.Add(medIou);
            Controls.Add(labelMedIou);
            Controls.Add(meanIou);
            Controls.Add(labelMeanIou);
            Controls.Add(progressLabel);
            Controls.Add(progressTitleLabel);
            Controls.Add(progressBar);
            Controls.Add(labelVerdictIOU);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(btnOuvrir);
            Controls.Add(btnStartStop);
            Controls.Add(pictureBoxiinitiale);
            Controls.Add(pictureBoxTraite);
            Controls.Add(pictureBoxvterrain);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Name = "Form1";
            Text = "ProjetCPP";
            ((System.ComponentModel.ISupportInitialize)pictureBoxvterrain).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBoxTraite).EndInit();
            ((System.ComponentModel.ISupportInitialize)pictureBoxiinitiale).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private PictureBox pictureBoxvterrain;
        private PictureBox pictureBoxTraite;
        private PictureBox pictureBoxiinitiale;
        private Button btnStartStop;
        private Button btnOuvrir;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label labelVerdictIOU;
        private System.Windows.Forms.Timer timer;
        private ProgressBar progressBar;
        private Label progressTitleLabel;
        private Label progressLabel;
        private Label meanIou;
        private Label labelMeanIou;
        private Label medIou;
        private Label labelMedIou;
        private Label hammingValue;
        private Label label6;
        private Label iouValue;
        private Label label8;
        private Label labelVerdictHamming;
        private Label medHamming;
        private Label labelMedHamming;
        private Label meanHamming;
        private Label labelMeanHamming;
    }
}