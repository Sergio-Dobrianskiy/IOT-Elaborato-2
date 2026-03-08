package iot.drone_carrier;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
// import java.awt.BorderLayout;
// import java.awt.Graphics;
// import java.awt.Graphics2D;
// import java.awt.LayoutManager;
// import java.awt.RenderingHints;
// import java.util.LinkedList;

import javax.swing.*;


class DashboardView extends JPanel implements ActionListener  {



	// Send commands from GUI to Hangar simulating:
	private JButton landButton;      // - Landing
	private JButton takeOffButton;   // - Taking off
	private JButton alarmButton;     // Alarm simulation
	private boolean alarmActive = false;


	// Shows state of the drone (rest, taking off, operating, landing)
    private JTextField droneState;
	// Shows state of the hangar (normal, alarm, prealarm)
	private JTextField hangarState;      

	// Drone distance from the ground
	private JTextField groundDistance;
	
	//private JTextField hangarTemperature;
	private JTextField currentTemperature;
	
	private JTextField droneAbove;

	//private int WINDOW_WIDTH;
	//private int WINDOW_HEIGHT; 
	private int FIELD_WIDTH;
	private int FIELD_HEIGHT;

	
	
	private DashboardController controller;	
	
	public DashboardView(){
		//super(".:: Drone Carrier ::.");
		//WINDOW_WIDTH = 600;
		//WINDOW_HEIGHT = 150;
		FIELD_WIDTH = 200;
		FIELD_HEIGHT = 15;



		setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
		add(Box.createRigidArea(new Dimension(0, 10)));

		// Riga info
		JPanel infoLine = new JPanel();
        infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.X_AXIS));



		// Hangar State
		hangarState = new JTextField("--");
		hangarState.setEditable(false);
		//hangarState.setPreferredSize(new Dimension(FIELD_WIDTH,FIELD_HEIGHT));
		hangarState.setMaximumSize(new Dimension(FIELD_WIDTH, FIELD_HEIGHT));
        infoLine.add(new JLabel("Hangar State: "));
        infoLine.add(hangarState);
        infoLine.add(Box.createRigidArea(new Dimension(10, 0)));

		// Drone State
		droneState = new JTextField("--");
		droneState.setEditable(false);

		droneState.setMaximumSize(new Dimension(FIELD_WIDTH, FIELD_HEIGHT));
		infoLine.add(new JLabel("Drone State:")); 
		infoLine.add(droneState);
		infoLine.add(Box.createRigidArea(new Dimension(10, 0)));


		// Ground Distance
        groundDistance = new JTextField("--");
        groundDistance.setEditable(false);
        groundDistance.setMaximumSize(new Dimension(FIELD_WIDTH, FIELD_HEIGHT));
        infoLine.add(new JLabel("Ground Distance: "));
        infoLine.add(groundDistance);
        infoLine.add(Box.createRigidArea(new Dimension(10, 0)));

		// Temperature of hangar

        currentTemperature = new JTextField("--");
        currentTemperature.setEditable(false);
        currentTemperature.setMaximumSize(new Dimension(FIELD_WIDTH, FIELD_HEIGHT));
        infoLine.add(new JLabel("Temperature: "));
        infoLine.add(currentTemperature);

		// Is the drone above
		droneAbove = new JTextField("--");
        droneAbove.setEditable(false);
        droneAbove.setMaximumSize(new Dimension(FIELD_WIDTH, FIELD_HEIGHT));
        infoLine.add(new JLabel("Drone Above: "));
        infoLine.add(droneAbove);

        add(infoLine);
        add(Box.createRigidArea(new Dimension(0, 12)));
		

		// Button to simulate landing
        // ---- Bottoni ----
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.X_AXIS));

        landButton = new JButton("Land");
        landButton.setEnabled(false);
        landButton.addActionListener(this);

        takeOffButton = new JButton("Take Off");
        takeOffButton.setEnabled(false);
        takeOffButton.addActionListener(this);

        alarmButton = new JButton("Start Alarm State");
        alarmButton.setEnabled(true);
        alarmButton.addActionListener(this);

        buttonPanel.add(landButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(10, 0)));
        buttonPanel.add(takeOffButton);
        buttonPanel.add(Box.createRigidArea(new Dimension(10, 0)));
        buttonPanel.add(alarmButton);

        add(buttonPanel);
        add(Box.createRigidArea(new Dimension(0, 10)));

	}
	

	public void registerController(DashboardController contr){
		this.controller = contr;
	}


	/* SETTERS */

	public void setHangarState(String msg){
		SwingUtilities.invokeLater(() -> {
			hangarState.setText(msg); 
		});
	}


	public void setCurrentTemperature(Float msg){
		SwingUtilities.invokeLater(() -> {
			currentTemperature.setText("" + msg); 
		});
	}

	public void setDroneState(String msg) {
		SwingUtilities.invokeLater(() -> {
			droneState.setText(msg);
		});
	}

	public void setDroneAbove(Integer msg) {
		SwingUtilities.invokeLater(() -> {
			if(msg == 0) {
				droneAbove.setText("False");
			} else {
				droneAbove.setText("True");
			}
		});
	}

	public void setGroundDistance(Float msg) {
		SwingUtilities.invokeLater(() -> {
			groundDistance.setText(""+msg);
		});
	}

	/* ENABLERS */
	public void enableTakeoff() {
		SwingUtilities.invokeLater(()-> {
			takeOffButton.setEnabled(true);
		});
	}

	public void enableLanding() {
		SwingUtilities.invokeLater(() -> {
			landButton.setEnabled(true);
		});
	}

	public void disableTakeoff() {
		SwingUtilities.invokeLater(() -> {
			takeOffButton.setEnabled(false);
		});
	}
	public void disableLanding() {
		SwingUtilities.invokeLater(() -> {
			landButton.setEnabled(false);
		});
	}

	// Cosa fare quando un tasto e' cliccato
	public void actionPerformed(ActionEvent ev){
		try {
			if (ev.getSource() == landButton) {			// Se premuto il tasto Land
				landButton.setEnabled(false);
				controller.notifyLanding();
			} else if (ev.getSource() == takeOffButton) { // se premuto il tasto takeoff
				takeOffButton.setEnabled(false);
				controller.notifyTakingOff();
			} else if (ev.getSource() == alarmButton) {
				alarmActive = !alarmActive;

				if (alarmActive) {
					alarmButton.setText("Stop Alarm State");
					controller.notifyStartAlarm(); 
				} else {
					alarmButton.setText("Start Alarm State");
					controller.notifyStopAlarm();
				}
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}
