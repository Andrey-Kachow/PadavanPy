package homeWork;
import java.util.Scanner;

// CHECK IF A DATE IS VALID & ADJUST ACCORDING TO A PREDETERMINED FORMATING MODE

public class formatterDate {


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

        //check month
        if(month < 1 || month > 12){
            valid = false;
        }

        //check days in month
        if (month == 1 || month == 3 || month == 5 || month == 7 ||
                month == 8 || month == 10 || month == 12) {
            maxDay = 31;
        } else if (month == 4 || month == 6 || month == 9 || month == 11){
            maxDay = 30;
        } else if (month == 2 && (year % 4 == 0 && year % 100 != 0 ) || (year % 400 == 0) ){
            maxDay = 29;
        } else {
            maxDay = 28;
        }

        //check day
        if (day < 1 || day > maxDay) {
            valid = false;
        }

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