using System.Net;
using System.Net.Http;
using System.Web.Http;
using MySql.Data.MySqlClient;

namespace api
{
    public class Authenticator
    {
        private MySqlDatabase _database;

        public Authenticator(MySqlDatabase database)
        {
            _database = database;
        }

        public bool Authenticate(string username, string password)
        {
            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;
            command.CommandText = @"SELECT * FROM users WHERE username=@Username";
            command.Parameters.AddWithValue("@Username", username);
            MySqlDataReader reader = command.ExecuteReader();

            bool result = false;

            if (reader.Read())
            {
                if (password == reader.GetString("password"))
                {
                    result = true;
                }
            }

            reader.Close();

            return result;
        }
    }
}