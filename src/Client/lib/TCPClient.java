package Client.lib;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

/*
 * @author: Bruno Vitte @Tanque40
 * @version: 1.0
 * @brief: Create a TCP Client to sent wich button was pressed
 */

public class TCPClient {
    private Socket socketClient;
    private final String HOST = "localhost";
    private final int PORT = 49152;

    public TCPClient(int valueToSend) {
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
            DataOutputStream out = new DataOutputStream(socketClient.getOutputStream());
            out.writeInt(valueToSend);
        } catch (IOException exception) {
            System.err.println("At SendPoint [IO]: " + exception.getMessage());
        }
    }

    public int registerUser(String userName) {
        DataOutputStream out;
        DataInputStream in;

        int returnedId = -1;

        try {
            out = new DataOutputStream(socketClient.getOutputStream());
            in = new DataInputStream(socketClient.getInputStream());
            out.writeUTF(userName);
            returnedId = in.readInt();
        } catch (IOException exception) {
            System.err.println("At registerUser [IO]: " + exception.getMessage());
        }

        return returnedId;
    }
}
