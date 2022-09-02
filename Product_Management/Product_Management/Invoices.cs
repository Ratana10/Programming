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
    public partial class Invoices : Form
    {
        SqlConnection con = new SqlConnection("Data Source=RATANA10;Initial Catalog=dbShop;User ID=Sa;Password=123");
        SqlCommand cmd;
        string sql;

        public Invoices()
        {
            InitializeComponent();
            getProductNameFormDatabase();

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
        private void Invoices_Load(object sender, EventArgs e)
        {
            LoadBillNo();
        }

        private void btnDecrease_Click(object sender, EventArgs e)
        {
            if(txtQty.Text != "1")
            {
                txtQty.Text = (Convert.ToInt32(txtQty.Text) - 1).ToString();
            }
        }

        private void btnIncrease_Click(object sender, EventArgs e)
        {
            if(txtQty.Text != "")
            {
                txtQty.Text = (Convert.ToInt32(txtQty.Text) + 1).ToString();
            }
            
        }
        private int getQtyFromDB(int proID)
        {
            int qty = 0;

            try
            {
                con.Open();
                sql = "SELECT p.StockQty FROM tbProduct p WHERE p.ProID = @p1";
               
                cmd = new SqlCommand(sql, con);
                cmd.Parameters.AddWithValue("@p1", proID);

                if(cmd.ExecuteScalar() != null)
                {
                    qty = Convert.ToInt32(Convert.ToString(cmd.ExecuteScalar()));   
                }


                con.Close();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            return qty;
        }
        private void decreaseProductQty(int proID)
        {
            try
            {
                con.Open();
                sql = "UPDATE tbProduct SET StockQty = StockQty - @p3 WHERE ProID = @p1";

                cmd = new SqlCommand(sql, con);

                cmd.Parameters.AddWithValue("@p1", proID.ToString());
                cmd.Parameters.AddWithValue("@p3",txtQty.Text);
                cmd.ExecuteNonQuery();


                con.Close();
            }catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void increaseProductQty(int proID, int qty)
        {
            try
            {
                con.Open();
                sql = "UPDATE tbProduct SET StockQty = StockQty + @p3 WHERE ProID = @p1";
                cmd = new SqlCommand(sql, con);

                cmd.Parameters.AddWithValue("@p1", proID.ToString());
                cmd.Parameters.AddWithValue("@p3", qty.ToString());
                cmd.ExecuteNonQuery();

                con.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        private void btnAdd_Click(object sender, EventArgs e)
        {
            int proID = getProductID();
            //put qty into tbProduct 
            

            if (cbProName.Text == "")
            {
                MessageBox.Show("Please enter ProductName");
            }
            else if(txtQty.Text == "")
            {
                MessageBox.Show("please put product QTY");
            }
            else
            {
                if (txtQty.Text != "")
                {
                    int qty = getQtyFromDB(proID);
                    if (qty < Convert.ToInt32(txtQty.Text))
                    {
                        
                        MessageBox.Show("Product :" + proID+ " Instock : " + qty + " qty", "Out of Stock", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    }
                    
                    else
                    {
                        decreaseProductQty(proID);

                        bool found = false;
                        if (dataGridView1.Rows.Count > 0)
                        {
                            foreach (DataGridViewRow row in dataGridView1.Rows)
                            {
                                if (Convert.ToString(row.Cells[1].Value) == cbProName.Text)
                                {

                                    row.Cells[3].Value = Convert.ToString(Convert.ToInt16(row.Cells[3].Value) + Convert.ToInt16(txtQty.Text));

                                    row.Cells[4].Value = Convert.ToString(Convert.ToDouble(row.Cells[4].Value) + Convert.ToDouble(txtAmount.Text));
                                    found = true;
                                }
                            }
                            if (!found)
                            {
                                int row = 0;
                                dataGridView1.Rows.Add();
                                row = dataGridView1.Rows.Count - 1;

                                dataGridView1["ProductName", row].Value = cbProName.Text;
                                dataGridView1["Price", row].Value = txtPrice.Text;
                                dataGridView1["Qty", row].Value = txtQty.Text;
                                dataGridView1["Amount", row].Value = txtAmount.Text;
                                dataGridView1["BillNO", row].Value = txtBillNo.Text;
                                dataGridView1["ProID", row].Value = proID;

                            }
                        }
                        else
                        {
                            int row = 0;
                            dataGridView1.Rows.Add();
                            row = dataGridView1.Rows.Count - 1;

                            dataGridView1["ProductName", row].Value = cbProName.Text;
                            dataGridView1["Price", row].Value = txtPrice.Text;
                            dataGridView1["Qty", row].Value = txtQty.Text;
                            dataGridView1["Amount", row].Value = txtAmount.Text;
                            dataGridView1["BillNO", row].Value = txtBillNo.Text;
                            dataGridView1["ProID", row].Value = proID;

                            if (dataGridView1.Rows.Count > 0)
                            {
                                dataGridView1.CurrentCell = dataGridView1.Rows[dataGridView1.Rows.Count - 1].Cells[1];

                            }

                        }

                    }
                }
                /*
                 * Update using btnAdd
                else
                {
                    int i = Convert.ToInt32(txtDelUpdate.Text);
                    DataGridViewRow row = dataGridView1.Rows[i - 1];
                    row.Cells[1].Value = cbProName.Text;
                    row.Cells[2].Value = txtPrice.Text;
                    row.Cells[3].Value = txtQty.Text;
                    row.Cells [4].Value = txtAmount.Text;
                    row.Cells[5].Value = proID;

                }
                */

                clearText();
                gridTotal();
                totalQty();
            }
        }

        private void dataGridView1_RowPostPaint(object sender, DataGridViewRowPostPaintEventArgs e)
        {
            this.dataGridView1.Rows[e.RowIndex].Cells[0].Value = (e.RowIndex + 1).ToString();
        }

        private void LoadBillNo()
        {
            int a;

            con.Open();
            sql = "SELECT MAX(InvoiceID) FROM tbInvoice";
            cmd = new SqlCommand(sql, con);
            SqlDataReader reader = cmd.ExecuteReader();
            if (reader.Read())
            {
                string val = reader[0].ToString();
                if (val == "")
                {
                    txtBillNo.Text = "1";
                }
                else
                {
                    a = Convert.ToInt32(reader[0].ToString());

                    a = a + 1;
                    txtBillNo.Text = a.ToString();
                }
            }
            con.Close();
        }

        private void gridTotal()
        {
            try
            {
                int i = 0;
                double sum = 0;
                for (i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    sum += Convert.ToDouble(dataGridView1.Rows[i].Cells[4].Value);
                }
                txtTotal.Text = sum.ToString();
            }catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
           
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
            if(amt > 0)
            {
                txtAmount.Text = amt.ToString("C").Remove(0,1);
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
        private void txtQty_Leave(object sender, EventArgs e)
        {
            callAmount();
            getPriceFromDB();
        }
        private void txtQty_TextChanged(object sender, EventArgs e)
        {
            callAmount();
            getPriceFromDB();
        }



        private void getPriceFromDB()
        {
            try
            {
                con.Open();
                sql = "SELECT UnitPrice FROM tbProduct WHERE ProName = @p1";
                cmd = new SqlCommand(sql, con);
                cmd.Parameters.AddWithValue("@p1", cbProName.Text);
                
                if(cmd.ExecuteScalar() != null)
                {
                    txtPrice.Text = cmd.ExecuteScalar().ToString();
                }

                con.Close();
            }catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        

        private void btnPay_Click(object sender, EventArgs e)
        {
            int staffID = FLogin.LoginStaffID;
            if(dataGridView1.Rows.Count < 1)
            {
                MessageBox.Show("No Product select");
            }
            else
            {
                try
                {
                    con.Open();
                    sql = "INSERT INTO tbInvoice VALUES(@p1, @p2, @p3, @p4, @p5)";
                    cmd = new SqlCommand(sql, con);
                    cmd.Parameters.AddWithValue("@p1", dateTimeDate.Value.ToString());
                    cmd.Parameters.AddWithValue("@p2", txtTotal.Text);
                    cmd.Parameters.AddWithValue("@p3", txtDisAmount.Text);
                    cmd.Parameters.AddWithValue("@p4", txtNetpay.Text);
                    cmd.Parameters.AddWithValue("@p5", staffID);
                    cmd.ExecuteNonQuery();
                    con.Close();

                   
                    for(int i=0; i<dataGridView1.Rows.Count; i++)
                    {
                        try
                        {
                            con.Open();
                            //insert into table Invoice Detail
                            sql = "INSERT INTO tbInvoiceDetail VALUES(@p0, @p1, @p2, @p3, @p4, @p5) ";
                            cmd = new SqlCommand(sql, con);

                            cmd.Parameters.AddWithValue("@p0", dataGridView1.Rows[i].Cells[0].Value.ToString());
                            cmd.Parameters.AddWithValue("@p1", dataGridView1.Rows[i].Cells[6].Value.ToString());
                            cmd.Parameters.AddWithValue("@p2", dataGridView1.Rows[i].Cells[2].Value.ToString());
                            cmd.Parameters.AddWithValue("@p3", dataGridView1.Rows[i].Cells[3].Value.ToString());
                            cmd.Parameters.AddWithValue("@p4", dataGridView1.Rows[i].Cells[4].Value.ToString());
                            cmd.Parameters.AddWithValue("@p5", dataGridView1.Rows[i].Cells[5].Value.ToString());

                            cmd.ExecuteNonQuery();
                            con.Close();

                            

                        }
                        catch(Exception ex)
                        {
                            MessageBox.Show(ex.ToString());
                        }
                    }

                    // update qty in tbProduct
                    /*
                    for (int i = 0; i < dataGridView1.Rows.Count; i++)
                    {
                        try
                        {
                            con.Open();
                            //insert into table Invoice Detail
                            sql = "UPDATE tbProduct SET StockQty = StockQty - @p3 WHERE ProID = @p1";
                            cmd = new SqlCommand(sql, con);

                            cmd.Parameters.AddWithValue("@p1", dataGridView1.Rows[i].Cells[6].Value.ToString());
                            cmd.Parameters.AddWithValue("@p3", dataGridView1.Rows[i].Cells[3].Value.ToString());
                            cmd.ExecuteNonQuery();
                            con.Close();



                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show(ex.ToString());
                        }
                    }
                    */

                    LoadBillNo();
                    btnClear_Click(this, new EventArgs());

                    dataGridView1.Rows.Clear();
                    dataGridView1.Refresh();
                }catch(Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
            }
        }
        private int getProductID()
        {
            int proID = 0;
            try
            {

                con.Open();
                sql = "SELECT ProID FROM tbProduct WHERE ProName = '" + cbProName.Text + "'";
                cmd = new SqlCommand(sql, con);
     
                if(cmd.ExecuteScalar() != null)
                {
                    proID = Convert.ToInt32 (cmd.ExecuteScalar());
                }

                con.Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
            
            return proID;
        }
        private void txtDisAmount_TextChanged(object sender, EventArgs e)
        {
            calDiscout();
        }

        private void txtTotal_TextChanged(object sender, EventArgs e)
        {
            calDiscout();
        }

        private void cbProName_SelectedValueChanged(object sender, EventArgs e)
        {
            getPriceFromDB();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            cbProName.ResetText();
            txtQty.Text = "";
            txtPrice.Text = "";
            txtAmount.Text = "";
            txtTotal.Text = "";
            txtDisAmount.Text = "";
            txtNetpay.Text = "";
            txtTotalQty.Text = "";
            txtDelUpdate.Text = "";

            dateTimeDate.Value = DateTime.Now;
            dataGridView1.Rows.Clear();
            dataGridView1.Refresh();

        }
        private void clearText()
        {
            cbProName.ResetText();
            txtQty.Text = "";
            txtPrice.Text = "";
            txtAmount.Text = "";
            
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            foreach (DataGridViewRow row in dataGridView1.SelectedRows)
            {

                if (!row.IsNewRow)
                {
                    int qty =Convert.ToInt32( row.Cells[3].Value.ToString());
                    int proID = Convert.ToInt32(row.Cells[6].Value.ToString());
                    increaseProductQty(proID, qty);
                    dataGridView1.Rows.Remove(row);
                }
                    
               
            }
        }

        private void bnUpdate_Click(object sender, EventArgs e)
        {
            int proID = getProductID();
            int i = Convert.ToInt32(txtDelUpdate.Text);
            DataGridViewRow row = dataGridView1.Rows[i - 1];
            row.Cells[1].Value = cbProName.Text;
            row.Cells[2].Value = txtPrice.Text;
            row.Cells[3].Value = txtQty.Text;
            row.Cells[4].Value = txtAmount.Text;
            row.Cells[5].Value = proID;

            btnClear_Click(this, new EventArgs());
        }

        private void dataGridView1_CellDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            try
            {
                int i = e.RowIndex;
                DataGridViewRow row = dataGridView1.Rows[i];

                txtDelUpdate.Text = row.Cells[0].Value.ToString();
                cbProName.Text = row.Cells[1].Value.ToString();
                txtQty.Text = row.Cells[3].Value.ToString();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }

        private void txtQty_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                btnAdd_Click(this, new EventArgs());
            }
        }

        private void cbProName_TextChanged(object sender, EventArgs e)
        {
            txtQty.Text = "1";
            callAmount();
        }
    }
}
