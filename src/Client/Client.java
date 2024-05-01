package Client;

import Client.Controller.ControllerClient;

public class Client {
    public static void main(String[] args) {
        // ViewClient vc = new ViewClient("Vista Cliente");
        Thread thread = new Thread(new ControllerClient("Controller Client and Runnable"));
        thread.start();
    }
}
