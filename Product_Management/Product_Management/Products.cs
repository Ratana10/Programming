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
    public partial class Products : Form
    {

        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;

        public Products()
        {
            InitializeComponent();
            getCbProduct();
        }

        private void Products_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'dbShopDataSet.tbProduct' table. You can move, or remove it, as needed.
            this.tbProductTableAdapter.Fill(this.dbShopDataSet.tbProduct);
            grid();
            //cb Prouct

            btnClear_Click(this, new EventArgs());

            txtProName.Select();

            btnAdd.Visible = true;
            btnDelete.Visible = false;
        }
        private void grid()
        {
            con.Open();

            cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            sql = "SELECT p.ProID, p.ProName, p.StockQty, p.UnitPrice,t.Type FROM tbProduct AS p INNER JOIN tbProductType AS t  ON p.TypeID = t.TypeID";
            cmd.CommandText = sql;
            cmd.ExecuteNonQuery();

            DataTable dt = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);

            da.Fill(dt);
            dataGridView1.DataSource = dt;

            con.Close();
        }
        private void getCbProduct()
        {
            // cbProdcutType
            sql = "SELECT Type FROM tbProductType ORDER BY Type ASC";
            cmd = new SqlCommand(sql, con);

            DataTable dt = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            da.Fill(dt);
            foreach (DataRow dr in dt.Rows)
            {
                cbType.Items.Add(dr["Type"]).ToString();
            }
        }

        private int getTypeID()
        {
            int typeID = 0;
            try
            {

                con.Open();
                sql = "SELECT TypeID FROM tbProductType WHERE Type = '" + cbType.Text + "'";
                cmd = new SqlCommand(sql, con);
                SqlDataReader reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    typeID = Convert.ToInt32(reader["TypeID"]);
                }
                con.Close();

                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            return typeID;
        }

        private void dataGridView1_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            //avoid double click on header
            int i = e.RowIndex;
            if (i == -1) return;

            try
            {
                
                DataGridViewRow row = dataGridView1.Rows[i];
                txtProID.Text = row.Cells[0].Value.ToString();
                txtProName.Text = row.Cells[1].Value.ToString();
                txtStockQty.Text = row.Cells[2].Value.ToString();
                txtUnitPrice.Text = row.Cells[3].Value.ToString();
                cbType.Text = row.Cells[4].Value.ToString();
                btnAdd.Visible = false;
                btnDelete.Visible = true;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

       

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtProName.Text = "";
            txtStockQty.Text = "";
            txtUnitPrice.Text = "";
            txtProID.Text = "";
            cbType.Text = "";
            btnAdd.Visible = true;
            btnDelete.Visible = false;
        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            int typeID = getTypeID();
            if (txtProName.Text != "" && txtUnitPrice.Text != "")
            {
                try
                {
                    con.Open();
                    sql = "INSERT INTO tbProduct VALUES(@p1, @p2, @p3, @p4)";

                    cmd = new SqlCommand(sql, con);
                    cmd.Parameters.AddWithValue("@p1", txtProName.Text);
                    cmd.Parameters.AddWithValue("@p2", txtStockQty.Text);
                    cmd.Parameters.AddWithValue("@p3", txtUnitPrice.Text);
                    cmd.Parameters.AddWithValue("@p4", typeID);
                    cmd.ExecuteNonQuery();
                    con.Close();

                    MessageBox.Show("Added Successfully");

                    Products_Load(this, new EventArgs());
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }


            }
            else
            {
                MessageBox.Show("Please fill in the Product name and UnitPrice");
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            int typeID = getTypeID();
            try
            {
                con.Open();

                sql = "UPDATE tbProduct SET ProName = @p1, UnitPrice = @p2 , StockQty=@p3, TypeID=@p4 WHERE ProID = @p5";

                cmd = new SqlCommand(sql, con);
                cmd.Parameters.AddWithValue("@p1", txtProName.Text);
                cmd.Parameters.AddWithValue("@p2", txtUnitPrice.Text);
                cmd.Parameters.AddWithValue("@p3", txtStockQty.Text); 
                cmd.Parameters.AddWithValue("@p4", typeID);
                cmd.Parameters.AddWithValue("@p5", txtProID.Text);
                cmd.ExecuteNonQuery();
                con.Close();

                MessageBox.Show("Update Successfully");
                btnClear_Click(this, new EventArgs());
                Products_Load(this, new EventArgs());

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (txtProID.Text == "" || txtProName.Text == "")
            {
                MessageBox.Show("Please enter ProductID or ProductName");
            }
            else
            {
                DialogResult dr = MessageBox.Show("Are you sure you want to delete the ProductName : " + txtProName.Text + "  ?", "", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {


                    try
                    {
                        con.Open();
                        sql = "DELETE FROM tbProduct WHERE ProID = @p1";
                        cmd = new SqlCommand(sql, con);
                        cmd.Parameters.AddWithValue("@p1", txtProID.Text);
                        int numberOfRowAffected = cmd.ExecuteNonQuery();

                        con.Close();
                        if (numberOfRowAffected == 0)
                        {
                            MessageBox.Show("No Product Selected");
                        }
                        else
                        {
                            MessageBox.Show("Deleted Successfully");
                        }

                        Products_Load(this, new EventArgs());
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                }
            }
        }

        
    }
}
