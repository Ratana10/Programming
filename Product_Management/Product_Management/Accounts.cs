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
    public partial class Accounts : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;

        public Accounts()
        {
            InitializeComponent();
            getCbStaffID();
        }

        private void Accounts_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'dbShopDataSetAccount.tbAccount' table. You can move, or remove it, as needed.
            this.tbAccountTableAdapter.Fill(this.dbShopDataSetAccount.tbAccount);
            //get all staffID
            //clear 
            
            btnClear_Click(this, new EventArgs());
        }
        private void getCbStaffID()
        {
            // cbStaffID
            sql = "SELECT StaffID FROM tbStaff ORDER BY StaffID ASC";
            cmd = new SqlCommand(sql, con);

            DataTable dt1 = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);
            da.Fill(dt1);
            foreach(DataRow dr in dt1.Rows)
            {
                txtID.Items.Add(dr["StaffID"]).ToString();
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
                txtID.Text = row.Cells[4].Value.ToString();
                txtUsername.Text = row.Cells[1].Value.ToString();
                txtPassword.Text = row.Cells[2].Value.ToString();
                cbType.Text = row.Cells[3].Value.ToString();

                btnSave.Visible = false;
                btnDelete.Visible = true;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }


        private void btnUpdate_Click(object sender, EventArgs e)
        {

            if (txtID.Text == "")
            {
                MessageBox.Show("Please enter Staff ID to update");
            }
            try
            {
                con.Open();

                sql = "UPDATE tbAccount SET Username = @p1, Password = @p2 , Type=@p3 WHERE StaffID = @p4";

                cmd = new SqlCommand(sql, con);
                cmd.Parameters.AddWithValue("@p1", txtUsername.Text);
                cmd.Parameters.AddWithValue("@p2", txtPassword.Text);
                cmd.Parameters.AddWithValue("@p3", cbType.Text);
                cmd.Parameters.AddWithValue("@p4", txtID.Text);

                cmd.ExecuteNonQuery();
                con.Close();

                MessageBox.Show("Update Successfully");

                Accounts_Load(this, new EventArgs());

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

      

        private void btnDelete_Click(object sender, EventArgs e)
        {
            if (txtID.Text == "")
            {
                MessageBox.Show("Please enter Staff ID");
            }
            else
            {
                DialogResult dr = MessageBox.Show("Are you sure you want to delete the Account StaffID : " + txtID.Text + "  ?", "", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {


                    try
                    {
                        con.Open();
                        sql = "DELETE FROM tbAccount WHERE StaffID = @p0";
                        cmd = new SqlCommand(sql, con);
                        cmd.Parameters.AddWithValue("@p0", txtID.Text);
                        int numberOfRowAffected = cmd.ExecuteNonQuery();

                        con.Close();

                        Accounts_Load(this, new EventArgs());
                        if (numberOfRowAffected == 0)
                        {
                            MessageBox.Show("No Account Selected");
                        }
                        else
                        {
                            MessageBox.Show("Delete Account Successfully");
                        }


                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                }
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtID.Text = "";
            txtUsername.Text = "";
            txtPassword.Text = "";
            cbType.Text = "";
            txtID.Select();

            btnSave.Visible = true;
            btnDelete.Visible = false;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (txtID.Text == "")
            {
                MessageBox.Show("Please fill the name");
            }
            else
            {
                try
                {
                    con.Open();
                    sql = "INSERT INTO tbAccount VALUES(@p1, @p2, @p3, @p4)";

                    cmd = new SqlCommand(sql, con);
                    cmd.Parameters.AddWithValue("@p1", txtUsername.Text);
                    cmd.Parameters.AddWithValue("@p2", txtPassword.Text);
                    cmd.Parameters.AddWithValue("@p3", cbType.Text);
                    cmd.Parameters.AddWithValue("@p4", txtID.Text);

                    cmd.ExecuteNonQuery();
                    con.Close();

                    MessageBox.Show("Create Successfully");
                    Accounts_Load(this, new EventArgs());
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }
    }
}
