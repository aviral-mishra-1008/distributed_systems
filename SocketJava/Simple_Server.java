import java.io.*;
import java.net.*;


public class Simple_Server{

    private static final int PORT = 8003;

    public static void main(String[] args){
        try{
            try(ServerSocket serSock = new ServerSocket(PORT)){
                try(Socket cliSock = serSock.accept()){
                    BufferedReader in = new BufferedReader(new InputStreamReader(cliSock.getInputStream()));
                    PrintWriter out = new PrintWriter(cliSock.getOutputStream(),true);

                    String inputString = in.readLine();
                    System.out.println("Received: "+inputString);

                    out.println(inputString);
                }
            }
        } catch(IOException e){
            System.out.println("Error message: "+e.getMessage());
        }
    }
}
