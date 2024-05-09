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
    private static Socket socketClient;
    static ObjectOutputStream out;
    static ObjectInputStream in;
    static private final String HOST = "localhost";
    static private final int PORT = 49152;

    public static void sendPoint(int valueToSend) {
        try {
            socketClient = new Socket(HOST, PORT);
            out = new ObjectOutputStream(socketClient.getOutputStream());
            ConnectionObject connectionObject = new ConnectionObject(
                    ConnectionType.SET_POINT,
                    null,
                    valueToSend,
                    "",
                    0);
            out.writeObject(connectionObject);
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

    public static int registerUser(String userName) {
        int returnedId = -1;
        try {
            socketClient = new Socket(HOST, PORT);
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
        } catch (UnknownHostException exception) {
            System.err.println("Socket: " + exception.getMessage());
        } catch (EOFException exception) {
            System.err.println("EOF: " + exception.getMessage());
        } catch (IOException exception) {
            System.err.println("IO: " + exception.getMessage());
        } catch (ClassNotFoundException classNotFoundException) {
            System.err.println("Error on recive class [Register User]: " + classNotFoundException.getMessage());
        } finally {
            try {
                socketClient.close();
            } catch (IOException exception) {
                System.err.println("[On Close Socket] IO: " + exception.getMessage());
            }
        }
        return returnedId;
    }
}
