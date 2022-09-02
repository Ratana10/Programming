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
    public partial class FUpdateBills : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;


        public FUpdateBills()
        {
            InitializeComponent();
            getProductNameFormDatabase();
        }

        private void FUpdateBills_Load(object sender, EventArgs e)
        {
            con.Open();
            
            cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            sql = "SELECT * FROM tbInvoiceDetail WHERE InvoiceID LIKE ('" + txtBillNo.Text + "%' )";
            cmd.CommandText = sql;
            cmd.ExecuteNonQuery();

            DataTable dt = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);

            da.Fill(dt);
            dataGridView1.DataSource = dt;

            con.Close();
            dataGridView1.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;


            //fill products name foorm product tabel to products combobox



        }

        void getProductNameFormDatabase()
        {
            // cbStaffID
            sql = "SELECT ProName FROM tbProduct ORDER BY ProID ASC";
            cmd = new SqlCommand(sql, con);

            DataTable dt1 = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            da.Fill(dt1);
            foreach (DataRow dr in dt1.Rows)
            {
                cbProName.Items.Add(dr["ProName"]).ToString();
            }
        }

        private void btnDecrease_Click(object sender, EventArgs e)
        {
            if (txtQty.Text != "1")
            {
                txtQty.Text = (Convert.ToInt32(txtQty.Text) - 1).ToString();
            }
        }

        private void btnIncrease_Click(object sender, EventArgs e)
        {
            if (txtQty.Text != "")
            {
                txtQty.Text = (Convert.ToInt32(txtQty.Text) + 1).ToString();
            }

        }
        private void gridTotal()
        {
            int i = 0;
            double sum = 0;
            for (i = 0; i < dataGridView1.Rows.Count; i++)
            {
                sum += Convert.ToDouble(dataGridView1.Rows[i].Cells[4].Value);
            }
            txtTotal.Text = sum.ToString();
            txtTotalPro.Text = i.ToString();
        }

        private void totalQty()
        {
            int i = 0;
            double sum = 0;
            for (i = 0; i < dataGridView1.Rows.Count; i++)
            {
                sum += Convert.ToDouble(dataGridView1.Rows[i].Cells[4].Value);
            }
            txtTotalQty.Text = sum.ToString();
        }
        private void callAmount()
        {
            double a, b, amt;
            double.TryParse(txtQty.Text, out a);
            double.TryParse(txtPrice.Text, out b);
            amt = a * b;
            if (amt > 0)
            {
                txtAmount.Text = amt.ToString("C").Remove(0, 1);
            }
        }
        private void calDiscout()
        {
            double a, b, amt;
            double.TryParse(txtTotal.Text, out a);
            double.TryParse(txtDisAmount.Text, out b);
            amt = a - b;
            if (amt > 0)
            {
                txtNetpay.Text = amt.ToString("C").Remove(0, 1);
            }

        }
        private void getPriceFromDB()
        {
            try
            {
                con.Open();
                sql = "SELECT UnitPrice FROM tbProduct WHERE ProName = @p1";
                cmd = new SqlCommand(sql, con);
                cmd.Parameters.AddWithValue("@p1", cbProName.Text);

                SqlDataReader reader = cmd.ExecuteReader();
                double price;
                while (reader.Read())
                {
                    txtPrice.Text = reader["UnitPrice"].ToString();
                }


                con.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void cbProName_TextChanged(object sender, EventArgs e)
        {
            getPriceFromDB();
        }

        private void txtQty_TextChanged(object sender, EventArgs e)
        {
            callAmount();
        }
        private void LoadSerialNO()
        {
            int i = 1;
            foreach (DataGridViewRow row in dataGridView1.Rows)
            {
                row.Cells[i].Value = i;
                i++;
            }
        }

        private void dataGridView1_RowsAdded(object sender, DataGridViewRowsAddedEventArgs e)
        {
            LoadSerialNO();
        }

        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                int i = e.RowIndex;
                DataGridViewRow row = dataGridView1.Rows[i];
                txtDelUpdate.Text = row.Cells[0].Value.ToString();
                cbProName.Text = row.Cells[1].Value.ToString();
                txtPrice.Text = row.Cells[2].Value.ToString();
                txtQty.Text = row.Cells[3].Value.ToString();
                txtAmount.Text = row.Cells[4].Value.ToString();
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            foreach(DataGridViewRow row in dataGridView1.SelectedRows)
            {
                if (!row.IsNewRow)
                    dataGridView1.Rows.Remove(row);
                LoadSerialNO();
            }
        }

        private void bnUpdate_Click(object sender, EventArgs e)
        {

        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            
        }
    }
}
