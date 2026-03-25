package basicsLoops;

import common.DateUtils;
import common.EarliestDay;
import common.LatestDay;
import java.util.Scanner;

// WHILE LOOPS 2.5 & 2.6

public class DatesDuration {
    public static void main(String[] args){

        Scanner scanner = new Scanner(System.in);

        System.out.print("How many dates you want to process? ");
        int size = scanner.nextInt();
        scanner.nextLine();

        String[] dates = new String[size];
        int[][] noFormatDates = new int[size][3];
        int validDates = 0;

        //format asked once, since not in the while loop
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
            System.out.println("Invalid format!");
        }

        while (validDates < size) {

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
            }

            noFormatDates[validDates][0] = day;
            noFormatDates[validDates][1] = month;
            noFormatDates[validDates][3] = year;

            //output
            String output = switch (format) {
                case 0 -> day + "." + month + "." + year; // European
                case 1 -> day + "/" + month + "/" + year; // British
                case 2 -> month + "/" + day + "/" + year; // American
                case 3 -> year + "-" + month + "-" + day; // ISO
                default -> "Unknown format number!";
            };

            //store formatted date in the array
            dates[validDates] = output;
            validDates++;

            System.out.println("Formatted date: " + output);
            System.out.println();
        }

        //check for user error
        if (validDates > 0){
            int[][] validOnly = new int[validDates][3];
            for (int i = 0; i < validDates; i++){
                validOnly[i][0] = noFormatDates[i][0];
                validOnly[i][1] = noFormatDates[i][1];
                validOnly[i][2] = noFormatDates[i][2];
            }

            int earliest = EarliestDay.compareEarlierDates(validOnly);
            int latest = LatestDay.compareLateDates(validOnly);

            System.out.println("The earliest date is: "
                    + validOnly[earliest][0] + "."
                    + validOnly[earliest][1] + "."
                    + validOnly[earliest][2]);

            System.out.println("The latest date is: "
                    + validOnly[latest][0] + "."
                    + validOnly[latest][1] + "."
                    + validOnly[latest][2]);
        } else {
            System.out.println("No valid dates entered.");
        }


    }

}
