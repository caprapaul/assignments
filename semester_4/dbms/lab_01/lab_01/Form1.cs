using System;
using System.Data;
using System.Data.SqlClient;

using System.Windows.Forms;

namespace lab_01
{
    public partial class Form1 : Form
    {
        private SqlConnection _connection;
        private SqlDataAdapter _daCategories;
        private SqlDataAdapter _daProducts;
        private DataSet _dataSet;
        private BindingSource _bsCategories;
        private BindingSource _bsProducts;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _connection =
                new SqlConnection(
                    @"Data Source = DESKTOP-CMIOIHP\SQLEXPRESS; Initial Catalog = coffee_shops; Integrated Security = True");
            
            _dataSet = new DataSet();

            _daCategories = new SqlDataAdapter("SELECT * FROM ProductCategories", _connection);
            _daProducts = new SqlDataAdapter("SELECT * FROM CoffeeProducts", _connection);
            new SqlCommandBuilder(_daProducts);
            _bsCategories = new BindingSource();
            _bsProducts = new BindingSource();
            
            Fill();

            DataRelation dataRelation = new DataRelation(
                "FK_CategoriesProducts",
                _dataSet.Tables["ProductCategories"].Columns["Id"],
                _dataSet.Tables["CoffeeProducts"].Columns["CategoryId"]
            );
            _dataSet.Relations.Add(dataRelation);
            
            _bsCategories.DataSource = _dataSet;
            _bsCategories.DataMember = "ProductCategories";
            
            _bsProducts.DataSource = _bsCategories;
            _bsProducts.DataMember = "FK_CategoriesProducts";

            dgvCategories.DataSource = _bsCategories;
            dgvProducts.DataSource = _bsProducts;
        }

        private void Fill()
        {
            _connection.Open();
            
            _daCategories.Fill(_dataSet, "ProductCategories");
            _daProducts.Fill(_dataSet, "CoffeeProducts");
            
            _connection.Close();
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            _daProducts.Update(_dataSet, "CoffeeProducts");
        }

        private void RefreshButton_Click(object sender, EventArgs e)
        {
            _dataSet.Clear();
            Fill();
        }
    }
}