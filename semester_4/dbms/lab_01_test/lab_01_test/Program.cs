using System;
using System.Data;
using System.Data.SqlClient;

namespace lab_01_test
{
    // SqlCommand - ExecuteScalar, ExecuteReader, ExecuteNonQuery
    // SqlDataAdapter - update row AND eliminate row
    internal class Program
    {
        public static void Main(string[] args)
        {
            SqlConnection connection = new SqlConnection();
            connection.ConnectionString = @"Data Source = DESKTOP-CMIOIHP\SQLEXPRESS; Initial Catalog = Northwind; Integrated Security = True";
            connection.Open();
            DataSet dataSet = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter("SELECT * FROM Employees", connection);
            dataAdapter.Fill(dataSet, "Employees");

            foreach (DataRow row in dataSet.Tables["Employees"].Rows)
            {
                Console.WriteLine($"{row["EmployeeID"]} {row["LastName"]}");
            }
            
            Console.WriteLine("\n");

            string query = "SELECT * FROM Employees WHERE Country=@country";
            SqlCommand command = new SqlCommand(query, connection);
            command.Parameters.Add("@country", SqlDbType.NVarChar);
            command.Parameters["@country"].Value = "USA";
            
            // Reader
            using(SqlDataReader reader = command.ExecuteReader())
            {
                while (reader.Read())
                {
                    Console.WriteLine($"{reader[0]} {reader[1]}");
                }
            }
            
            Console.WriteLine("\n");
            
            // Scalar
            Int32 first = (Int32) command.ExecuteScalar();
            Console.WriteLine($"First: {first}");
            
            connection.Close();
        }
    }
}