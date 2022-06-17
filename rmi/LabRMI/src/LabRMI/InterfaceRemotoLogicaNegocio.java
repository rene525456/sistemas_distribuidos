package LabRMI;
import java.rmi.*;

public interface InterfaceRemotoLogicaNegocio extends Remote
{
   boolean hacerLogin(String usuario,String password) throws RemoteException;
}