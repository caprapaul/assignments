using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using MySql.Data.MySqlClient;

namespace api.Controllers
{
    [ApiController]
    [Route("api/users")]
    public class NewsController : ControllerBase
    {
        private readonly ILogger<NewsController> _logger;
        private MySqlDatabase _database;

        public NewsController(ILogger<NewsController> logger, MySqlDatabase database)
        {
            _logger = logger;
            _database = database;
        }

        [HttpPost]
        public void Create([FromForm] string username, [FromForm] string password, [FromForm] News news)
        {
            Authenticator authenticator = new Authenticator(_database);

            if (!authenticator.Authenticate(username, password))
            {
                return;
            }

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"SELECT MAX(id)+1 id FROM news";
            int id = Convert.ToInt32(command.ExecuteScalar());

            command.CommandText = @"INSERT INTO news (id, text, title, producer, date, category) VALUES(@Id, @Text, @Title, @Producer, @Date, @Category)";
            command.Parameters.AddWithValue("@Id", id);
            command.Parameters.AddWithValue("@Text", news.Text);
            command.Parameters.AddWithValue("@Title", news.Title);
            command.Parameters.AddWithValue("@Producer", news.Producer);
            command.Parameters.AddWithValue("@Date", news.Date);
            command.Parameters.AddWithValue("@Category", news.Category);
            command.ExecuteNonQuery();
        }

        [HttpGet]
        public IEnumerable<User> Read()
        {

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"SELECT * FROM users2";

            MySqlDataReader dataReader = command.ExecuteReader();

            List<User> result = new List<User>();
            while (dataReader.Read())
            {
                result.Add(new User
                {
                    Id = (int)dataReader.GetInt32("id"),
                    Username = dataReader.GetString("username"),
                    Password = dataReader.GetString("password"),
                });
            }

            dataReader.Close();

            return result;
        }

        [HttpPost("{id}")]
        public void Update([FromForm] string username, [FromForm] string password, int id, [FromForm] News news)
        {
            Authenticator authenticator = new Authenticator(_database);

            if (!authenticator.Authenticate(username, password))
            {
                return;
            }

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"UPDATE news SET text=@Text, title=@Title, producer=@Producer, date=@Date, category=@Category WHERE id=@Id";
            command.Parameters.AddWithValue("@Id", id);
            command.Parameters.AddWithValue("@Text", news.Text);
            command.Parameters.AddWithValue("@Title", news.Title);
            command.Parameters.AddWithValue("@Producer", news.Producer);
            command.Parameters.AddWithValue("@Date", news.Date);
            command.Parameters.AddWithValue("@Category", news.Category);
            command.ExecuteNonQuery();
        }

        [HttpGet("{id}")]
        public void Delete(string username, string password, int id, [FromForm] News news)
        {
            Authenticator authenticator = new Authenticator(_database);

            if (!authenticator.Authenticate(username, password))
            {
                return;
            }

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"DELETE FROM news WHERE id=@Id";
            command.Parameters.AddWithValue("@Id", id);
            command.ExecuteNonQuery();
        }
    }
}
