package Client.Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;

import javax.swing.JButton;

import Client.View.ViewClient;
import Client.lib.TCP_Client;

public class ControllerClient extends ViewClient implements Runnable {
    boolean initialazed = false;

    public ControllerClient(String title) {
        super("Controller Client");
        this.lNotes.setText("Controller initialized");
        int cont = 1;
        for (JButton btMole : btMole) {
            btMole.addActionListener(new BtnMoleListenner(this, btMole, cont));
            if (!initialazed)
                btMole.setText("Mole Down");
            cont++;
        }
        initialazed = true;
    }

    public class BtnMoleListenner implements ActionListener {
        private int id;
        private boolean moleUp = true;
        private ControllerClient controller;
        private JButton thisButton;

        public BtnMoleListenner(ControllerClient _cotroller, JButton _thisButton, int _id) {
            super();
            id = _id;
            controller = _cotroller;
            thisButton = _thisButton;
        }

        public void actionPerformed(ActionEvent actionEvent) {
            controller.lNotes.setText("Boton puchado " + id);
            TCP_Client tcpClient = new TCP_Client(id);
        }
    }

    @Override
    public void run() {
        MulticastSocket socket = null;
        while (true) {
            try {
                InetAddress group = InetAddress.getByName("228.5.6.7");
                socket = new MulticastSocket(49155);
                socket.joinGroup(group);
                byte[] buffer = new byte[1000];
                DatagramPacket messageIn = new DatagramPacket(buffer, buffer.length);
                socket.receive(messageIn);
                String message = new String(messageIn.getData()).trim();
                int value = new Integer(message);
                this.btMole[value - 1].setText("Mole Up");
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
