package Client.Controller;

import Client.View.ViewClient;

public class ControllerClient extends ViewClient implements Runnable {
    boolean initialazed = false;

    public ControllerClient(String title) {
        super("Controller Client");
        this.lNotes.setText("Controller initialized");
    }

    @Override
    public void run() {
        while (true) {
            System.out.println("hi client controller");
        }
    }
}
