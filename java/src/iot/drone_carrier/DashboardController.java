package iot.drone_carrier;
public class DashboardController  {

	static final String MSG_TAKING_OFF  = "to";
	static final String MSG_LANDING 	= "la";
	
	static final String MSG_RESET       = "re";
	static final String MSG_OPERATING 	= "op";

	static final String MSG_ALARM_ON = "ao";
	static final String MSG_ALARM_OFF = "af";
	
	SerialCommChannel channel;
	DashboardView view;
	LogView logger;
	
	public DashboardController(String port, DashboardView view, LogView logger) throws Exception {
		this.view = view;
		this.logger = logger;
		
		channel = new SerialCommChannel(port,9600);		
		new MonitoringAgent(channel,view,logger).start();
			
		/* attesa necessaria per fare in modo che Arduino completi il reboot */
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
	
	}


    public void notifyReset() {
        channel.sendMsg(MSG_RESET);
        logger.log("RESET");
    }
	
	public void notifyTakingOff() {
		channel.sendMsg(MSG_TAKING_OFF);
		logger.log("TAKING OFF");
	}

	public void notifyOperating() {
		channel.sendMsg(MSG_OPERATING);
		logger.log("OPERATING");
	}
	
	public void notifyLanding() {
		channel.sendMsg(MSG_LANDING);
		logger.log("LANDING");
	}

	public void notifyStartAlarm() {
		channel.sendMsg(MSG_ALARM_ON);
		logger.log("ALARM ON");
	}
	public void notifyStopAlarm()  {
		channel.sendMsg(MSG_ALARM_OFF);
		logger.log("ALARM OFF");
	}


}
