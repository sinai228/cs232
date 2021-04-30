// CeasarCipherClient
// Name: Sinai Park (sp46)
// For CS232, Spring 2021
// April 23, 2021

import java.net.*;
import java.util.Scanner;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.OutputStream;
import java.io.DataOutputStream;
import java.io.PrintWriter;

class CaesarCipherClient {
  Scanner myScanner = new Scanner(System.in);
  Socket client;
  PrintWriter out;
  BufferedReader in;
  BufferedReader stdIn;

  public void run(String[] args) {

    String host = args[0];
    int port = Integer.parseInt(args[1]);
    System.out.println("Connected to " + host + " on port " + port + "...");

    try {
      client = new Socket(host, port);
      out = new PrintWriter(client.getOutputStream(), true);
      in = new BufferedReader(new InputStreamReader(client.getInputStream()));
      stdIn = new BufferedReader(new InputStreamReader(System.in));
    } catch (Exception e) {
      System.out.println("Error... Failed in initialization of socket");
      System.out.println(e.toString());
      return;
    }
    // Initiate client
    System.out.println("Welcome to Caesar Cipher Client!");
    System.out.print("Enter a rotation number between 1 and 25: ");
    Integer rotation = myScanner.nextInt();

    if (rotation < 1 || rotation > 25) {
      System.out.println("Please enter a valid integer from 1 to 25.");
      System.exit(1);
    }

    // initiallize server with rotation
    try {
      out.println(rotation);
      System.out.println(in.readLine());
    } catch (Exception ee) {
      System.out.println("Error...Failed to initialize server with rotation...");
    }

    System.out.println("Enter a message to encrypt (q to exit): ");
    String userInput;
    while (true) {
      try {
        while ((userInput = stdIn.readLine()) != null) {
          // quit the program if user enters q
          if (userInput.equals("q")) {
            System.out.println("Quiting...");
            System.exit(1);
          } else {
            out.println(userInput);
            System.out.println("Encrypted: " + in.readLine());
          }
        }
      } catch (Exception eee) {
        try {
          client.close();
        } catch (Exception eeee) {
        }
        ;
        break;
      }
    }
  }

  public static void main(String[] args) {
    if (args.length == 2) {
      CaesarCipherClient c = new CaesarCipherClient();
      c.run(args);
    } else
      System.err.println("\nUsage: java UDPDaytimeClient <host> <port>\n");
  }
}