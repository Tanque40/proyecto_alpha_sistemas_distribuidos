package Client.View;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.border.Border;

public class ViewLogInClient extends JFrame {
    private JPanel jPanelViewLogInClient;
    private Font viewClientFont = new Font("Arial", 1, 14);
    private Border viewClientBorder;
    private GridBagConstraints constraints;

    protected JButton btnContinue;
    protected JLabel lUserNameMessage;
    protected JTextField tfUserName;

    public ViewLogInClient(String title) {
        super(title);
        jPanelViewLogInClient = new JPanel();
        jPanelViewLogInClient.setLayout(new GridBagLayout());
        viewClientBorder = BorderFactory.createEmptyBorder(10, 15, 10, 15);
        jPanelViewLogInClient.setBorder(viewClientBorder);
        jPanelViewLogInClient.setBackground(new Color(14, 140, 250));

        constraints = new GridBagConstraints();

        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.weightx = 0.1;
        constraints.weighty = 1.0;
        constraints.anchor = GridBagConstraints.LINE_END;
        constraints.fill = GridBagConstraints.NONE;
        lUserNameMessage = new JLabel("Username:");
        lUserNameMessage.setFont(viewClientFont);
        jPanelViewLogInClient.add(lUserNameMessage, constraints);

        constraints.gridx = 1;
        constraints.gridy = 0;
        constraints.gridheight = 1;
        constraints.gridwidth = 1;
        constraints.weightx = 1.0;
        constraints.weighty = 1.0;
        constraints.anchor = GridBagConstraints.LINE_START;
        constraints.fill = GridBagConstraints.HORIZONTAL;
        tfUserName = new JTextField(255);
        tfUserName.setFont(viewClientFont);
        jPanelViewLogInClient.add(tfUserName, constraints);

        constraints.gridx = 0;
        constraints.gridy = 1;
        constraints.gridheight = 1;
        constraints.gridwidth = 2;
        constraints.weightx = 1.0;
        constraints.weighty = 1.0;
        constraints.anchor = GridBagConstraints.CENTER;
        constraints.fill = GridBagConstraints.NONE;
        btnContinue = new JButton("To the game");
        btnContinue.setFont(viewClientFont);
        jPanelViewLogInClient.add(btnContinue, constraints);

        this.add(jPanelViewLogInClient);
        this.setBounds(400, 100, 400, 200);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }
}
