package servlets;

import com.fasterxml.jackson.databind.ObjectMapper;
import model.Authenticator;
import model.User;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Optional;

@WebServlet("/api/login")
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Authenticator authenticator = new Authenticator();
        Optional<User> result = authenticator.authenticate(username, password);


        if (result.isEmpty()) {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED);
            return;
        }

        User user = new User(username, password);
        ObjectMapper mapper = new ObjectMapper();
        String json = mapper.writeValueAsString(user);

        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().write(json);
        response.getWriter().close();
    }

}