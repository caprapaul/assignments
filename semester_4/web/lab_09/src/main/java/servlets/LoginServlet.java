package servlets;

import model.Authenticator;
import model.Game;
import model.User;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    public LoginServlet() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getRequestDispatcher("login.jsp").forward(request, response);
    }

    protected void doPost(HttpServletRequest request,
                          HttpServletResponse response) throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        Authenticator authenticator = new Authenticator();
        boolean result = authenticator.authenticate(username, password);

        if (result) {
            User user = new User(username, password);

            if (!Game.getInstance().addPlayer(user)) {
                request.getRequestDispatcher("error.jsp").forward(request, response);
                return;
            }

            request.getSession().setAttribute("user", user);
            response.sendRedirect(request.getContextPath() + "/game");
            return;
        }

        request.getRequestDispatcher("error.jsp").forward(request, response);
    }

}