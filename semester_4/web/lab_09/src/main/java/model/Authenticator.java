package model;

import java.sql.*;

public class Authenticator {
    private PreparedStatement preparedStatement;
    private Connection con;

    public Authenticator() {
        connect();
    }

    public void connect() {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/tictactoe", "root", "");

        } catch(Exception e) {
            //System.out.println("Connection error:" + e.getMessage());
            e.printStackTrace();
        }
    }

    public boolean authenticate(String username, String password) {

        ResultSet rs;
        boolean result = false;
        System.out.println(username + " " + password);

        try {
            preparedStatement = con.prepareStatement("select * from users where username=?");
            preparedStatement.setString(1, username);
            rs = preparedStatement.executeQuery();

            if (rs.next() && rs.getString("password").equals(password)) {
                result = true;
            }

            rs.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return result;
    }
}