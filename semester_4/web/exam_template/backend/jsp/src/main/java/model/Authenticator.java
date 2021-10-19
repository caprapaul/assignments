package model;

import java.sql.*;
import java.util.Optional;

public class Authenticator {
    private MySqlDatabase database;

    public Authenticator() {
        database = new MySqlDatabase();
    }

    public Optional<User> authenticate(String username, String password) {

        ResultSet rs;
        Optional<User> result = Optional.empty();

        try {
            PreparedStatement preparedStatement = database.getConnection().prepareStatement("select * from users2 where username=?");
            preparedStatement.setString(1, username);
            rs = preparedStatement.executeQuery();

            if (rs.next()) {
                User user = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
                result = Optional.of(user).filter(u -> u.getPassword().equals(password));
            }

            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;
    }
}