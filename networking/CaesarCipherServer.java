
import java.util.Scanner;
import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.util.Date;
import java.text.DateFormat;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;

public class CaesarCipherServer {

	public static void main(String[] args) {
		if (args.length != 1) {
			System.out.println("Usage: java CaesarCipherServer <port>");
			System.exit(1);
		}
		int port = Integer.parseInt(args[0]);

		try (ServerSocket serverSocket = new ServerSocket(port);) {
			System.out.println("Initializing connection to port: " + port);
			System.out.println("Connecting...");

			while (true) {
				Socket c = serverSocket.accept();

				System.out.println(new Date().toString() + "\nConnection initialized with " + c.getRemoteSocketAddress().toString());
				new MultiCaesarCipherServer(c).start();
			}
		} catch (IOException e) {
			System.out.println("Error...Failure to connect to port " + port);
		}

	}

}

class MultiCaesarCipherServer extends Thread {
	private Socket mySocket;

	public MultiCaesarCipherServer(Socket mySocket) {
		this.mySocket = mySocket;
	}

	// code.java.net Java Server Multi thread Algorithm and tutorial
	public void run() {
		try {
			BufferedReader userInput = new BufferedReader(new InputStreamReader(mySocket.getInputStream()));
			PrintWriter sendToClient = new PrintWriter(mySocket.getOutputStream(), true);

			String line;
			line = userInput.readLine();
			int rotation = Integer.valueOf(line);

			sendToClient.println("Encrypting with rotation num: " + rotation );

			// check if input is not empty or == quit
			while ((line = userInput.readLine()) != null && !line.isEmpty() && !line.equals("q")) {
				//System.out.println(line); // receive messages from client
				sendToClient.println(encrypt(line, rotation));
			}

			mySocket.close();
			System.out.println(new Date().toString() + "\nConnection disconnected with " + mySocket.getRemoteSocketAddress().toString());

		} catch (IOException ex) {
			System.err.println("Error..." + ex);
			System.exit(1);
		}
	}

	public String encrypt(String string, int num) {
		String encrypted = ""; 
		int n;
		for(int i = 0; i<string.length(); i++){
			n = (int) string.charAt(i);
			if(n>64 && n<91)//UpperCase
			{
				n-=65;
				n+=num;n= (n % 26 + 26) % 26;
				n+=65;
			}
			else if(n>96 && n<123)//LowerCase
			{
				n-=97;
				n+=num;n= (n % 26 + 26) % 26;					
				n+=97;
			}
			encrypted += (char) n;
		}
		return encrypted;
	}
}
