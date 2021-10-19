using System;
using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using MySql.Data.MySqlClient;

namespace api.Controllers
{
    [ApiController]
    [Route("api/auctions")]
    public class AuctionController : ControllerBase
    {
        private readonly ILogger<AuctionController> _logger;
        private MySqlDatabase _database;

        public AuctionController(ILogger<AuctionController> logger, MySqlDatabase database)
        {
            _logger = logger;
            _database = database;
        }


        [NonAction]
        public Category CheckCategory(int id)
        {

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"SELECT * FROM categories WHERE id=@Id";
            command.Parameters.AddWithValue("@Id", id);

            MySqlDataReader dataReader = command.ExecuteReader();

            Category result = null;

            if (dataReader.Read())
            {
                result = new Category
                {
                    Id = dataReader.GetInt32("id"),
                    Name = dataReader.GetString("name"),
                };
            }

            dataReader.Close();

            return result;
        }

        [NonAction]
        public Category CheckCategory(string name)
        {

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"SELECT * FROM categories WHERE name=@Name";
            command.Parameters.AddWithValue("@Name", name);

            MySqlDataReader dataReader = command.ExecuteReader();

            Category result = null;

            if (dataReader.Read())
            {
                result = new Category
                {
                    Id = dataReader.GetInt32("id"),
                    Name = dataReader.GetString("name"),
                };
            }

            dataReader.Close();

            return result;
        }

        [HttpGet]
        public IEnumerable<Auction> Read(string username)
        {

            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"SELECT * FROM auction WHERE user=@Username";
            command.Parameters.AddWithValue("@Username", username);

            MySqlDataReader dataReader = command.ExecuteReader();

            List<Auction> result = new List<Auction>();
            while (dataReader.Read())
            {
                result.Add(new Auction
                {
                    Id = dataReader.GetInt32("id"),
                    User = dataReader.GetString("user"),
                    CategoryId = dataReader.GetInt32("categoryId"),
                    Description = dataReader.GetString("description"),
                    Date = dataReader.GetString("date")
                });
            }

            dataReader.Close();

            return result;
        }

        [HttpPost]
        public void Add(string username, [FromForm] Auction auction, [FromForm] string category)
        {
            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            int categoryId = -1;
            Category category1 = CheckCategory(category);


            if (category1 == null)
            {
                command.CommandText = @"INSERT INTO cateogry (name) VALUES(@Name)";

                command.Parameters.AddWithValue("@Name", category);
                MySqlDataReader mySqlDataReader = command.ExecuteReader();
                mySqlDataReader.Read();
                categoryId = mySqlDataReader.GetInt32("id");
            }
            else
            {
                categoryId = category1.Id;
            }

            command.CommandText = @"INSERT INTO auction (user, categoryId, description, date) VALUES(@User, @CategoryId, @Description, @Date)";

            command.Parameters.AddWithValue("@User", username);
            command.Parameters.AddWithValue("@CategoryId", categoryId);
            command.Parameters.AddWithValue("@Description", auction.Description);
            command.Parameters.AddWithValue("@Date", auction.Date);
            command.ExecuteNonQuery();
        }

        [HttpPost("{id}")]
        public void Update(string username, int id, [FromForm] Auction auction)
        {
            MySqlCommand command = _database.Connection.CreateCommand() as MySqlCommand;

            command.CommandText = @"SELECT * FROM auction WHERE id=@Id";
            command.Parameters.AddWithValue("@Id", id);

            MySqlDataReader dataReader = command.ExecuteReader();

            List<Auction> result = new List<Auction>();

            if (!dataReader.Read() || dataReader.GetString("user") != username)
            {
                return;
            }

            command.CommandText = @"UPDATE auction SET user=@User, CategoryId=@CategoryId, description=@Description, date=@Date WHERE id=@Id";

            command.Parameters.AddWithValue("@Id", id);
            command.Parameters.AddWithValue("@User", username);
            command.Parameters.AddWithValue("@CategoryId", auction.CategoryId);
            command.Parameters.AddWithValue("@Description", auction.Description);
            command.Parameters.AddWithValue("@Date", auction.Date);
            command.ExecuteNonQuery();
        }
    }
}
