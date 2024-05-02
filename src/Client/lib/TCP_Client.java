package Client.lib;

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

public class TCP_Client {
    private Socket socketClient;
    private final String HOST = "localhost";
    private final int PORT = 49152;

    public TCP_Client(int valueToSend) {
        try {
            socketClient = new Socket(HOST, PORT);
            DataOutputStream out = new DataOutputStream(socketClient.getOutputStream());
            out.writeInt(valueToSend);
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
}
