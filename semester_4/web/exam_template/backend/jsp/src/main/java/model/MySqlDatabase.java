package model;

import lombok.Data;

import java.sql.Connection;
import java.sql.DriverManager;

@Data
public class MySqlDatabase {
    private Connection connection;

    public MySqlDatabase() {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");

        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
