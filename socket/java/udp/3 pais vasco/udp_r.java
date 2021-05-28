import java.net.*;

// This program waits to receive datagrams sent to a specified port.
// When it receives one, it displays the sending host and port,
// and prints the contents of the datagram as a string.

public class udp_r {
    public static void main(String args[]) throws Exception {
        if (args.length != 1) {
            System.out.println("Usage: java udp_r <port>");
            System.exit(0);
        }

        int port = Integer.parseInt(args[0]);

        byte[] buffer = new byte[1024];
        String s;

        // Create a socket to listen on the port.
        DatagramSocket socket = new DatagramSocket(port);
        System.out.println("Reception socket created...");

        long expected = 1;
        
        for(;;) {
            // Create a packet with an empty buffer to receive data
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

            // Wait to receive a datagram
            socket.receive(packet);

            // Convert the contents to a string
            s = new String(buffer, 0, packet.getLength());

            // Get the seuqence number as a long
            long sequence_number = Long.parseLong(s);

            System.out.println("Sequence " + sequence_number);
            System.out.println("Expected " + expected);
            //if (sequence_number == expected) {
                expected++;
                System.out.println("udp_r: received from " + 
                           packet.getAddress().getHostName() + ":" +
                           packet.getPort() + ": " + s);
            
                           String cadena = "enviado ";
            
            
            /*}
            else {
                System.out.println("ERROR: unexpected sequence number: " + sequence_number);
                System.exit(-1);
            }*/
        }
    }
}
