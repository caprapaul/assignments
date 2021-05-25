package servlets;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class HelloWorldController extends HttpServlet {

    protected void doGet(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {

        String username = request.getParameter("user");

        RequestDispatcher rd;

        String helloWorld = "Welcome to servlet and jsp, " + username + "!";
        rd = request.getRequestDispatcher("/helloWorld.jsp");
        request.setAttribute("helloMessage", helloWorld);
        rd.forward(request, response);

    }
}
