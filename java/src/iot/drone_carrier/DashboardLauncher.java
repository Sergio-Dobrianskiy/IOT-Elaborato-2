package iot.drone_carrier;

class DashboardLauncher {

    static DashboardView view = null;
    static LogView log = null;
    static HistoryView history = null;

    static MainWindow mainWindow = null;

    public static void main(String[] args) throws Exception {

        view = new DashboardView();
        log = new LogView();
        history = new HistoryView();

        // Mirror live log messages into the history panel
        log.addLogListener(history::log);

        mainWindow = new MainWindow(view, log, history);

        String portName = "COM5"; // TODO: put into config/constant
        DashboardController contr = new DashboardController(portName, view, log);
        view.registerController(contr);

        mainWindow.display();
    }
}