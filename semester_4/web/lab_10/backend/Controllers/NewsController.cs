using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using MySql.Data.MySqlClient;

namespace api.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
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
        public IEnumerable<News> Read(string username, string password, DateTime start, DateTime end, string category)
        {
            Authenticator authenticator = new Authenticator(_database);

            if (!authenticator.Authenticate(username, password))
            {
                return null;
            }

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            if (category.ToUpper() == "ALL")
            {
                command.CommandText = @"SELECT id, text, title, producer, date, category FROM news WHERE (date BETWEEN @Start AND @End)";
            }
            else
            {
                command.CommandText = @"SELECT id, text, title, producer, date, category FROM news WHERE ((date BETWEEN @Start AND @End) AND category=@Category)";
                command.Parameters.AddWithValue("@Category", category);
            }

            command.Parameters.AddWithValue("@Start", start.ToString("yyyy-MM-dd"));
            command.Parameters.AddWithValue("@End", end.ToString("yyyy-MM-dd"));

            MySqlDataReader dataReader = command.ExecuteReader();

            List<News> result = new List<News>();
            while (dataReader.Read())
            {
                result.Add(new News
                {
                    Id = (int)dataReader.GetInt32("id"),
                    Text = dataReader.GetString("text"),
                    Title = dataReader.GetString("title"),
                    Producer = dataReader.GetString("producer"),
                    Date = dataReader.GetDateTime("date").ToString("yyyy-MM-dd"),
                    Category = dataReader.GetString("category")
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
