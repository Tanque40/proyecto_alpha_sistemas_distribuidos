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
    private int countPlayers = 0;

    public int getCountPlayers() {
        return countPlayers;
    }

    public ArrayList<User> getPlayers() {
        return players;
    }

    public int getWinnerPlayer() {
        return winnerPlayer;
    }

    public void setWinnerPlayer(int winnerPlayer) {
        this.winnerPlayer = winnerPlayer;
    }

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

    public int addPlayer(User player) {
        players.add(player);
        countPlayers++;
        return countPlayers;
    }

    public boolean hasWinner() {
        boolean response = false;

        for (User player : players) {
            if (player.getPoints() == 5) {
                this.setWinnerPlayer(player.getId());
                response = true;
            }
        }

        return response;
    }
}
