package iot;

/**
 *
 */
public class SimpleSerialMonitor  {

    // private static String DEFAULT_SERIAL_PORT_NAME = "/dev/tty.usbmodem1422401"; /* to be changed depending on the system */
    private static String DEFAULT_SERIAL_PORT_NAME = "COM5"; /* to be changed depending on the system */
    
    public static void main(String[] args) throws Exception {

        String comPortName = DEFAULT_SERIAL_PORT_NAME; // args[0];

        if (args.length > 0) {
            comPortName = args[0];
        } 
        
        System.out.println("Start monitoring serial port " + comPortName + " at 9600 baud rate");  // Fixato typo "boud" -> "baud"
        
        try {
            SerialMonitor monitor = new SerialMonitor();
            monitor.start(comPortName);							
            Thread.sleep(1000000);  // Per test, riduci a 30000 (30 sec) se vuoi
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        } catch (Exception ex) {  // Cattura tutte le altre eccezioni
            System.err.println("Errore durante l'avvio del monitor: ");
            ex.printStackTrace();  // Stampa lo stack trace per debug
            System.exit(1);  // Opzionale: esci esplicitamente con code 1
        }
    }
}