using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace IHM
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void ofd_ouverture_image_FileOk(object sender, CancelEventArgs e)
        {
            if (ofd_ouverture_image.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.Image = Image.FromFile(ofd_ouverture_image.FileName);
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            if (fbd.ShowDialog() == DialogResult.OK)
            {
                pictureBox1.Image = fbd.SelectedPath;
            }


        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
