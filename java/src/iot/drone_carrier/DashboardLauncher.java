package iot.drone_carrier;

import javax.swing.SwingUtilities;

class DashboardLauncher   {

	static DashboardView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {	
		/*
		if (args.length != 1){
			System.err.println("Args: <serial port>");
			System.exit(1);
		}*/

		view = new DashboardView();
		log = new LogView();
		
		String portName = "COM5";
		DashboardController contr = new DashboardController(portName,view,log);
		view.registerController(contr);
		
		view.display();
		log.display();
	}
}