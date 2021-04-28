using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SQLite;
using System.IO; 

namespace ZDeLozierACP2_2
{
    public partial class frmDisplay : Form
    {
        static string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "favorites.db");

        public frmDisplay()
        {
            InitializeComponent();
        }
        SQLiteConnection liteConn; 
        private SQLiteConnection CreateConnection()
        {
            SQLiteConnection liteConn;
            liteConn = new SQLiteConnection("Data Source=" + path);
            //open connection 
            try
            {
                liteConn.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            return liteConn;
        }

        private void frmDisplay_Load(object sender, EventArgs e)
        {
            liteConn = CreateConnection();
            StringBuilder foods;
            bool vegan = false;
            bool vegatarian = false; 
            //display info from database in listbox. 
            SQLiteCommand cmd = liteConn.CreateCommand();
            cmd.CommandText = "SELECT * FROM foods";
            SQLiteDataReader dr;
            dr = cmd.ExecuteReader();
            string[] titles = { "ID", "Name", "Exp.", "Vegan", "Vegatarian", "Price" }; 
            foods = new StringBuilder(String.Format("{0,-20} {1,-20} {2,-20} {3,-20} {4,-20} {5,-20}", titles[0], titles[1], titles[2], titles[3], titles[4], titles[5]));
            lstFood.Items.Add(foods); 
            while (dr.Read())
            {
                if(dr.GetInt32(3) == 1)
                    vegan = true; 
                if (dr.GetInt32(4) == 2)
                    vegatarian = true; 
                foods = new StringBuilder(""); 
                foods.Append(string.Format("{0,-20} {1,-20} {2,-20} {3,-20} {4,-20} {5,20}", dr.GetInt32(0), dr.GetString(1), dr.GetInt32(2), vegan, vegatarian, dr.GetValue(5)));
                lstFood.Items.Add(foods); 
            }

        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close(); 
        }
    }
}
