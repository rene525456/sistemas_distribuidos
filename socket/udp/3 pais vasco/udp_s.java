import java.net.*;

// This program sends periodically a datagram to the specified (host & port)

public class udp_s {
    public static void main(String args[]) throws Exception {
        if (args.length != 3) {
            System.out.println("Usage: java udp_s <host> <port> <period in ms>");
            System.exit(0);
        }

        // Get the internet address of the specified host and the port number
        InetAddress address = InetAddress.getByName(args[0]);
        System.out.println("Address = " + address);
        int port = Integer.parseInt(args[1]);
        System.out.println("Port = " + port);

        // Create a socket, and send the packet through it
        DatagramSocket socket = new DatagramSocket();
        System.out.println("Sending socket created...");

        String s = new String();
        long sequence_number = 0;

        long period = Long.parseLong(args[2]);
        byte[] buffer = new byte[1000];
        for (;;) {
            sequence_number++;
            Long sequence = new Long(sequence_number);
            s = sequence.toString();

            // Convert the string s to an array of bytes
            byte[] message = new byte[1024];
            message = s.getBytes();

            // Initialize the packet with data and address
            DatagramPacket packet = new DatagramPacket(message, s.length(), address, port);

            // send the packet through the socket
            System.out.println("udp_s: sending message " + sequence_number);
            socket.send(packet);

            // Wait for period milliseconds


            
            

            Thread.sleep(period);


        }
    }
}
