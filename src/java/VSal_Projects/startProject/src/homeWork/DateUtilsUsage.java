package homeWork;
import common.DateUtils;

import java.util.Scanner;

// CHECK IF A DATE IS VALID & ADJUST ACCORDING TO A PREDETERMINED FORMATING MODE

public class DateUtilsUsage {


    public static void main(String[] args){

        int maxDay;
        int format;
        boolean valid = true;

        Scanner scanner = new Scanner(System.in);

        System.out.println("DATE FORMATTER");
        System.out.println("Here are the available formats:");
        System.out.println("0: European");
        System.out.println("1: British");
        System.out.println("2: American");
        System.out.println("3: ISO");

        System.out.print("\nChoose your format: ");
        format = scanner.nextInt();
        scanner.nextLine();

        System.out.print("Enter the day: ");
        int day = scanner.nextInt();
        scanner.nextLine();

        System.out.print("Enter the month: ");
        int month = scanner.nextInt();
        scanner.nextLine();

        System.out.print("Enter the year: ");
        int year = scanner.nextInt();
        scanner.nextLine();

        //check format
        if (format < 0 || format > 3) {
            System.out.println("Invalid format!");
            return;
        }

        valid = DateUtils.isDateValid(day, month, year);

        //output if NOT valid
        if (!valid) {
            System.out.println("Invalid date!");
            return;
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

        scanner.close();
    }
}