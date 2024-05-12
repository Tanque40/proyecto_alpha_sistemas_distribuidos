package Server.Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

import javax.swing.JButton;

import Server.Utils.ConnectionManager;
import Server.View.ViewServer;
import Server.lib.GameManager;

public class ControllerServer extends ViewServer implements Runnable {
    private boolean initialazed = false;
    private final int TCP_SERVER_PORT = 49152;
    private GameManager gameManager;

    public ControllerServer(String title) {
        super(title);
        this.lNotes.setText("Controller Iniciado");
        int cont = 1;
        for (JButton btMole : btMole) {
            btMole.addActionListener(new BtnMoleListenner(this, btMole, cont));
            if (!initialazed)
                btMole.setText("Mole Down");
            cont++;
        }
        initialazed = true;
        gameManager = new GameManager();
    }

    public class BtnMoleListenner implements ActionListener {
        private int id;
        private boolean moleUp = true;
        private ControllerServer controller;
        private JButton thisButton;

        public BtnMoleListenner(ControllerServer _cotroller, JButton _thisButton, int _id) {
            super();
            id = _id;
            controller = _cotroller;
            thisButton = _thisButton;
        }

        public void actionPerformed(ActionEvent actionEvent) {
            MulticastSocket socket = null;
            try {
                InetAddress group = InetAddress.getByName("228.5.6.7"); // destination multicast group
                socket = new MulticastSocket(49155);
                socket.setTimeToLive(10);
                System.out.println("Messages' TTL (Time-To-Live): " + socket.getTimeToLive());
                String myMessage = "" + id;
                byte[] m = myMessage.getBytes();
                DatagramPacket messageOut = new DatagramPacket(m, m.length, group, 49155);
                socket.send(messageOut);
                System.out.println("Mensaje enviado: " + id);
            } catch (SocketException e) {
                System.out.println("Socket: " + e.getMessage());
            } catch (IOException e) {
                System.out.println("IO: " + e.getMessage());
            } finally {
                if (socket != null)
                    socket.close();
            }
            System.out.println("Boton puchado: " + id);

            controller.lNotes.setText("Boton puchado: " + id);

            if (moleUp) {
                thisButton.setText("Mole Up");
            } else {
                thisButton.setText("Mole Down");
            }
            moleUp = !moleUp;
        }
    }

    @Override
    public void run() {
        ServerSocket tcpServerSocket;
        try {
            tcpServerSocket = new ServerSocket(TCP_SERVER_PORT);
            while (true) {
                System.out.println("Waiting for messages...");
                Socket managerSocket = tcpServerSocket.accept();
                ConnectionManager connectionManager = new ConnectionManager(managerSocket, gameManager);
                connectionManager.start();
            }
        } catch (IOException e) {
            System.out.println("Listen :" + e.getMessage());
        }
    }
}
