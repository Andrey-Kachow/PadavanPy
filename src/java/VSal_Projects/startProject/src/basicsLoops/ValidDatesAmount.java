package basicsLoops;

import common.DateUtils;
import java.util.Scanner;

// WHILE LOOPS 2.3

public class ValidDatesAmount {
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.print("How many dates you want to process? ");
        int size = scanner.nextInt();
        scanner.nextLine();

        int validDates = 0;
        int attempts = 0;

        //Format dates

        while (attempts < size) {
            attempts++;

            System.out.println("\n/////////////////");
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
                System.out.println("This format does NOT exist.");
                continue;
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
                System.out.println("This date does NOT exist");
                continue;
            }

            //output
            String output = switch (format) {
                case 0 -> day + "." + month + "." + year; // European
                case 1 -> day + "/" + month + "/" + year; // British
                case 2 -> month + "/" + day + "/" + year; // American
                case 3 -> year + "-" + month + "-" + day; // ISO
                default -> "Unknown format number!";
            };

            validDates++;

            System.out.println("Formatted date: " + output);
            System.out.println();

        }

        //Amount of numbers formated:
        System.out.println("\nIn total " + validDates + "/" + size + " date(s) was/were formated.");

        scanner.close();

    }

}
