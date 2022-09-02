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
    public partial class FLogin : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand command;
        string sql;

        public static Int32? LoginAccountID;
        public static string LoginAccountType;
        public static int LoginStaffID;


        public FLogin()
        {
            InitializeComponent();
            txtUsername.Select();
        }

        private void btnLogin_Click(object sender, EventArgs e)
        {
            if (txtUsername.Text != "" && txtPassword.Text != "")
            {
                try
                {
                    con.Open();
                    sql = "SELECT * FROM tbAccount WHERE Username = @p1 AND Password = @p2";
                    command = new SqlCommand(sql, con);
                    command.Parameters.AddWithValue("@p1", txtUsername.Text);
                    command.Parameters.AddWithValue("@p2", txtPassword.Text);
                    SqlDataReader reader = command.ExecuteReader();

                    while (reader.Read())
                    {
                        LoginAccountID = Convert.ToInt32(reader["AccID"]);
                        LoginAccountType = reader["Type"].ToString();
                        LoginStaffID = Convert.ToInt32(reader["StaffID"]);
                    }
                    con.Close();

                    if (LoginAccountID == null)
                    {
                        MessageBox.Show("Incorrect username or password");
                    }
                    else
                    {
                        new Form1().Show();
                        this.Hide();
                    }
                    btnCancle_Click(this, new EventArgs());
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
            else if (txtUsername.Text == "" && txtPassword.Text == "")
            {
                MessageBox.Show("Please fill in Password and Password");
            }
            else if (txtUsername.Text == "")
            {
                MessageBox.Show("Please fill in Username");
            }
            else if (txtPassword.Text == "")
            {
                MessageBox.Show("Please fill in Password");
            }
        }

        private void btnCancle_Click(object sender, EventArgs e)
        {
            txtUsername.Text = "";
            txtPassword.Text = "";
        }

        private void txtPassword_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                btnLogin_Click(this, new EventArgs());
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
    }
}
