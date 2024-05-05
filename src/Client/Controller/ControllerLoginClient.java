package Client.Controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import Client.View.ViewLogInClient;

public class ControllerLoginClient extends ViewLogInClient {
    public ControllerLoginClient(String title) {
        super(title);

        btnContinue.addActionListener(new BtnContinueListener(this));
    }

    public class BtnContinueListener implements ActionListener {
        private ControllerLoginClient controller;

        public BtnContinueListener(ControllerLoginClient controller) {
            this.controller = controller;
        }

        public void actionPerformed(ActionEvent actionEvent) {
            String userName = controller.tfUserName.getText();
            controller.setVisible(false);
            ControllerClient cc = new ControllerClient("Hora de Jugar:", userName);
        }
    }
}
