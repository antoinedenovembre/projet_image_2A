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
            labelVerdict = new Label();
            timer = new System.Windows.Forms.Timer(components);
            treeView1 = new TreeView();
            ((System.ComponentModel.ISupportInitialize)pictureBoxvterrain).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBoxTraite).BeginInit();
            ((System.ComponentModel.ISupportInitialize)pictureBoxiinitiale).BeginInit();
            SuspendLayout();
            // 
            // pictureBoxvterrain
            // 
            pictureBoxvterrain.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxvterrain.Location = new Point(842, 101);
            pictureBoxvterrain.Name = "pictureBoxvterrain";
            pictureBoxvterrain.Size = new Size(285, 258);
            pictureBoxvterrain.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxvterrain.TabIndex = 0;
            pictureBoxvterrain.TabStop = false;
            // 
            // pictureBoxTraite
            // 
            pictureBoxTraite.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxTraite.Location = new Point(561, 101);
            pictureBoxTraite.Name = "pictureBoxTraite";
            pictureBoxTraite.Size = new Size(275, 258);
            pictureBoxTraite.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxTraite.TabIndex = 1;
            pictureBoxTraite.TabStop = false;
            // 
            // pictureBoxiinitiale
            // 
            pictureBoxiinitiale.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxiinitiale.Location = new Point(271, 101);
            pictureBoxiinitiale.Name = "pictureBoxiinitiale";
            pictureBoxiinitiale.Size = new Size(284, 258);
            pictureBoxiinitiale.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxiinitiale.TabIndex = 2;
            pictureBoxiinitiale.TabStop = false;
            // 
            // btnStartStop
            // 
            btnStartStop.Location = new Point(863, 388);
            btnStartStop.Name = "btnStartStop";
            btnStartStop.Size = new Size(236, 68);
            btnStartStop.TabIndex = 4;
            btnStartStop.Text = "Début/Pause cycle";
            btnStartStop.UseVisualStyleBackColor = true;
            btnStartStop.Click += startStopCycle;
            // 
            // btnOuvrir
            // 
            btnOuvrir.Location = new Point(576, 388);
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
            label1.Location = new Point(271, 53);
            label1.Name = "label1";
            label1.Size = new Size(117, 25);
            label1.TabIndex = 6;
            label1.Text = "Image initiale";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(561, 53);
            label2.Name = "label2";
            label2.Size = new Size(116, 25);
            label2.TabIndex = 7;
            label2.Text = "Image traitée";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(842, 53);
            label3.Name = "label3";
            label3.Size = new Size(111, 25);
            label3.TabIndex = 8;
            label3.Text = "Vérité terrain";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(1133, 53);
            label4.Name = "label4";
            label4.Size = new Size(66, 25);
            label4.TabIndex = 9;
            label4.Text = "Verdict";
            // 
            // labelVerdict
            // 
            labelVerdict.BackColor = Color.White;
            labelVerdict.BorderStyle = BorderStyle.FixedSingle;
            labelVerdict.Location = new Point(1133, 101);
            labelVerdict.Name = "labelVerdict";
            labelVerdict.Size = new Size(266, 258);
            labelVerdict.TabIndex = 10;
            // 
            // treeView1
            // 
            treeView1.Location = new Point(12, 10);
            treeView1.Name = "treeView1";
            treeView1.Size = new Size(237, 473);
            treeView1.TabIndex = 11;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1440, 495);
            Controls.Add(treeView1);
            Controls.Add(labelVerdict);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(btnOuvrir);
            Controls.Add(btnStartStop);
            Controls.Add(pictureBoxiinitiale);
            Controls.Add(pictureBoxTraite);
            Controls.Add(pictureBoxvterrain);
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
        private Label labelVerdict;
        private System.Windows.Forms.Timer timer;
        private TreeView treeView1;
    }
}