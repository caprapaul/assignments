package filters;

import com.fasterxml.jackson.databind.ObjectMapper;
import model.Authenticator;
import model.User;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.stream.Collectors;

@WebFilter("/api/data")
public class AuthFilter implements Filter {
    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;

        if (request.getMethod().equalsIgnoreCase("OPTIONS")) {
            chain.doFilter(request, response);
            return;
        }

        String data = request.getHeader("Authorization");

        if (data == null) {
            data = "";
        }

        String[] split = data.split(":");

        String username = "";
        String password = "";

        if (split.length == 2) {
            username = split[0];
            password = split[1];
        }


        Authenticator authenticator = new Authenticator();

        boolean loggedIn = authenticator.authenticate(username, password).isPresent();

        if (loggedIn) {
            chain.doFilter(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED);
        }
    }

    @Override
    public void destroy() {
        Filter.super.destroy();
    }
}
