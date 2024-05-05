package Client;

import Client.Controller.ControllerClient;
import Client.Controller.ControllerLoginClient;

public class Client {
    public static void main(String[] args) {

        ControllerLoginClient clc = new ControllerLoginClient("Login Controller");

        // Thread thread = new Thread(new ControllerClient("Controller Client and
        // Runnable"));
        // thread.start();
    }
}
