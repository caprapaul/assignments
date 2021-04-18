using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tommy;

namespace lab_02
{
    public partial class Form1 : Form
    {
        private SqlConnection _connection;
        private SqlDataAdapter _daParent;
        private SqlDataAdapter _daChild;
        private DataSet _dataSet;
        private BindingSource _bsParent;
        private BindingSource _bsChild;

        private TomlTable _config;
        private TomlNode _parent;
        private TomlNode _child;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            LoadConfig();
            int option = _config["option"].AsInteger;
            _parent = _config["tables"].AsArray[option]["parent"];
            _child = _config["tables"].AsArray[option]["child"];
            
            _connection =
                new SqlConnection(
                    @"Data Source = DESKTOP-CMIOIHP\SQLEXPRESS; Initial Catalog = MMORPG; Integrated Security = True");
            
            _dataSet = new DataSet();

            _daParent = new SqlDataAdapter(_parent["select"].AsString.Value, _connection);
            _daChild = new SqlDataAdapter(_child["select"].AsString.Value, _connection);
            new SqlCommandBuilder(_daChild);
            _bsParent = new BindingSource();
            _bsChild = new BindingSource();
            
            Fill();

            string relationName = $"FK_{_parent["name"].AsString.Value}{_child["name"].AsString.Value}";
            DataRelation dataRelation = new DataRelation(
                relationName,
                _dataSet.Tables[_parent["name"].AsString.Value].Columns[_parent["key"].AsString.Value],
                _dataSet.Tables[_child["name"].AsString.Value].Columns[_child["key"].AsString.Value]
            );
            _dataSet.Relations.Add(dataRelation);
            
            _bsParent.DataSource = _dataSet;
            _bsParent.DataMember = _parent["name"].AsString.Value;
            
            _bsChild.DataSource = _bsParent;
            _bsChild.DataMember = relationName;

            ParentGrid.DataSource = _bsParent;
            ChildGrid.DataSource = _bsChild;
            ParentLabel.Text = _parent["name"].AsString.Value;
            ChildLabel.Text = _child["name"].AsString.Value;
        }

        private void LoadConfig()
        {
            using(StreamReader reader = new StreamReader(File.OpenRead("config.toml")))
            {
                _config = TOML.Parse(reader);
            }
        }

        private void Fill()
        {
            _connection.Open();
            
            _daParent.Fill(_dataSet, _parent["name"].AsString.Value);
            _daChild.Fill(_dataSet, _child["name"].AsString.Value);
            
            _connection.Close();
        }

        private void Reload()
        {
            _dataSet.Clear();
            Fill();
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            _daChild.Update(_dataSet, _child["name"].AsString.Value);
        }

        private void RefreshButton_Click(object sender, EventArgs e)
        {
            Reload();
        }
    }
}