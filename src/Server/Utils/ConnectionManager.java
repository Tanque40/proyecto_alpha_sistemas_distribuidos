package Server.Utils;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

import Server.lib.GameManager;
import lib.ConnectionObject;
import lib.ConnectionType;
import lib.User;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: ManageConnection recives each player point
 */

public class ConnectionManager extends Thread {
    private ObjectInputStream in;
    private ObjectOutputStream out;
    private Socket connectionSocket;
    private GameManager gameManager;
    ConnectionObject connectionObject;

    public ConnectionManager(Socket connectionSocket, GameManager gameManager) {
        try {
            this.connectionSocket = connectionSocket;
            this.gameManager = gameManager;
            in = new ObjectInputStream(this.connectionSocket.getInputStream());
            out = new ObjectOutputStream(this.connectionSocket.getOutputStream());
        } catch (IOException error) {
            System.out.println("Error on connection: " + error.getMessage());
        }
    }

    public User addUser(String userName) {
        int userId = gameManager.getCountPlayers() + 1;
        User player = new User(userId, userName, 0);
        gameManager.addPlayer(player);
        return player;
    }

    public void addPoint(int playerId) {
        gameManager.addPoint(playerId);

    }

    @Override
    public void run() {
        try {
            while (true) {
                connectionObject = (ConnectionObject) in.readObject();
                switch (connectionObject.connectionType) {
                    case REGISTER_USER:
                        User returnedPlayer = addUser(connectionObject.userName);
                        out.writeObject(new ConnectionObject(
                                ConnectionType.REGISTER_USER,
                                returnedPlayer,
                                -1,
                                "",
                                returnedPlayer.getId()));
                        break;
                    case SET_POINT:
                        addPoint(connectionObject.user.getId());
                        break;

                    default:
                        System.err.println("Connection Type not found");
                        break;
                }
            }
        } catch (EOFException e) {
            System.out.println("EOF:" + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO:" + e.getMessage());
        } catch (ClassNotFoundException e) {
            System.err.println("Error on use connection object classs");
        } finally {
            try {
                connectionSocket.close();
            } catch (IOException e) {
                System.out.println(e);
            }
        }
    }
}
