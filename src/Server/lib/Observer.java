package Server.lib;

import Server.Utils.ManageConnection;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: Observer manage the different events and send the following actions
 */

enum GameEventType {
    ADD_POINT,
    ADD_PLAYER,
}

// ? Descanso de un momento por estar en una llamada

public class Observer {

    private GameManager gameManager;
    private ManageConnection connectionManager;

    public Observer(GameManager gameManager, ManageConnection connectionManager) {
        this.gameManager = gameManager;
        this.connectionManager = connectionManager;
    }

    public void update() {

    }

    private void sendToGameManager(GameEventType eventType, int player) {
        if (GameEventType.ADD_PLAYER == eventType) {
            int playerNumber = gameManager.addPlayer();
            // TODO connection manager should return a number player to the player
        } else if (GameEventType.ADD_POINT == eventType) {
            gameManager.addPoint(player);
            if (gameManager.hasWinner()) {
                // TODO implements controller sends a winner notification
            }
        }
    }
}
