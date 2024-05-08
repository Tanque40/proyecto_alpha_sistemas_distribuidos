package Client.lib;

import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import lib.ConnectionObject;
import lib.ConnectionType;

/*
 * @author: Bruno Vitte @Tanque40
 * @version: 1.0
 * @brief: Create a TCP Client to sent wich button was pressed
 */

public class TCPClient {
    private Socket socketClient;
    ObjectOutputStream out;
    ObjectInputStream in;
    private final String HOST = "localhost";
    private final int PORT = 49152;

    public TCPClient() {
        try {
            socketClient = new Socket(HOST, PORT);

        } catch (UnknownHostException exception) {
            System.err.println("Socket: " + exception.getMessage());
        } catch (EOFException exception) {
            System.err.println("EOF: " + exception.getMessage());
        } catch (IOException exception) {
            System.err.println("IO: " + exception.getMessage());
        } finally {
            try {
                socketClient.close();
            } catch (IOException exception) {
                System.err.println("[On Close Socket] IO: " + exception.getMessage());
            }
        }
    }

    public void sendPoint(int valueToSend) {
        try {
            out = new ObjectOutputStream(socketClient.getOutputStream());
            ConnectionObject connectionObject = new ConnectionObject(
                    ConnectionType.SET_POINT,
                    null,
                    valueToSend,
                    "",
                    0);
            out.writeObject(connectionObject);
        } catch (IOException exception) {
            System.err.println("At SendPoint [IO]: " + exception.getMessage());
        }
    }

    public int registerUser(String userName) {
        int returnedId = -1;

        try {
            out = new ObjectOutputStream(socketClient.getOutputStream());
            in = new ObjectInputStream(socketClient.getInputStream());
            ConnectionObject connectionObject = new ConnectionObject(
                    ConnectionType.SET_POINT,
                    null,
                    0,
                    userName,
                    0);
            out.writeObject(connectionObject);
            returnedId = ((ConnectionObject) in.readObject()).returnedId;
        } catch (IOException exception) {
            System.err.println("At registerUser [IO]: " + exception.getMessage());
        } catch (ClassNotFoundException classNotFoundException) {
            System.err.println("Error on recive class [Register User]: " + classNotFoundException.getMessage());
        }

        return returnedId;
    }
}
