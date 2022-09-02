using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Product_Management
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
          
            if(FLogin.LoginAccountType != "Admin")
            {
                menuAccout.Visible = false;
                menuStaff.Visible = false;

            }
        }

       

        

        private void btnLogout_Click(object sender, EventArgs e)
        {
            FLogin.LoginAccountID = null;
            FLogin.LoginAccountType = null;
            FLogin.LoginStaffID = 0;

            new FLogin().Show();
            this.Hide();
        }

        private void menuInvoice_Click(object sender, EventArgs e)
        {
            new Invoices().Show();
        }

        private void menuBill_Click(object sender, EventArgs e)
        {
            new viewBills().Show();
        }

        private void menuProduct_Click(object sender, EventArgs e)
        {
            new Products().Show();
        }

        private void menuProductType_Click(object sender, EventArgs e)
        {
            new ProductType().Show();
        }

        private void menuAccout_Click(object sender, EventArgs e)
        {
            new Accounts().Show();
        }

        private void menuStaff_Click(object sender, EventArgs e)
        {
            new Staffs().Show();
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }
    }
}
