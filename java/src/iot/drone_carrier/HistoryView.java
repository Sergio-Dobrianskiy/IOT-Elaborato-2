package iot.drone_carrier;

import java.awt.BorderLayout;
import java.util.Date;

import javax.swing.*;

/**
 * History panel that shows an append-only log with timestamps.
 * (Converted from JFrame to JPanel so it can be hosted inside the main window.)
 */
class HistoryView extends JPanel {

    private final JTextArea log;

    public HistoryView() {
        super(new BorderLayout());

        log = new JTextArea(30, 40);
        log.setEditable(false);

        add(new JScrollPane(log), BorderLayout.CENTER);
    }

    public void log(String msg) {
        SwingUtilities.invokeLater(() -> {
            String date = new Date().toString();
            log.append("[" + date + "] " + msg + "\n");
        });
    }
}
