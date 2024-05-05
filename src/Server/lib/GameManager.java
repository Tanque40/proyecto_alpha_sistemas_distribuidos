package Server.lib;

import java.util.ArrayList;

import lib.User;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: Manager stores different users and their points, if someone haves
 * 5 point is the winner
 */

public class GameManager {
    private ArrayList<User> players;
    private int winnerPlayer;

    public GameManager() {
        players = new ArrayList<User>();
        winnerPlayer = 0;
    }

    public void addPoint(int playerId) {
        for (User player : players) {
            if (player.getId() == playerId)
                player.setPoints(player.getPoints() + 1);
        }
    }

    public void addPlayer(User player) {
        players.add(player);
    }

    public boolean hasWinner() {
        boolean response = false;

        for (User player : players) {
            if (player.getPoints() == 5) {
                winnerPlayer = player.getId();
                response = true;
            }
        }

        return response;
    }
}
