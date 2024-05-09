package Client.Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.MulticastSocket;
import java.net.SocketException;

import javax.swing.JButton;

import Client.View.ViewClient;
import Client.lib.TCPClient;
import lib.User;

public class ControllerClient extends ViewClient implements Runnable {
    private boolean initialazed = false;
    private User playerMe = null;

    public ControllerClient(String title, String userName) {
        super(title + " " + userName);
        this.lNotes.setText("Controller initialized");
        int cont = 1;
        for (JButton btMole : btMole) {
            btMole.addActionListener(new BtnMoleListener(this, btMole, cont));
            if (!initialazed)
                btMole.setText("Mole Down");
            cont++;
        }
        initialazed = true;
        int playerId;
        if (!readUser(userName)) {
            System.out.println("Checando ando");
            playerId = TCPClient.registerUser(userName);
            playerMe = new User(playerId, userName, 0);
        }
    }

    public boolean readUser(String userName) {
        playerMe = User.readUserFile(userName);
        return playerMe != null;
    }

    public class BtnMoleListener implements ActionListener {
        private int id;
        private boolean moleUp = false;
        private ControllerClient controller;
        private JButton thisButton;

        public BtnMoleListener(ControllerClient _cotroller, JButton _thisButton, int _id) {
            super();
            id = _id;
            controller = _cotroller;
            thisButton = _thisButton;
        }

        public void actionPerformed(ActionEvent actionEvent) {
            controller.lNotes.setText("Boton puchado " + id);
            if (moleUp) {
                thisButton.setText("Mole Up");
            } else {
                thisButton.setText("Mole Down");
            }
            moleUp = !moleUp;
        }

        public boolean isMoleUp() {
            return moleUp;
        }

        public void setMoleUp(boolean moleUp) {
            this.moleUp = moleUp;
        }
    }

    @Override
    public void run() {
        MulticastSocket socket = null;
        while (true) {
            try {
                socket = new MulticastSocket(49155);
                byte[] buffer = new byte[1000];
                DatagramPacket messageIn = new DatagramPacket(buffer, buffer.length);
                socket.receive(messageIn);
                String message = new String(messageIn.getData()).trim();
                int value = Integer.parseInt(message);
                this.btMole[value - 1].doClick();
                this.lNotes.setText("Text recibido" + message);
            } catch (SocketException e) {
                System.out.println("Socket: " + e.getMessage());
            } catch (IOException e) {
                System.out.println("IO: " + e.getMessage());
            } finally {
                if (socket != null)
                    socket.close();
            }
            System.out.println("hi client controller");
        }
    }
}
