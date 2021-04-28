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
    public partial class frmMain : Form
    {
        public frmMain()
        {
            InitializeComponent();
        }
        SQLiteConnection liteConn;
        static string path = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "favorites.db");

        private void btnCreateTable_Click(object sender, EventArgs e)
        {
            SQLiteCommand cmd;
            cmd = liteConn.CreateCommand();
            //drop table 
            cmd.CommandText = "DROP TABLE IF EXISTS foods";
            cmd.ExecuteNonQuery();
            //create table
            cmd.CommandText = @"CREATE TABLE foods(Id INTEGER PRIMARY KEY, name TEXT, experation INT, vegan INT, vegatarian INT, price REAL )";
            cmd.ExecuteNonQuery(); 
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            liteConn = CreateConnection(); 
        }
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

        private void btnInsert_Click(object sender, EventArgs e)
        {
            if (liteConn.State == ConnectionState.Open)
            {
                SQLiteCommand cmd;
                cmd = liteConn.CreateCommand();
                cmd.CommandText = "DELETE FROM foods";
                //insert //15 records
                cmd.CommandText = "INSERT INTO foods(name, experation, vegan, vegatarian, price) VALUES('Asperagus', 2021, 1, 1, 10.99), ('Apple', 2022, 1,1,5.99), ('Chicken', 2020, 0,0,9.99), ('Orange', 2020,1,1,1.99),('Beef', 2020,0,0,12.99),('Soda', 2020,1,1,1.99),('Water', 2060, 1,1,0.00),('Peach', 2021,1,1,2.55),('Curry', 2025, 0,1,20.99),('Hotdog', 2030, 0,0,2.33),('Tofu', 2050,1,1,23.55),('Fuit Loop', 2022,0,0,9.99),('Milk', 2020,0,1,13.99),('Coconut', 2020,1,1,12.99),('Milk Chocolate', 2021,0,1,3.99)";
                cmd.ExecuteNonQuery();
            }
            else
                MessageBox.Show("The database is closed", "error"); 
        }

        private void btnDisplay_Click(object sender, EventArgs e)
        {
            frmDisplay display = new frmDisplay();
            display.ShowDialog(); 
        }

        private void btnReport_Click(object sender, EventArgs e)
        {
            PrintReport(GenerateReport()); 
        }
        private StringBuilder GenerateReport()
        {
            bool vegan = false;
            bool vegatarian = false;
            StringBuilder html = new StringBuilder();
            StringBuilder css = new StringBuilder();

            //css - 
            css.Append("<style>");
            css.Append(@"*{font-family:Times; }"); 
            css.Append("td{padding:5px; text-align:center;font-weight:bold;text-align:center;}");
            css.Append("h1{color:black}");
            css.Append("</style>");
            html.Append("<html>");
            html.Append("<img src=\"Food.jpg\"width=\"100\"height=\"100\">");
            html.Append($"<head>{css}<title>{"Food List"}</title></head>");
            html.Append($"<h1>{"Food List"}</h1>");

            //create table data. 
            SQLiteDataReader dr;
            SQLiteCommand cmd;
            cmd = liteConn.CreateCommand();
            cmd.CommandText = "SELECT * FROM foods";
            //grab data. .
            dr = cmd.ExecuteReader();
            html.Append("<table>");
            html.Append("<tr><td colspan=3><hr/></td></tr>");
            html.Append("<tr>");
            html.Append("<th>ID</th><th>Title</th><th>Exp.</th><th>Vegan</th><th>Vegatarian</th><th>Price</th></tr>");
            while (dr.Read())
            {
                if (dr.GetInt32(3) == 1)
                    vegan = true;
                if (dr.GetInt32(4) == 2)
                    vegatarian = true;
                html.Append($"<td>{dr.GetInt32(0)}</td>");
                html.Append($"<td>{dr.GetString(1)}</td>");
                html.Append($"<td>{dr.GetInt32(2)}</td>");
                html.Append($"<td>{vegan}</td>");
                html.Append($"<td>{vegatarian}</td>");
                html.Append($"<td>{dr.GetDouble(5)}</td></tr>");
            }
            html.Append("<tr><td colspan=4><hr/></td></tr>");
            DateTime today = DateTime.Now;
            html.Append(today.ToString("yyyy-MM-dd-HHmmss"));
            html.Append(@"<footer>Created By: Zoe DeLozier</footer>"); 
            html.Append("<table>");
            html.Append("</body></html>");

            return html;
        }
        private void PrintReport(StringBuilder html)
        {
            //write to report.html
            try
            {
                //using will automatically close a file after opening it. 
                using (StreamWriter wr = new StreamWriter(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Report.html"))
                {
                    wr.WriteLine(html);
                }
                System.Diagnostics.Process.Start(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Report.html");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            DateTime today = DateTime.Now;
            using (StreamWriter wr = new StreamWriter($"{today.ToString("yyyy-MM-dd-HHmmss")} - report.html"))
            {
                wr.WriteLine(html);
            }
        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            Application.Exit(); 
        }

        private void btnAbout_Click(object sender, EventArgs e)
        {
            frmAbout about = new frmAbout();
            about.ShowDialog(); 
        }
    }
}
