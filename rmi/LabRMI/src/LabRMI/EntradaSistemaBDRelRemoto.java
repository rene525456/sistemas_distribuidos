package LabRMI;
import java.rmi.*;
import java.rmi.server.UnicastRemoteObject;
import java.sql.*;

public class EntradaSistemaBDRelRemoto extends UnicastRemoteObject
                                    implements InterfaceRemotoLogicaNegocio
{
  public static final int MAX_INTENTOS = 3;
  public static final int numPuerto=1099;
  public static final String nombreServicio = "entradaSistema";
  PreparedStatement s;
  Statement st;
  Connection o;
  
  public EntradaSistemaBDRelRemoto() throws RemoteException
  { try{
     //DriverManager.registerDriver(new sun.jdbc.odbc.JdbcOdbcDriver());
     Class.forName("sun.jdbc.odbc.JdbcOdbcDriver");
     System.out.println("Cargado el driver");
     o=DriverManager.getConnection("jdbc:odbc:BDPasswLab3N"); 
     s=o.prepareStatement("select * from cuenta where usuario like ? and password=? and numIntentosFallidos<?");
     st=o.createStatement();
    }
    catch (Exception ex){System.out.println("Error: "+ex.toString());}
  }

/** Método para hacer login
* @param a Nombre del usuario
* @param b Password
* @return Valor booleano que indica si se le da permiso
*/
  public boolean hacerLogin(String a,String b) throws RemoteException {
    try {
      String c="%"+a+"%";
      s.setString(1,c);
      s.setString(2,b);
      s.setInt(3,EntradaSistemaBDRelRemoto.MAX_INTENTOS); 
      ResultSet r=s.executeQuery();
      boolean res = r.next();
      if (res) 
        st.executeUpdate("update cuenta set numIntentosFallidos=0 where usuario='"+a+"'");
      else st.executeUpdate("update cuenta set numIntentosFallidos=numIntentosFallidos+1 where usuario='"+a+"'");
      return res;
    }
    catch (Exception ex) {System.out.println("Error: "+ex.toString());
                         return false;}
    }

public static void main(String[] args) {

	EntradaSistemaBDRelRemoto objetoServidor;	
	try { 		  		
		System.setProperty("java.security.policy",
				           "C:\\LabRMI\\java.policy");
		//O bien colocar el fichero java.policy en $jre$\lib\security	
		System.setSecurityManager(new RMISecurityManager());

	objetoServidor = new EntradaSistemaBDRelRemoto();
	System.out.println("lanzado objeto");

  try { java.rmi.registry.LocateRegistry.createRegistry(numPuerto); // Equivalente a lanzar RMIREGISTRY
  } catch (Exception e) 
      {System.out.println(e.toString()+"\nSe supone que el error es porque el rmiregistry ya estaba lanzado");}
  
	// Registrar el servicio remoto
	Naming.rebind("//localhost:"+numPuerto+"/"+nombreServicio,objetoServidor);
 	// "//DireccionIP:NumPuerto/NombreServicio"
    // NO FUNCIONA SI EL SERVIDOR DE NOMBRE rmiregistry NO ESTÁ EN EL localhost

  } catch (Exception e) 
	 {System.out.println("Error al lanzar el servidor: "+e.toString());}
}
}