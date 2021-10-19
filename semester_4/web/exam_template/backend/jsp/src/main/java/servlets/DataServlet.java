package servlets;

import com.fasterxml.jackson.databind.ObjectMapper;
import model.MySqlDatabase;
import model.User;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

@WebServlet("/api/data")
public class DataServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {

        MySqlDatabase database = new MySqlDatabase();

        List<User> result = new ArrayList<>();

        try (PreparedStatement stmt = database.getConnection().prepareStatement("select * from users2");
             ResultSet rs = stmt.executeQuery()) {

            while (rs.next()) {
                result.add(
                        new User(rs.getInt("id"),
                                rs.getString("username"),
                                rs.getString("password"))
                );
            }
        }
        catch (SQLException exception) {
            exception.printStackTrace();
        }

        ObjectMapper mapper = new ObjectMapper();
        String json = mapper.writeValueAsString(result);

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write(json);
        response.getWriter().close();
    }
}
