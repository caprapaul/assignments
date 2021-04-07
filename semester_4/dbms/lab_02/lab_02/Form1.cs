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
        private SqlDataAdapter _daPlayers;
        private SqlDataAdapter _daCharacters;
        private DataSet _dataSet;
        private SqlCommandBuilder _commandBuilder;
        private BindingSource _bsPlayers;
        private BindingSource _bsCharacters;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Refresh();
        }

        private void Refresh()
        {
            _connection =
                new SqlConnection(
                    @"Data Source = DESKTOP-CMIOIHP\SQLEXPRESS; Initial Catalog = MMORPG; Integrated Security = True");
            
            _connection.Open();
            _dataSet = new DataSet();

            _daPlayers = new SqlDataAdapter("SELECT * FROM Players", _connection);
            _daCharacters = new SqlDataAdapter("SELECT * FROM Characters", _connection);
            _commandBuilder = new SqlCommandBuilder(_daCharacters);

            _daPlayers.Fill(_dataSet, "Players");
            _daCharacters.Fill(_dataSet, "Characters");

            DataRelation dataRelation = new DataRelation(
                "FK__Character__Playe__30F848ED",
                _dataSet.Tables["Players"].Columns["Id"],
                _dataSet.Tables["Characters"].Columns["PlayerId"]
            );
            _dataSet.Relations.Add(dataRelation);

            _bsPlayers = new BindingSource();
            
            _bsPlayers.DataSource = _dataSet;
            _bsPlayers.DataMember = "Players";
            
            _bsCharacters = new BindingSource();

            _bsCharacters.DataSource = _bsPlayers;
            _bsCharacters.DataMember = "FK__Character__Playe__30F848ED";

            PlayersGrid.DataSource = _bsPlayers;
            CharactersGrid.DataSource = _bsCharacters;
            CharactersGrid.Columns["PlayerId"].Visible = false;
            CharactersGrid.Columns["AttributesId"].Visible = false;
            CharactersGrid.Columns["Id"].ReadOnly = true;
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            _daCharacters.Update(_dataSet, "Characters");
        }

        private void RefreshButton_Click(object sender, EventArgs e)
        {
            Refresh();
        }
    }
}