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

namespace lab_01
{
    public partial class Form1 : Form
    {
        private SqlConnection _connection;
        private SqlDataAdapter _daPlayers;
        private SqlDataAdapter _daCharacters;
        private DataSet _dataSet;
        private BindingSource _bsPlayers;
        private BindingSource _bsCharacters;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            _connection =
                new SqlConnection(
                    @"Data Source = DESKTOP-CMIOIHP\SQLEXPRESS; Initial Catalog = MMORPG; Integrated Security = True");
            
            // contains data tables that store a local copy of the data
            _dataSet = new DataSet();

            // data adapters are the link between data sets and the database to get the data and change it
            _daPlayers = new SqlDataAdapter("SELECT * FROM Players", _connection);
            _daCharacters = new SqlDataAdapter("SELECT * FROM Characters", _connection);
            new SqlCommandBuilder(_daCharacters);
            _bsPlayers = new BindingSource();
            _bsCharacters = new BindingSource();
            
            Fill();

            DataRelation dataRelation = new DataRelation(
                "FK_PlayersCharacters",
                _dataSet.Tables["Players"].Columns["Id"],
                _dataSet.Tables["Characters"].Columns["PlayerId"]
            );
            _dataSet.Relations.Add(dataRelation);
            
            _bsPlayers.DataSource = _dataSet;
            _bsPlayers.DataMember = "Players";
            
            _bsCharacters.DataSource = _bsPlayers;
            _bsCharacters.DataMember = "FK_PlayersCharacters";

            PlayersGrid.DataSource = _bsPlayers;
            CharactersGrid.DataSource = _bsCharacters;
            
            CharactersGrid.Columns["PlayerId"].Visible = false;
            CharactersGrid.Columns["AttributesId"].Visible = false;
            CharactersGrid.Columns["Id"].ReadOnly = true;
        }

        private void Fill()
        {
            _connection.Open();
            
            // fill thee dataset with the data from the database
            _daPlayers.Fill(_dataSet, "Players");
            _daCharacters.Fill(_dataSet, "Characters");
            
            _connection.Close();
        }

        private void Reload()
        {
            _dataSet.Clear();
            Fill();
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            // update the database by executing an INSERT/UPDATE/DELETE on each row based on its state
            _daCharacters.Update(_dataSet, "Characters");
        }

        private void RefreshButton_Click(object sender, EventArgs e)
        {
            Reload();
        }
    }
}