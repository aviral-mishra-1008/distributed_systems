import java.io.*;
import java.net.*;

public class Simple_Client{
    public static final int PORT = 8003;
    public static final String IPADDR = "localhost";

    public static void main(String[] args) {
        try(Socket cliSock = new Socket(IPADDR,PORT)){
            BufferedReader in = new BufferedReader(new InputStreamReader(cliSock.getInputStream()));
            PrintWriter out = new PrintWriter(cliSock.getOutputStream(), true);
            String sendMessage = "Sending you hello request";

            out.println(sendMessage);
            String response = in.readLine();

            System.out.println("Received response: "+response);

        }catch(IOException e){
            System.out.println("Error: "+e.getMessage());
        }

    }
    
}