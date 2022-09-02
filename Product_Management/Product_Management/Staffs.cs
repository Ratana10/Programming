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
using System.Globalization;

namespace Product_Management
{
    public partial class Staffs : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;


        public Staffs()
        {
            InitializeComponent();
        }

        private void Staffs_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'dbShopDataSet1.tbStaff' table. You can move, or remove it, as needed.
            this.tbStaffTableAdapter.Fill(this.dbShopDataSet1.tbStaff);
            btnClear_Click(this, new EventArgs());

            txtFName.Select();
            btnAdd.Visible = true;
            btnDelete.Visible = false;
        }
        private Boolean getStop()
        {
            String b = cbStop.Text;
            return (b == "True") ? true : false;
        }
        private char getGender()
        {

            return (rdMale.Checked == true) ? 'M' : 'F';

        }
        private void setGender(string gender)
        {
            if (gender == "M")
            {
                rdMale.Checked = true;
            }
            else
            {
                rdFemale.Checked = true;
            }
        }
      

        private void dataGridView1_CellMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            int i = e.RowIndex;
            if (i == -1) return;
            try
            {
                DataGridViewRow row = dataGridView1.Rows[i];

                txtID.Text = row.Cells[0].Value.ToString();
                txtFName.Text = row.Cells[1].Value.ToString();
                txtLName.Text = row.Cells[2].Value.ToString();
                String gender = row.Cells[3].Value.ToString();
                setGender(gender);

                //date time formart
                var formatInfo = new DateTimeFormatInfo();
                dateTimeDOB.Value = Convert.ToDateTime(row.Cells[4].Value.ToString(), formatInfo);

                txtPosition.Text = row.Cells[5].Value.ToString();
                txtSalary.Text = row.Cells[6].Value.ToString();
                txtPhone.Text = row.Cells[7].Value.ToString();
                txtLocation.Text = row.Cells[8].Value.ToString();
                dateTimeHire.Value = Convert.ToDateTime(row.Cells[9].Value.ToString(), formatInfo);
                cbStop.Text = row.Cells[10].Value.ToString();

                btnAdd.Visible = false;
                btnDelete.Visible = true;

            }catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

      

        

        

        private void btnAdd_Click(object sender, EventArgs e)
        {
           
            if (txtLName.Text == "" || txtFName.Text == "")
            {
                MessageBox.Show("Please fill the name");
            }
            else
            {
                try
                {
                    con.Open();
                    sql = "INSERT INTO tbStaff VALUES(@p1, @p2, @p3, @p4, @p5, @p6, @p7, @p8, @p9, @p10 )";

                    cmd = new SqlCommand(sql, con);
                    cmd.Parameters.AddWithValue("@p1", txtFName.Text);
                    cmd.Parameters.AddWithValue("@p2", txtLName.Text);
                    cmd.Parameters.AddWithValue("@p3", getGender());
                    cmd.Parameters.AddWithValue("@p4", dateTimeDOB.Value.ToString());
                    cmd.Parameters.AddWithValue("@p5", txtPosition.Text);
                    cmd.Parameters.AddWithValue("@p6", txtSalary.Text);
                    cmd.Parameters.AddWithValue("@p7", txtPhone.Text);
                    cmd.Parameters.AddWithValue("@p8", txtLocation.Text);
                    cmd.Parameters.AddWithValue("@p9", dateTimeHire.Value.ToString());
                    cmd.Parameters.AddWithValue("@p10", getStop());
                    cmd.ExecuteNonQuery();
                    con.Close();

                    MessageBox.Show("Added Successfully");
                    Staffs_Load(this, new EventArgs());
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
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
                DialogResult dr = MessageBox.Show("Are you sure you want to delete the StaffID : " + txtID.Text + "  ?", "", MessageBoxButtons.YesNo);
                if (dr == DialogResult.Yes)
                {


                    try
                    {
                        con.Open();
                        sql = "DELETE FROM tbStaff WHERE StaffID = @p0";
                        cmd = new SqlCommand(sql, con);
                        cmd.Parameters.AddWithValue("@p0", txtID.Text);
                        int numberOfRowAffected = cmd.ExecuteNonQuery();

                        con.Close();

                        Staffs_Load(this, new EventArgs());
                        if (numberOfRowAffected == 0)
                        {
                            MessageBox.Show("No Staff Selected");
                        }
                        else
                        {
                            MessageBox.Show("Delete Staff Successfully");
                        }


                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                }
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            if (txtLName.Text == "" || txtFName.Text == "")
            {
                MessageBox.Show("Please fill the name");
            }
            else
            {
                try
                {
                    con.Open();


                    sql = "UPDATE tbStaff SET StaffFName = @p1, StaffLName = @p2, Gender=@p3, DOB=@p4, Position=@p5, Salary=@p6, Phone=@p7, Address=@p8, Hiredate=@p9, StopWork=@p10  WHERE StaffID = @p0";
                    cmd = new SqlCommand(sql, con);

                    cmd.Parameters.AddWithValue("@p1", txtFName.Text);
                    cmd.Parameters.AddWithValue("@p2", txtLName.Text);
                    cmd.Parameters.AddWithValue("@p3", getGender());
                    cmd.Parameters.AddWithValue("@p4", dateTimeDOB.Value.ToString());
                    cmd.Parameters.AddWithValue("@p5", txtPosition.Text);
                    cmd.Parameters.AddWithValue("@p6", txtSalary.Text);
                    cmd.Parameters.AddWithValue("@p7", txtPhone.Text);
                    cmd.Parameters.AddWithValue("@p8", txtLocation.Text);
                    cmd.Parameters.AddWithValue("@p9", dateTimeHire.Value.ToString());
                    cmd.Parameters.AddWithValue("@p10", getStop());
                    cmd.Parameters.AddWithValue("@p0", txtID.Text);
                    cmd.ExecuteNonQuery();
                    con.Close();


                    Staffs_Load(this, new EventArgs());
                    MessageBox.Show("Update Successfully");

                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            txtID.Text = "";
            txtFName.Text = "";
            txtLName.Text = "";
            rdMale.Focus();
            dateTimeDOB.Value = DateTime.Now; // dob
            txtPosition.Text = "";
            txtSalary.Text = "";
            txtPhone.Text = "";
            txtLocation.SelectedIndex = 10;
            dateTimeHire.Value = DateTime.Now; //hiredate
            cbStop.SelectedIndex = 0;
            txtFName.Select();

            btnAdd.Visible = true;
            btnDelete.Visible = false;

        }
    }
}
