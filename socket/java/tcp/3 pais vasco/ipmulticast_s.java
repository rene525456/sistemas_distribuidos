import java.net.*;
import java.io.*;
import java.util.Random;

public class ipmulticast_s {
    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.out.println("Usage: java ipmulticast_s <your username>");
            System.exit(0);
        }

        String message;
        int n = 1;
        InetAddress address = null;
        MulticastSocket socket = null;
        DatagramPacket packet = null;
        Random r = new Random();
        long t;

        try {
            //address = InetAddress.getByName("224.0.0.1");
            address = InetAddress.getByName("127.0.0.1");
        }
        catch (UnknownHostException e) {
            System.out.println("Error: " + e.toString());
        }

        try {
            socket = new MulticastSocket();
            // socket.setTimeToLive(255);
        }
        catch (IOException e) {
            System.out.println("Error: " + e.toString());
        }

        while (true) {
            message = args[0] + " sender's message #" + Integer.toString(n++);

            byte[] data = new byte[1024];
            data = message.getBytes();
            packet = new DatagramPacket(data, data.length, address, 4000);

            socket.send(packet);
            System.out.println("Sent: " + message);

            t = (r.nextInt(10) + 1) * 100;  // value between 100 and 1000
            Thread.sleep(t);
        }
    }
}
