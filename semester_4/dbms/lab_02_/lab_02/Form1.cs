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

namespace lab_02
{
    public partial class Form1 : Form
    {
        private SqlConnection _connection;
        private DataSet _dataSet;
        private SqlDataAdapter _employeesDataAdapter;
        private SqlDataAdapter _reportsToDataAdapter;
        private SqlCommandBuilder _employeesCommandBuilder;
        private BindingSource _employeesBindingSource;
        private BindingSource _reportsToBindingSource;
        
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _connection = new SqlConnection(@"Data Source = DESKTOP-CMIOIHP\SQLEXPRESS; Initial Catalog = Northwind; Integrated Security = True");
            _connection.Open();
            _dataSet = new DataSet();
            _employeesDataAdapter = new SqlDataAdapter("SELECT * FROM Employees", _connection);
            _reportsToDataAdapter = new SqlDataAdapter("SELECT * FROM Employees", _connection);
            _employeesCommandBuilder = new SqlCommandBuilder(_employeesDataAdapter);

            _employeesDataAdapter.Fill(_dataSet, "Employees");
            _reportsToDataAdapter.Fill(_dataSet, "Employees");

            DataRelation dataRelation = new DataRelation("FK_Employees_Employees",
                _dataSet.Tables["Employees"].Columns["EmployeeID"],
                _dataSet.Tables["Employees"].Columns["ReportsTo"]);
            //_dataSet.Relations.Add(dataRelation);

            _employeesBindingSource = new BindingSource();
            _reportsToBindingSource = new BindingSource();
            
            _employeesBindingSource.DataSource = _dataSet;
            _employeesBindingSource.DataMember = "Employees";

            _reportsToBindingSource.DataSource = _employeesBindingSource;
            //_reportsToBindingSource.DataMember = "FK_Employees_Employees";
            
            EmployeesGrid.DataSource = _employeesBindingSource;
            ReportsToGrid.DataSource = _reportsToBindingSource;
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            _reportsToDataAdapter.Update(_dataSet, "Employees");
        }
    }
}