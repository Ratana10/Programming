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
    public partial class viewBills : Form
    {

        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;


        public viewBills()
        {
            InitializeComponent();
            
        }

        private void viewBills_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'dbShopDataSetInvoices.tbInvoice' table. You can move, or remove it, as needed.
            this.tbInvoiceTableAdapter.Fill(this.dbShopDataSetInvoices.tbInvoice);
            //fillGrid();
            totalBillSale();

            if (FLogin.LoginAccountType != "Admin")
            {
                btnDelete.Visible = false;
            }
            else
            {
                btnDelete.Visible = true;
            }

        }
        private void totalBillSale()
        {
            // no of bill
            txtTotalBill.Text = dataGridView1.Rows.Count.ToString();

            // total sale amount
            double sum = 0;
            for(int i=0; i< dataGridView1.Rows.Count; i++)
            {
                sum += Convert.ToDouble(dataGridView1.Rows[i].Cells[4].Value);
            }
            txtTotalSale.Text = sum.ToString();

        }
        private void fillGrid()
        {
            con.Open();
            sql = "SELECT * FROM tbInvoice ORDER BY InvoiceID ASC";
            SqlDataAdapter da = new SqlDataAdapter(sql, con);
            con.Close();

            SqlCommandBuilder cb = new SqlCommandBuilder(da);
            DataTable dt = new DataTable();
            da.Fill(dt);
            dataGridView1.DataSource = dt;

            con.Close();
        }
        private void btnView_Click(object sender, EventArgs e)
        {
            con.Open();
            sql = "SELECT * FROM tbInvoice WHERE InvoiceDATE BETWEEN '"+dateTime1.Value.ToString("MM/dd/yyyy") + "' AND '" + dateTime2.Value.ToString("MM/dd/yyyy") + "' ORDER BY InvoiceID ";
            SqlDataAdapter da = new SqlDataAdapter(sql, con);
            DataSet ds = new DataSet();
            da.Fill(ds, "tbInvoice");
            dataGridView1.DataSource = ds.Tables["tbInvoice"];
            totalBillSale();
            con.Close();
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if(txtDelete.Text == "")
            {
                MessageBox.Show("Please select bill you want to delete");
            }
            else
            {
                DialogResult dr = MessageBox.Show("Are you sure you want to delete bill : "+txtDelete.Text,"", MessageBoxButtons.YesNo);

                if (dr == DialogResult.Yes)
                {
                    try
                    {
                        con.Open();
                        sql = "DELETE FROM tbInvoice WHERE InvoiceID = '" + txtDelete.Text + "' ";
                        cmd = new SqlCommand(sql, con);
                        cmd.ExecuteNonQuery();

                        con.Close();

                        MessageBox.Show("Delete Successfully : " + txtDelete.Text);
                        viewBills_Load(this, new EventArgs());
                        txtDelete.Text = "";
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                }
            }
            
            
        }

        private void dataGridView1_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
           
            InvoiceDetail up = new InvoiceDetail();

            up.txtBillNo.Text = this.dataGridView1.CurrentRow.Cells[0].Value.ToString();
            up.txtTotal.Text = this.dataGridView1.CurrentRow.Cells[2].Value.ToString();
            up.txtDisAmount.Text = this.dataGridView1.CurrentRow.Cells[3].Value.ToString();
            up.txtNetpay.Text = this.dataGridView1.CurrentRow.Cells[4].Value.ToString();

            up.Show();
            this.Hide();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            viewBills_Load(this, new EventArgs());
            fillGrid();
            dataGridView1.Refresh();
            txtDelete.Text = "";
        }

        private void dataGridView1_MouseClick(object sender, MouseEventArgs e)
        {
            DataGridViewRow dr = dataGridView1.SelectedRows[0];
            txtDelete.Text = dr.Cells[0].Value.ToString();
        }
    }
}
