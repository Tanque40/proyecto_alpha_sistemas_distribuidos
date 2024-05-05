package Client.View;

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

public class ViewClient extends JFrame {
    static final int NumberMoles = 9;

    private JPanel jPanelViewClient;
    Font viewClientFont = new Font("Arial", 1, 14);
    Border viewClientBorder;
    GridBagConstraints constraints;
    protected JButton btMole[];
    protected JLabel lNotes;

    public ViewClient(String title) {
        super(title);

        jPanelViewClient = new JPanel();
        jPanelViewClient.setLayout(new GridBagLayout());
        viewClientBorder = BorderFactory.createEmptyBorder(10, 15, 10, 15);
        jPanelViewClient.setBorder(viewClientBorder);
        jPanelViewClient.setBackground(new Color(14, 140, 250));

        constraints = new GridBagConstraints();

        btMole = new JButton[NumberMoles];
        int cont = 1;
        for (int i = 0; i < Math.sqrt(NumberMoles); i++) {
            for (int j = 0; j < Math.sqrt(NumberMoles); j++) {
                btMole[cont - 1] = new JButton("Topo " + cont);
                btMole[cont - 1].setFont(viewClientFont);

                constraints.gridx = j;
                constraints.gridy = i;
                constraints.gridwidth = 1;
                constraints.gridheight = 1;
                constraints.weightx = 1.0;
                constraints.weighty = 1.0;
                constraints.anchor = GridBagConstraints.CENTER;
                constraints.fill = GridBagConstraints.NONE;

                jPanelViewClient.add(btMole[cont - 1], constraints);
                cont++;
            }
        }

        lNotes = new JLabel("Vista Cliente Iniciada");
        lNotes.setFont(viewClientFont);
        constraints.gridy = (int) Math.sqrt(NumberMoles) + 1;
        constraints.gridx = 0;
        jPanelViewClient.add(lNotes, constraints);

        this.add(jPanelViewClient);
        this.setBounds(400, 100, 400, 400);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }
}
