using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading; 
namespace ZDeLozierACP2_2
{
    public partial class frmSplash : Form
    {
        public frmSplash()
        {
            InitializeComponent();
        }


        private void frmSplash_Load(object sender, EventArgs e)
        {
            bkgWorker.WorkerReportsProgress = true;
            bkgWorker.RunWorkerAsync(); 
        }

        private void bkgWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            for (int i = 0; i <= 100; ++i)
            {
                Thread.Sleep(50);
                bkgWorker.ReportProgress(i);
            }
            
        }

        private void bkgWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            pgrSplash.Value = e.ProgressPercentage;
            lblProgress.Text = "Progress: " + e.ProgressPercentage.ToString();
            if (pgrSplash.Value >= 100)
            {
                this.Hide();
                frmMain main = new frmMain();
                main.ShowDialog();
            }
        }
    }
}
