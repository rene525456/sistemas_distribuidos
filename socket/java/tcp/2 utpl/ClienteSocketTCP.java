import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ClienteSocketTCP {

	public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException, InterruptedException{
    	//get the localhost IP address, if server is running on some other IP, you need to use that
    	//InetAddress host = InetAddress.getLocalHost();
	    	String host = "127.0.0.1";
	    	Socket socket = null;
	    	ObjectOutputStream oos = null;
	    	ObjectInputStream ois = null;
	    	for(int i=0; i<20;i++){
			//establish socket connection to server
			//socket = new Socket(host.getHostName(), 9876);
			socket = new Socket(host, 9876);
			//write to socket using ObjectOutputStream
			oos = new ObjectOutputStream(socket.getOutputStream());
			System.out.println("Sending request to Socket Server");
			if(i==19)
				oos.writeObject("exit");
			else 
				oos.writeObject(""+i);
			//read the server response message
			ois = new ObjectInputStream(socket.getInputStream());
			String message = (String) ois.readObject();
			System.out.println("Message: " + message);
			//close resources
			ois.close();
			oos.close();
			Thread.sleep(1000);
	    	}
	}
}
