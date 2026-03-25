package basicsLoops;
import java.util.Scanner;

// WHILE LOOPS 1.1

public class InputEcho {
    public static void main(String[] args){

        Scanner scanner = new Scanner(System.in);

    // INITIAL VERSION: the loop continue as long as I enter any text

    /*  boolean loopMustGoOn = true;
        while (loopMustGoOn) {

            String lineOfText = scanner.nextLine();

            System.out.printf("Your input was \"%s\"\n", lineOfText);

            if (lineOfText.isBlank()) {
                loopMustGoOn = false;
            }
        }
     */

        String response = scanner.nextLine();

        while(!response.isEmpty()){
            System.out.printf("Your input was \"%s\"\n", response);
            response = scanner.nextLine();
        }

    }
}
