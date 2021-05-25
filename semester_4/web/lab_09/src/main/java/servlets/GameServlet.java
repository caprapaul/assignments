package servlets;

import model.Cell;
import model.Game;
import model.User;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/game")
public class GameServlet extends HttpServlet {
    @Override
    public void init() throws ServletException {
        super.init();
    }

    private Cell getUserType(User user) {
        for (int i = 0; i < Game.getInstance().getPlayers().length; i++) {
            User player = Game.getInstance().getPlayers()[i];

            if (player.getUsername().equals(user.getUsername())) {
                return Cell.valueOf(i);
            }
        }

        return Cell.Empty;
    }

    private boolean checkWinner() {
        Cell[] board = Game.getInstance().getBoard();
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum = 0;

            for (int j = 0; j < 3; j++) {
                int id = i + j * 3;

                sum += board[id].getValue();
            }

            if (sum == 3 || sum == 0) {
                Game.getInstance().setWinner(Game.getInstance().getCurrentPlayer());
                return true;
            }
        }

        for (int j = 0; j < 3; j++) {
            sum = 0;

            for (int i = 0; i < 3; i++) {
                int id = i + j * 3;

                sum += board[id].getValue();
            }

            if (sum == 3 || sum == 0) {
                Game.getInstance().setWinner(Game.getInstance().getCurrentPlayer());
                return true;
            }
        }

        return false;
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setAttribute("board", Game.getInstance().getBoardString());
        User winner = Game.getInstance().getWinner();
        request.setAttribute("winner", winner == null ? "null" : winner.getUsername());
        request.setAttribute("winner_type", Game.getInstance().getCurrentPlayerIndex());
        request.getRequestDispatcher("game.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        User user = (User) request.getSession().getAttribute("user");
        int cell = Integer.parseInt(request.getParameter("cell"));

        if (Game.getInstance().getWinner() != null) {
            return;
        }

        if (!user.getUsername().equals(Game.getInstance().getCurrentPlayer().getUsername())) {
            return;
        }

        if (Game.getInstance().getBoard()[cell] != Cell.Empty) {
            return;
        }

        Cell userType = this.getUserType(user);

        if (userType == Cell.Empty) {
            return;
        }

        Game.getInstance().getBoard()[cell] = userType;

        if (this.checkWinner()) {
            return;
        }

        int index = Game.getInstance().getCurrentPlayerIndex();
        index = (index + 1) % Game.getInstance().getPlayers().length;
        Game.getInstance().setCurrentPlayerIndex(index);
    }
}
