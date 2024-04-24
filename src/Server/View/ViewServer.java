package Server.View;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.Border;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

public class ViewServer extends JFrame {

    static final int NumberMoles = 9;

    private JPanel jPanelViewServer;
    Font viewServerFont = new Font("Arial", 1, 14);
    Border viewServerBorder;
    GridBagConstraints constraints;
    protected JButton btMole[];
    protected JLabel lNotes;

    public ViewServer(String title) {
        super(title);

        jPanelViewServer = new JPanel();
        jPanelViewServer.setLayout(new GridBagLayout());
        viewServerBorder = BorderFactory.createEmptyBorder(10, 15, 10, 15);
        jPanelViewServer.setBorder(viewServerBorder);
        jPanelViewServer.setBackground(new Color(14, 140, 29));

        constraints = new GridBagConstraints();

        btMole = new JButton[NumberMoles];
        int cont = 1;
        for (int i = 0; i < Math.sqrt(NumberMoles); i++) {
            for (int j = 0; j < Math.sqrt(NumberMoles); j++) {
                btMole[cont - 1] = new JButton("Topo " + cont);
                btMole[cont - 1].setFont(viewServerFont);

                constraints.gridx = j;
                constraints.gridy = i;
                constraints.gridwidth = 1;
                constraints.gridheight = 1;
                constraints.weightx = 1.0;
                constraints.weighty = 1.0;
                constraints.anchor = GridBagConstraints.CENTER;
                constraints.fill = GridBagConstraints.NONE;

                jPanelViewServer.add(btMole[cont - 1], constraints);
                cont++;
            }
        }

        lNotes = new JLabel("Vista Iniciada");
        lNotes.setFont(viewServerFont);
        constraints.gridy = (int) Math.sqrt(NumberMoles) + 1;
        constraints.gridx = 0;
        jPanelViewServer.add(lNotes, constraints);

        this.add(jPanelViewServer);
        this.setBounds(400, 100, 400, 400);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }
}
