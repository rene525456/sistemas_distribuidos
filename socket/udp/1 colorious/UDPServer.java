import java.net.*;
import java.io.*;
public class UDPServer{
    public static void main(String args[]){
        DatagramSocket aSocket = null;
        try{
            aSocket = new DatagramSocket(6789);
            byte[] buffer = new byte[1000];
            while(true){
                System.out.println("\n********Esperando peticiones********");    
                DatagramPacket request = new DatagramPacket(buffer, buffer.length);
                aSocket.receive(request);
                System.out.println("Data = " + new String(request.getData())+"\nLength = " + request.getLength()+"\nAddress = "+ request.getAddress()+"\nPort = "+ request.getPort());
                
                DatagramPacket reply = new DatagramPacket(request.getData(),request.getLength(), request.getAddress(), request.getPort());
                aSocket.send(reply);
            }
        } catch (SocketException e){
            System.out.println("Socket: " + e.getMessage());
        } catch (IOException e) {
            System.out.println("IO: " + e.getMessage());
        } finally {
            if (aSocket != null) 
                aSocket.close();
        }
    }
}
