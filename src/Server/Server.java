package Server;

import Server.Controller.ControllerServer;

public class Server {
    public static void main(String[] args) {
        Thread controllerServerThread = new Thread(new ControllerServer("Server Controller Thread"));
        controllerServerThread.start();
    }
}
