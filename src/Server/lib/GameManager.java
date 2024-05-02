package Server.lib;

import java.util.ArrayList;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: Manager stores different users and their points, if someone haves
 * 5 point is the winner
 */

public class GameManager {
    private ArrayList<Integer> points;
    private int players;
    private int winnerPlayer;

    public GameManager() {
        points = new ArrayList<Integer>();
        players = 0;
        winnerPlayer = 0;
    }

    public void addPoint(int player) {
        points.set(player - 1, points.get(player - 1) + 1);
    }

    public int addPlayer() {
        points.add(0);
        players++;
        return players;
    }

    public boolean hasWinner() {
        boolean response = false;

        for (int i = 0; i < points.size(); i++) {
            if (points.get(i) == 5) {
                winnerPlayer = i + 1;
                response = true;
            }
        }

        return response;
    }
}
