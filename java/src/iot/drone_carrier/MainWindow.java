package iot.drone_carrier;

import javax.swing.*;

public class MainWindow extends JFrame {

    public MainWindow(DashboardView dashboardView, LogView logView, HistoryView historyView) {
        super("Drone Hangar - DRU");

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(1000, 600);

        JSplitPane split = new JSplitPane(
                JSplitPane.VERTICAL_SPLIT,
                dashboardView,
                logView
        );
        split.setResizeWeight(0.10);

        JTabbedPane tabs = new JTabbedPane();
        tabs.addTab("Dashboard", split);
        if (historyView != null) {
            tabs.addTab("History", historyView);
        }

        setContentPane(tabs);
        setLocationRelativeTo(null);
    }

    public void display() {
        SwingUtilities.invokeLater(() -> setVisible(true));
    }
}
