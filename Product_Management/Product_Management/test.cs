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
    public partial class test : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;

        int ID;

        public test()
        {
      
            InitializeComponent();
        }

        private void test_Load(object sender, EventArgs e)
        {
            con.Open();

            cmd = con.CreateCommand();
            cmd.CommandType = CommandType.Text;
            sql = "SELECT p.ProID, p.ProName, p.StockQty, p.UnitPrice,t.Type FROM tbProduct p INNER JOIN tbProductType t  ON p.TypeID = t.TypeID";
            cmd.CommandText = sql;
            cmd.ExecuteNonQuery();

            DataTable dt = new DataTable();
            SqlDataAdapter da = new SqlDataAdapter(cmd);

            da.Fill(dt);
            dataGridView1.DataSource = dt;

            con.Close();
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

                    test_Load(this, new EventArgs());
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

       


        private int getTypeID()
        {
            int typeID = 0;
            try
            {
               
                con.Open();
                sql = "SELECT TypeID FROM tbProductType WHERE Type = '" + cbType.Text + "'";
                cmd = new SqlCommand(sql, con);
                //md.Parameters.AddWithValue("@p1", cbType.Text);
                SqlDataReader reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    MessageBox.Show("Testing");

                    typeID = Convert.ToInt32(reader["TypeID"]);
                }
                con.Close();
             
               MessageBox.Show(typeID.ToString());
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            return typeID;
        }

       
    }
}
