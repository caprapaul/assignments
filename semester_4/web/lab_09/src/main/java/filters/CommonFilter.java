package filters;

import javax.servlet.*;
import javax.servlet.annotation.WebFilter;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;

//@WebFilter({"/app/*", "/login"})
public class CommonFilter implements Filter {
    @Override
    public void init(FilterConfig config) {
    }

    @Override
    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain) throws ServletException, IOException {
        HttpServletRequest request = (HttpServletRequest) req;
        String path;

        if (request.getRequestURI().length() > request.getContextPath().length()) {
            path = request.getRequestURI().substring(request.getContextPath().length() + 1);
            req.getRequestDispatcher(path + ".jsp").forward(req, res);
        }
    }

    @Override
    public void destroy() {
        Filter.super.destroy();
    }
}
