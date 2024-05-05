package Server.Utils;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;

import Server.lib.GameManager;

/*
 * @author: Bruno Vitte @Tanque40 in github
 * @version: 1.0
 * @brief: ManageConnection recives each player point
 */

public class ConnectionManager extends Thread {
    private DataInputStream in;
    private DataOutputStream out;
    private Socket connectionSocket;
    private GameManager gameManager;

    public ConnectionManager(Socket connectionSocket, GameManager gameManager) {
        try {
            this.connectionSocket = connectionSocket;
            this.gameManager = gameManager;
            in = new DataInputStream(connectionSocket.getInputStream());
            out = new DataOutputStream(connectionSocket.getOutputStream());
        } catch (IOException error) {
            System.out.println("Error on connection: " + error.getMessage());
        }
    }

    @Override
    public void run() {
        try {
            while (true) {
                int moleWhacked = in.readInt();
                System.out.println("Topo golpeado: " + moleWhacked);
            }
        } catch (EOFException e) {
            System.out.println("EOF:" + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO:" + e.getMessage());
        } finally {
            try {
                connectionSocket.close();
            } catch (IOException e) {
                System.out.println(e);
            }
        }
    }
}
