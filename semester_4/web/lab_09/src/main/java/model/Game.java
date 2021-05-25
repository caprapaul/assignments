package model;

import lombok.Data;

import java.util.Arrays;

@Data
public class Game {
    private static Game instance;
    private Cell[] board;
    private User[] players;
    private int currentPlayerIndex;
    private User winner;

    public static Game getInstance()
    {
        if (instance == null) {
            instance = new Game();
        }

        return instance;
    }

    public User getCurrentPlayer() {
        return this.players[this.currentPlayerIndex];
    }

    public Game() {
        this.board = new Cell[3 * 3];

        Arrays.fill(this.board, Cell.Empty);

        this.players = new User[2];
        this.currentPlayerIndex = 0;
    }

    public boolean addPlayer(User player) {
        for (int i = 0; i < this.players.length; i++) {
            if (this.players[i] == null) {
                this.players[i] = player;
                return true;
            }
        }

        return false;
    }

    public String getBoardString() {
        String output = "[";

        for (int i = 0; i < this.board.length; i++) {
            output += this.board[i].getValue();

            if (i < this.board.length - 1) {
                output += ",";
            }

        }

        output += "]";

        return output;
    }
}
