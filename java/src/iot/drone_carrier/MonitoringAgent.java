package iot.drone_carrier;

import java.util.concurrent.TimeUnit;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	DashboardView view;
	LogView logger;

	private static final String STATE_PREFIX = "STATE,";
	private static final String ERROR_MSG = "ERROR,";
	private static final String LOG_PREFIX = "lo,";
	
	/* "ENUMS" */

	public DroneState droneState = DroneState.INSIDE;
	public HangarState hangarState = HangarState.NORMAL;

	
	public enum HangarState {
		NORMAL("Normal"),
		PREALARM("Prealarm"),
		ALARM("Alarm");


		private final String name;

		HangarState(String name) {
			this.name = name;
		}

		public String getName() {
			return name;
		}

		public static HangarState fromCode(int code) {
			if (code < 0 || code >= values().length) {
				throw new IllegalArgumentException("Invalid hangar code: " + code);
			}
			return values()[code];
		}
	}

		public enum DroneState {
		INSIDE("Inside"),
		OPERATING("Operating"),
		REQUEST_LANDING("Request Landing"),
		REQUEST_TAKEOFF("Request Takeoff");


		private final String name;

		DroneState(String name) {
			this.name = name;
		}

		public String getName() {
			return name;
		}

		public static DroneState fromCode(int code) {
			if (code < 0 || code >= values().length) {
				throw new IllegalArgumentException("Invalid drone code: " + code);
			}
			return values()[code];
		}
	}

	/* ************************************************ */
	/* ******************* DEBUGGING ****************** */
	/* ************************************************ */
	// static final boolean DEBUGGING = true; 
	static final boolean DEBUGGING = false; 
	static final String debuggingMsg = "STATE,0,0,10,20.70,1"; // STATE,<hangar state>,<drone state><distance>,<temp>


	
	public MonitoringAgent(SerialCommChannel channel, DashboardView view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.channel = channel;
	}
	
	public void run(){
		boolean canLand = false;
		boolean canTakeoff = false;
		// -----------------------------------------------------------------------------
		
		while (true){
			try {

				/* DEBUGGING */
				String msg;
				if(DEBUGGING){
					msg = debuggingMsg;
					//msg = "";
				} else {
					msg = channel.receiveMsg();
				}

				logger.log("new msg: "+msg);

				TimeUnit.MILLISECONDS.sleep(100);  // Pausa di 0.1 secondi
				if (msg.startsWith(LOG_PREFIX)) {   // poi decide che messaggio e' (se inizia con log ava nella finestra di log, senno' aggiorna la gui)
					
					String cmd = msg.substring(LOG_PREFIX.length());
					System.out.println(cmd);

					// da DroneRemoteUnit::notifyNewState la stringa con lo gli stati e la temperatura
				} else if (msg.startsWith(STATE_PREFIX)){
					try {
						String args = msg.substring(STATE_PREFIX.length()); 
						String[] elems = args.split(",");
						
						if (elems.length >= 4) {
							int hangarCode = Integer.parseInt(elems[0]);
							int droneCode = Integer.parseInt(elems[1]);
							float groundDistance = Float.parseFloat(elems[2]);
							float currentTemperature = Float.parseFloat(elems[3]);
							int droneAbove = Integer.parseInt(elems[4]);
							view.setHangarState(HangarState.fromCode(hangarCode).getName());
							view.setDroneState(DroneState.fromCode(droneCode).getName());
							view.setGroundDistance(groundDistance);
							view.setCurrentTemperature(currentTemperature);
							view.setDroneAbove(droneAbove);
							
							if (droneCode == 0) {
								droneState = DroneState.INSIDE;
							} else if (droneCode == 1) {
								droneState = DroneState.OPERATING;
							}

							if (hangarCode == 0) {
								hangarState = HangarState.NORMAL;
							} else if (hangarCode == 1) {
								hangarState = HangarState.PREALARM;
							} else if (hangarCode == 2) {
								hangarState = HangarState.ALARM;
							}

							if (hangarState == HangarState.ALARM) {
								view.disableTakeoff();
								view.disableLanding();
								canTakeoff = false;
								canLand = false;
								
							} else if (droneState == DroneState.INSIDE && !canTakeoff) { // inside
								canTakeoff = true;
								view.enableTakeoff();

							} else if (droneState == DroneState.OPERATING && !canLand) {
								canLand = true;
								view.enableLanding();
							} else if (droneState != DroneState.OPERATING && canLand) {
								canLand = false;
								view.disableLanding();
							}
							else if (droneState != DroneState.INSIDE && canTakeoff) { // inside
								canTakeoff = false;
								view.disableTakeoff();
							}

						}
					} catch (Exception ex) {
						ex.printStackTrace();
						System.err.println("Error in msg: " + msg);
					}
				} else if (msg.startsWith(ERROR_MSG)){
					String cmd = msg.substring(ERROR_MSG.length());
					System.out.println(cmd);
					logger.log("!!! ALARM !!! " + msg);
					view.setHangarState("ALARM");
					return;
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}

	void setDroneStateInside() {
		this.droneState = DroneState.INSIDE;
	}

	void setDroneStateOperating() {
		this.droneState = DroneState.OPERATING;
	}
}
