package iot.drone_carrier;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.function.Consumer;

import javax.swing.*;
import javax.swing.border.Border;

class LogView extends JPanel  {

    private final JTextArea log;

    /**
     * Optional listeners that receive the raw message string (without timestamp).
     * Useful to mirror the same events into other panels (e.g., HistoryView).
     */
    private final List<Consumer<String>> listeners = new ArrayList<>();

    public LogView(){
        setLayout(new BorderLayout());

        log = new JTextArea();
        log.setEditable(false);

        // stile
        log.setFont(new Font("Consolas", Font.PLAIN, 12));
        log.setBackground(Color.BLACK);
        log.setForeground(Color.GREEN);

        Border border = BorderFactory.createEmptyBorder(8, 8, 8, 8);
        log.setBorder(border);

        add(new JScrollPane(log), BorderLayout.CENTER);
    }

    public void addLogListener(Consumer<String> listener) {
        if (listener != null) {
            listeners.add(listener);
        }
    }

    public void log(String msg){
        SwingUtilities.invokeLater(() -> {
            String date = new Date().toString();
            log.append("[" + date + "] " + msg + "\n");
            //log.setCaretPosition(log.getDocument().getLength()); // autoscroll in fondo

            for (Consumer<String> l : listeners) {
                try {
                    l.accept(msg);
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });
    }
}
