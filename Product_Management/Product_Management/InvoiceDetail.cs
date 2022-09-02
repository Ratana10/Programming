using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Product_Management
{
    public partial class InvoiceDetail : Form
    {

        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;


        public InvoiceDetail()
        {
            InitializeComponent();
        }

        private void InvoiceDetail_Load(object sender, EventArgs e)
        {
            con.Open();

            cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            sql = "SELECT i.InvoiceNO, p.ProName, i.Price, i.QTY, i.Amount, i.InvoiceID FROM tbInvoiceDetail i INNER JOIN tbProduct p ON i.ProID = p.ProID WHERE i.InvoiceID LIKE ('" + txtBillNo.Text + "%' ) ORDER BY i.InvoiceNO";
            cmd.CommandText = sql;
            cmd.ExecuteNonQuery();

            DataTable dt = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);

            da.Fill(dt);
            dataGridView1.DataSource = dt;

            con.Close();
            dataGridView1.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
        }
    }
}
