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
    public partial class ProductType : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;


        public ProductType()
        {
            InitializeComponent();
        }

        private void ProductType_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'dbShopDataSetProductType.tbProductType' table. You can move, or remove it, as needed.
            this.tbProductTypeTableAdapter.Fill(this.dbShopDataSetProductType.tbProductType);

            btnClear_Click(this, new EventArgs());

            btnAdd.Visible = true;
            btnDelete.Visible = false;

        }

        private void btnAdd_Click(object sender, EventArgs e)
        {
            if (txtTypeName.Text == "")
            {
                MessageBox.Show("Please fill the Product Type");
            }
            else
            {
                try
                {
                    con.Open();
                    sql = "INSERT INTO tbProductType VALUES(@p1)";

                    cmd = new SqlCommand(sql, con);
                    cmd.Parameters.AddWithValue("@p1", txtTypeName.Text);
                    

                    cmd.ExecuteNonQuery();
                    con.Close();

                    MessageBox.Show("Add Successfully");
                    ProductType_Load(this, new EventArgs());
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
           
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtTypeID.Text = "";
            txtTypeName.Text = "";
            txtTypeName.Select();

            btnAdd.Visible = true;
            btnDelete.Visible = false;

        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            if (txtTypeName.Text == "")
            {
                MessageBox.Show("Please Select ProductType update");
            }
            try
            {
                con.Open();

                sql = "UPDATE tbProductType SET Type=@p1 WHERE TypeID = @p0";

                cmd = new SqlCommand(sql, con);
                cmd.Parameters.AddWithValue("@p1", txtTypeName.Text);
                cmd.Parameters.AddWithValue("@p0", txtTypeID.Text);
                

                cmd.ExecuteNonQuery();
                con.Close();

                MessageBox.Show("Update Successfully");

                ProductType_Load(this, new EventArgs());

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (txtTypeID.Text == "")
            {
                MessageBox.Show("Please select ProductType ");
            }
            else
            {
                DialogResult dr = MessageBox.Show("Are you sure you want to delete the TypeID  : " + txtTypeID.Text + "  ?", "", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {


                    try
                    {
                        con.Open();
                        sql = "DELETE FROM tbProductType WHERE TypeID = @p0";
                        cmd = new SqlCommand(sql, con);
                        cmd.Parameters.AddWithValue("@p0", txtTypeID.Text);
                        int numberOfRowAffected = cmd.ExecuteNonQuery();

                        con.Close();

                        ProductType_Load(this, new EventArgs());
                        if (numberOfRowAffected == 0)
                        {
                            MessageBox.Show("No ProductType Selected");
                        }
                        else
                        {
                            MessageBox.Show("Delete Successfully");
                        }


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
            //avoid double click on header
            int i = e.RowIndex;
            if (i == -1) return;

            try
            {
                
                DataGridViewRow row = dataGridView1.Rows[i];
                txtTypeID.Text = row.Cells[0].Value.ToString();
                txtTypeName.Text = row.Cells[1].Value.ToString();


                btnAdd.Visible = false;
                btnDelete.Visible = true;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
