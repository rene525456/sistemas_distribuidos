
// Copyright (c) 2001 LSI (UPV-EHU)
package LabRMI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.rmi.*;

/**
 * A Swing-based top level window class.
 * <P>
 * @author Alfredo
 */
public class PresentacionRemoto extends JFrame {
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jPanel1 = new JPanel();
  JLabel jLabel1 = new JLabel();
  JLabel jLabel2 = new JLabel();
  JTextField jTextField1 = new JTextField();
  JPasswordField jPasswordField1 = new JPasswordField();
  JButton jButton1 = new JButton();
  InterfaceRemotoLogicaNegocio intLN;
  JLabel jLabel3 = new JLabel();
  
  public static final int numPuerto=1099;
  public static final String nombreServicio = "entradaSistema";
  public static final String maquinaRemota = "localhost";

  /**
   * Constructs a new instance.
   */
  public PresentacionRemoto() {
    super();
    try  {
      jbInit();
    }
    catch (Exception e) {
      e.printStackTrace();
    }
  }

  /**
   * Initializes the state of this instance.
   */
  private void jbInit() throws Exception {
    this.getContentPane().setLayout(borderLayout1);
    this.setSize(new Dimension(400, 300));
    jLabel1.setText("Escribe nombre usuario:");
    jLabel1.setBounds(new Rectangle(30, 50, 152, 32));
    jLabel2.setBounds(new Rectangle(55, 95, 113, 32));
    jTextField1.setBounds(new Rectangle(181, 50, 164, 31));
    jPasswordField1.setBounds(new Rectangle(180, 95, 163, 32));
    jButton1.setText("Acceder al sistema");
    jButton1.setBounds(new Rectangle(102, 145, 183, 36));
    jLabel3.setBounds(new Rectangle(42, 215, 326, 31));
    jButton1.addActionListener(new java.awt.event.ActionListener() {

      public void actionPerformed(ActionEvent e) {
        jButton1_actionPerformed(e);
      }
    });
    jLabel2.setText("Escribe password:");
    jPanel1.setLayout(null);
    this.setTitle("Este es el nivel de presentacion");
    this.getContentPane().add(jPanel1, BorderLayout.CENTER);
    jPanel1.add(jLabel2, null);
    jPanel1.add(jLabel1, null);
    jPanel1.add(jTextField1, null);
    jPanel1.add(jPasswordField1, null);
    jPanel1.add(jButton1, null);
    jPanel1.add(jLabel3, null);
  }

  public void setLogicaNegocio(InterfaceRemotoLogicaNegocio i) { //Antes NO REMOTO
    intLN=i;
  }

  void jButton1_actionPerformed(ActionEvent e) {
    try{
    	
      boolean b = intLN.hacerLogin(jTextField1.getText(),new String(jPasswordField1.getPassword()));
      if (b) jLabel3.setText("ADELANTE");
      else jLabel3.setText("LO SIENTO, NO TIENES PERMISO PARA ENTRAR");
    }
    catch (Exception ex) {jLabel3.setText("PROBLEMAS CON LA LÓGICA DEL NEGOCIO");}
  }
  
  public static void main(String[] args){
	  PresentacionRemoto p = new PresentacionRemoto();
	  
	  try { 		  		
			System.setProperty("java.security.policy",
					"C:\\LabRMI\\java.policy");
			//O bien colocar el fichero java.policy en $jre$\lib\security	
			System.setSecurityManager(new RMISecurityManager());

			try{
			  p.setLogicaNegocio(
						  (InterfaceRemotoLogicaNegocio) Naming.lookup("rmi://"+maquinaRemota+":"+numPuerto+"/"+nombreServicio));
				  
  		    } catch(Exception e) {System.out.println("Error al conseguir la lógica del negocio: "+ e.toString()); }

  		    p.setVisible(true);

	  } catch (Exception e) 
		 {System.out.println("Error al lanzar el cliente: "+e.toString());}
  }
}


