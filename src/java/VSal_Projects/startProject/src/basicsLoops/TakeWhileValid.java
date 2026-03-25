package basicsLoops;

import common.DateUtils;
import java.util.Scanner;

// WHILE LOOPS 2.1

public class TakeWhileValid {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        while (true) {

            System.out.println("DATE FORMATTER");
            System.out.println("Here are the available formats:");
            System.out.println("0: European");
            System.out.println("1: British");
            System.out.println("2: American");
            System.out.println("3: ISO");

            System.out.print("\nChoose your format: ");
            int format = scanner.nextInt();
            scanner.nextLine();

            //check format
            if (format < 0 || format > 3) {
                System.out.println("Invalid format!");
                break;
            }

            System.out.print("Enter the day: ");
            int day = scanner.nextInt();
            scanner.nextLine();

            System.out.print("Enter the month: ");
            int month = scanner.nextInt();
            scanner.nextLine();

            System.out.print("Enter the year: ");
            int year = scanner.nextInt();
            scanner.nextLine();

            //check date
            boolean valid = DateUtils.isDateValid(day, month, year);

            //output if NOT valid
            if (!valid) {
                System.out.println("Invalid date!");
                break;
            }

            //output
            String output = switch (format) {
                case 0 -> day + "." + month + "." + year; // European
                case 1 -> day + "/" + month + "/" + year; // British
                case 2 -> month + "/" + day + "/" + year; // American
                case 3 -> year + "-" + month + "-" + day; // ISO
                default -> "Unknown format number!";
            };

            System.out.println("Formatted date: " + output);
            System.out.println();
        }

    }
}
