import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;
import java.util.Scanner;

public class Main {

  public static final int SOME_UNRESERVED_PORT = 42069;

  /**
   * Usage: run with argument "listen", "serve" or "read" to act as server
   * or a hostname to act as client of a server.
   */
  public static void main(String[] args) {

    System.out.println("Hello world!");

    boolean actAsServer = List
            .of("listen", "serve", "read")
            .contains(args[0].toLowerCase());

    if (actAsServer) {
      new Server(SOME_UNRESERVED_PORT).run();
    } else {
      String hostToConnect = args[0];
      new Client(hostToConnect, SOME_UNRESERVED_PORT).run();
    }
  }

  static class Server {

    private final int port;

    Server(int port) {
      this.port = port;
    }

    private void listenAndDisplay(ServerSocket serverSocket) throws IOException {
      try (
              Socket clientSocket = serverSocket.accept();
              BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))
      ) {
        String inputLine = in.readLine();
        if (inputLine != null) {
          System.out.println(inputLine);
        }
      }
    }

    void run() {
      try (ServerSocket serverSocket = new ServerSocket(port)) {
        while (true) {
          listenAndDisplay(serverSocket);
        }
      } catch (IOException e) {
        e.printStackTrace();
        throw new RuntimeException();
      }
    }
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
    //
  }

  static class Client {

    private final String host;
    private final int port;

    Client(String host, int port) {
      this.host = host;
      this.port = port;
    }

    void run() {
      while (true) {
        Scanner scanner = new Scanner(System.in);
        try (
                Socket clientSocket = new Socket(host, port);
                PrintWriter pw = new PrintWriter(clientSocket.getOutputStream())
        ) {
          String msg = scanner.nextLine();
          if (msg.isBlank()) {
            break;
          }
          System.out.println("Sending message \"" + msg + "\"");
          pw.println(msg);
          pw.flush();
        } catch (IOException e) {
          throw new RuntimeException(e);
        }
      }
    }
  }


}